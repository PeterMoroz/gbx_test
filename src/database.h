#pragma once

#include <string>
#include <unordered_map>

class Database final
{
public:
    int addUser(const std::string& username, const std::string& password);
    std::string getUsername(int userId);
    std::string getPassword(int userId);

private:

    struct UserInfo
    {
        std::string name;
        std::string pass;

        UserInfo(const std::string& n, const std::string& p)
            : name(n), pass(p) {}
    };

    std::unordered_map<int, UserInfo> _users;
    int _nextId = 0;
};