#pragma once

#include <string>
#include <memory>
#include <libpq-fe.h>

class Database
{
public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

protected:
    Database(const std::string& dbname, 
        const std::string& username, 
        const std::string& password,
        const std::string& host, const std::string& port);
    bool checkConnection();

public:
    virtual ~Database();

protected:
    std::unique_ptr<PGconn, decltype(&PQfinish)> _connection;
};
