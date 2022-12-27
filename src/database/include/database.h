#pragma once

#include <connection_pool.h>
#include <connection.h>

namespace gbx
{

class Database
{
public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

protected:
    explicit Database(ConnectionPool& connectionPool);
    void checkConnection();

public:
    virtual ~Database();

protected:
    ConnectionPool& _connectionPool;
    connection_t _connection;
};


}
