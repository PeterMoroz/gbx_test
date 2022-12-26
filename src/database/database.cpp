#include <database.h>


#include <iostream>

using namespace gbx;

Database::Database(ConnectionPool& connectionPool)
    : _connectionPool(connectionPool)
{
    if (_connectionPool.availableConnections() == 0)
    {
        throw std::logic_error("No available connections.");
    }

    _connection = std::move(connectionPool.acquireConnection());

    if (!checkConnection())
    {
        throw std::runtime_error("No connection to DB.");
    }
}

bool Database::checkConnection()
{
    if (!_connection)
    {
        std::cerr << "Connection is not initialized." << std::endl;
        return false;
    }

    if (PQstatus(_connection.get()) != CONNECTION_OK)
    {
        std::cerr << "Connection lost: " << PQerrorMessage(_connection.get()) << std::endl;
        return false;
    }
    return true;
}

Database::~Database()
{
    if (checkConnection())
    {
        // return to pool only valid connections
        _connectionPool.releaseConnection(std::move(_connection));
    }
}
