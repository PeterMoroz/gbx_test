#pragma once

#include <database.h>


namespace gbx
{

class UsersDatabase : public Database
{
public:
    explicit UsersDatabase(ConnectionPool& connectionPool);

    void addUser(const std::string& username, const std::string& password);
    int getUserId(const std::string& username);
    void delUser(int userId);
    std::string getUsername(int userId);
    std::string getPassword(int userId);
    void changePassword(const std::string& username, const std::string& password);
};

}
