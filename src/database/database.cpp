#include <database.h>

#include <iostream>


Database::Database(const std::string& dbname, 
        const std::string& username, 
        const std::string& password,
        const std::string& host, const std::string& port)
{
    _connection.reset(PQsetdbLogin(host.c_str(), port.c_str(), NULL, NULL, dbname.c_str(), username.c_str(), password.c_str()), &PQfinish);
}

bool Database::checkConnection()
{
    if (PQstatus(_connection.get()) != CONNECTION_OK)
    {
        std::cerr << "Connection to DB failed: " << PQerrorMessage(_connection.get()) << std::endl;
        return false;
    }
    return true;
}

Database::~Database()
{

}
