#include <users_db.h>

#include <sstream>

using namespace gbx;

UsersDatabase::UsersDatabase(ConnectionPool& connectionPool)
    : Database(connectionPool)
{
    const char sql[] = "CREATE TABLE IF NOT EXISTS users( " \
                        "id SERIAL PRIMARY KEY," \
                        "name TEXT NOT NULL UNIQUE," \
                        "pass TEXT NOT NULL UNIQUE);";

    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), sql), &PQclear);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK)
    {
        std::ostringstream oss;
        oss << "CREATE TABLE failed. " << PQresultErrorMessage(result.get());
        throw std::runtime_error(oss.str().c_str());
    }
}


void UsersDatabase::addUser(const std::string& username, const std::string& password)
{
    std::ostringstream oss;
    oss << "INSERT INTO users(name, pass) VALUES('" << username << "', '" << password << "');";
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);

    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK)
    {
        std::ostringstream err_oss;
        err_oss << "INSERT INTO users failed. " << PQresultErrorMessage(result.get());
        throw std::runtime_error(err_oss.str().c_str());
    }


}

int UsersDatabase::getUserId(const std::string& username)
{
    std::ostringstream oss;
    oss << "SELECT id FROM users WHERE name='" << username << "';";
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);
    
    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK)
    {
        std::ostringstream err_oss;
        err_oss << "SELECT FROM users failed. " << PQresultErrorMessage(result.get()) << std::endl;
        return -1;
    }

    const std::string value(PQgetvalue(result.get(), 0, 0));

    int userId = -1;
    try {
        userId = std::stoi(value);
    } catch (const std::exception& ex) {
        std::ostringstream err_oss;
        err_oss << "Couldn't convert " << value << " to number. " << ex.what();
        throw std::logic_error(err_oss.str().c_str());
    }

    return userId;
}

void UsersDatabase::delUser(int userId)
{
    std::ostringstream oss;
    oss << "DELETE FROM users WHERE id=" << userId << ";";
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);

    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK)
    {
        std::ostringstream err_oss;
        err_oss << "DELETE FROM users failed. " << PQresultErrorMessage(result.get());
        throw std::runtime_error(err_oss.str().c_str());
    }
}

std::string UsersDatabase::getUsername(int userId)
{
    std::ostringstream oss;
    oss << "SELECT name FROM users WHERE id=" << userId << ";";
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);
    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK)
    {
        std::ostringstream err_oss;
        err_oss << "SELECT FROM users failed. " << PQresultErrorMessage(result.get());
        throw std::runtime_error(err_oss.str().c_str());
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
        std::ostringstream err_oss;
        err_oss << "SELECT FROM users failed. " << PQresultErrorMessage(result.get());
        throw std::runtime_error(err_oss.str().c_str());
    }

    const std::string value(PQgetvalue(result.get(), 0, 0));
    return value;
}

void UsersDatabase::changePassword(const std::string& username, const std::string& password)
{
    std::ostringstream oss;
    oss << "UPDATE users SET pass ='" << password << "' WHERE name='" << username << "';";
    std::unique_ptr<PGresult, decltype(&PQclear)> result(PQexec(_connection.get(), oss.str().c_str()), &PQclear);
    if (PQresultStatus(result.get()) != PGRES_COMMAND_OK)
    {
        std::ostringstream err_oss;
        err_oss << "UPDATE failed. " << PQresultErrorMessage(result.get());
        throw std::runtime_error(err_oss.str().c_str());
    }
}