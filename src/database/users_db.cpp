#include <users_db.h>

#include <iostream>
#include <sstream>

UsersDatabase::UsersDatabase(const std::string& dbname, 
        const std::string& username, 
        const std::string& password,
        const std::string& host, const std::string& port)
    : Database(dbname, username, password, host, port)
{
    if (!checkConnection())
    {
        throw std::runtime_error("No conection to DB.");
    }

    const char sql[] = "CREATE TABLE IF NOT EXISTS users( " \
                        "id SERIAL PRIMARY KEY," \
                        "name TEXT NOT NULL UNIQUE," \
                        "pass TEXT NOT NULL UNIQUE);";

    PGresult* result = PQexec(_connection.get(), sql);
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cerr << "CREATE failed. " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        throw std::runtime_error("Create table failed.");
    }
    PQclear(result);
}

int UsersDatabase::addUser(const std::string& username, const std::string& password)
{
    std::ostringstream oss;
    oss << "INSERT INTO users(name, pass) VALUES('" << username << "', '" << password << "');";
    PGresult* result = PQexec(_connection.get(), oss.str().c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cerr << "INSERT failed. " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return -1;
    }
    PQclear(result);

    result = PQexec(_connection.get(), "SELECT MAX(id) FROM users;");
    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "SELECT failed. " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return -1;
    }

    const std::string value(PQgetvalue(result, 0, 0));
    PQclear(result);

    int userId = -1;
    try {
        userId = std::stoi(value);
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return userId;
}

bool UsersDatabase::delUser(int userId)
{
    std::ostringstream oss;
    oss << "DELETE FROM users WHERE id=" << userId << ";";
    PGresult* result = PQexec(_connection.get(), oss.str().c_str());

    bool ret = true;
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        std::cerr << "DELETE failed. " << PQresultErrorMessage(result) << std::endl;
        ret = false;
    }
    PQclear(result);
    return ret;
}

std::string UsersDatabase::getUsername(int userId)
{
    std::ostringstream oss;
    oss << "SELECT name FROM users WHERE id=" << userId << ";";
    PGresult* result = PQexec(_connection.get(), oss.str().c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "SELECT failed. " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return "";
    }

    const std::string value(PQgetvalue(result, 0, 0));
    PQclear(result);
    return value;
}

std::string UsersDatabase::getPassword(int userId)
{
    std::ostringstream oss;
    oss << "SELECT pass FROM users WHERE id=" << userId << ";";
    PGresult* result = PQexec(_connection.get(), oss.str().c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        std::cerr << "SELECT failed. " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return "";
    }

    const std::string value(PQgetvalue(result, 0, 0));
    PQclear(result);
    return value;
}
