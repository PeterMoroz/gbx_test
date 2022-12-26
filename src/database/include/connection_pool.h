#pragma once


#include <string>
#include <list>

#include <mutex>
#include <condition_variable>

#include <connection.h>

namespace gbx
{

class ConnectionPool final
{
public:
    ConnectionPool(const ConnectionPool&) = delete;
    ConnectionPool& operator=(const ConnectionPool&) = delete;

private:
    ConnectionPool() = default;

public:
    ~ConnectionPool() = default;

    static ConnectionPool& getInstance();

    int init(int numConnections,
            const std::string& dbname, 
            const std::string& username, const std::string& password,
            const std::string& host, const std::string& port);
    
    connection_t acquireConnection();
    void releaseConnection(connection_t&& conn);

    int availableConnections();

private:
    std::list<connection_t> _connections;
    std::mutex _mutex;
    std::condition_variable _cond;
};

}
