#pragma once

#include <database.h>

class UsersDatabase : public Database
{
public:
    UsersDatabase(const std::string& dbname, 
        const std::string& username, 
        const std::string& password,
        const std::string& host, const std::string& port);

    int addUser(const std::string& username, const std::string& password);
    bool delUser(int userId);
    std::string getUsername(int userId);
    std::string getPassword(int userId);
};