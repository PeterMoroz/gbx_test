#pragma once

#include <database.h>


namespace gbx
{

class UsersDatabase : public Database
{
public:
    explicit UsersDatabase(ConnectionPool& connectionPool);

    int addUser(const std::string& username, const std::string& password);
    bool delUser(int userId);
    std::string getUsername(int userId);
    std::string getPassword(int userId);
    bool changePassword(const std::string& username, const std::string& password);
};

}
