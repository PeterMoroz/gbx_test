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

    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), sql), &PQclear);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK)
    {
        std::cerr << "CREATE failed. " << PQresultErrorMessage(result.get()) << std::endl;
        throw std::runtime_error("Create table failed.");
    }
}

int UsersDatabase::addUser(const std::string& username, const std::string& password)
{
    std::ostringstream oss;
    oss << "INSERT INTO users(name, pass) VALUES('" << username << "', '" << password << "');";
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);

    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK)
    {
        std::cerr << "INSERT failed. " << PQresultErrorMessage(result.get()) << std::endl;
        return -1;
    }

    result.reset(PQexec(_connection.get(), "SELECT MAX(id) FROM users;"));
    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK)
    {
        std::cerr << "SELECT failed. " << PQresultErrorMessage(result.get()) << std::endl;
        return -1;
    }

    const std::string value(PQgetvalue(result.get(), 0, 0));

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
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);

    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK)
    {
        std::cerr << "DELETE failed. " << PQresultErrorMessage(result.get()) << std::endl;
        return false;
    }
    return true;
}

std::string UsersDatabase::getUsername(int userId)
{
    std::ostringstream oss;
    oss << "SELECT name FROM users WHERE id=" << userId << ";";
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);
    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK)
    {
        std::cerr << "SELECT failed. " << PQresultErrorMessage(result.get()) << std::endl;
        return "";
    }

    const std::string value(PQgetvalue(result.get(), 0, 0));
    return value;
}

std::string UsersDatabase::getPassword(int userId)
{
    std::ostringstream oss;
    oss << "SELECT pass FROM users WHERE id=" << userId << ";";
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);
    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK)
    {
        std::cerr << "SELECT failed. " << PQresultErrorMessage(result.get()) << std::endl;
        return "";
    }

    const std::string value(PQgetvalue(result.get(), 0, 0));
    return value;
}
