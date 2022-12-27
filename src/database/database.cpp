#include <database.h>

#include <sstream>

using namespace gbx;

Database::Database(ConnectionPool& connectionPool)
    : _connectionPool(connectionPool)
{
    if (_connectionPool.availableConnections() == 0)
    {
        throw std::logic_error("No available connections.");
    }

    _connection = std::move(connectionPool.acquireConnection());

    checkConnection();
}

void Database::checkConnection()
{
    if (!_connection)
    {
        throw std::logic_error("Connection is not initialized.");
    }

    if (PQstatus(_connection.get()) != CONNECTION_OK)
    {
        std::ostringstream oss;
        oss << "Connection lost: " << PQerrorMessage(_connection.get());
        throw std::runtime_error(oss.str().c_str());
    }
}

Database::~Database()
{
    if (_connection && PQstatus(_connection.get()) == CONNECTION_OK)
    {
        // return to pool only valid connections
        _connectionPool.releaseConnection(std::move(_connection));
    }
}
