#include <connection_pool.h>

using namespace gbx;

ConnectionPool& ConnectionPool::getInstance()
{
    static ConnectionPool instance;
    return instance;
}

int ConnectionPool::init(int numConnections,
        const std::string& dbname, 
        const std::string& username, const std::string& password,
        const std::string& host, const std::string& port)
{
    std::lock_guard<std::mutex> lock(_mutex);

    int connectionCount = 0;
    for (; connectionCount < numConnections; connectionCount++) {
        connection_t conn(PQsetdbLogin(host.c_str(), port.c_str(), NULL, NULL, dbname.c_str(), username.c_str(), password.c_str()), CloseConnection());
        if (PQstatus(conn.get()) == CONNECTION_OK)
        {
            _connections.push_back(std::move(conn));
        }
        else
        {
            break;
        }
    }

    return connectionCount;
}

connection_t ConnectionPool::acquireConnection()
{
    std::unique_lock<std::mutex> lock(_mutex);
    while (_connections.empty()) {
        _cond.wait(lock);
    }
    connection_t conn = std::move(_connections.front());
    _connections.pop_front();
    return std::move(conn);
}

void ConnectionPool::releaseConnection(connection_t&& conn)
{
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _connections.push_back(std::move(conn));
    }
    _cond.notify_one();
}

int ConnectionPool::availableConnections()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return static_cast<int>(_connections.size());
}