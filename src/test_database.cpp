#include <gtest/gtest.h>

#include "database.h"

TEST(DatabaseTest, AddUser)
{
    Database db;
    int userId = db.addUser("peter", "12345678");
    ASSERT_EQ(userId, 0);
}

TEST(DatabaseTest, GetUsername)
{
    Database db;
    int userId = db.addUser("peter", "12345678");
    ASSERT_EQ(userId, 0);

    std::string name(db.getUsername(userId));
    ASSERT_EQ(name, "peter");
}

TEST(DatabaseTest, GetPassword)
{
    Database db;
    int userId = db.addUser("peter", "12345678");
    ASSERT_EQ(userId,0);

    std::string pass(db.getPassword(userId));
    ASSERT_EQ(pass, "12345678");
}


int main(int argc, char* argv[]) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}