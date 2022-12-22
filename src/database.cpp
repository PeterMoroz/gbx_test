#include "database.h"

int Database::addUser(const std::string& username, const std::string& password)
{
    for (const auto& ui : _users)
    {
        if (ui.second.name == username)
        {
            return -1;
        }
    }

    auto res = _users.emplace(std::make_pair(_nextId, UserInfo(username, password)));
    if (!res.second)
    {
        return -1;
    }
    
    _nextId++;
    return res.first->first;
}

std::string Database::getUsername(int userId)
{
    auto it = _users.find(userId);
    if (it != _users.cend())
    {
        return it->second.name;
    }
    return std::string();
}

std::string Database::getPassword(int userId)
{
    auto it = _users.find(userId);
    if (it != _users.cend())
    {
        return it->second.pass;
    }
    return std::string();
}