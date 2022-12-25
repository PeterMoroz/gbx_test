#include <gtest/gtest.h>
#include <iostream>

#include "users_db.h"

TEST(DatabaseTest, AddUser)
{
    try {
        UsersDatabase db("gbx", "postgres", "pguser", "127.0.0.1", "5432");
        const int userId = db.addUser("peter", "12345678");
        ASSERT_TRUE(userId != -1);

        ASSERT_TRUE(db.delUser(userId));
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        ASSERT_TRUE(false);
    }
}

TEST(DatabaseTest, GetUsername)
{
    try {
        UsersDatabase db("gbx", "postgres", "pguser", "127.0.0.1", "5432");
        const int userId = db.addUser("peter", "12345678");
        ASSERT_TRUE(userId != -1);
        std::string name(db.getUsername(userId));
        ASSERT_EQ(name, "peter");
        ASSERT_TRUE(db.delUser(userId));
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        ASSERT_TRUE(false);
    }    
}

TEST(DatabaseTest, GetPassword)
{
    try {
        UsersDatabase db("gbx", "postgres", "pguser", "127.0.0.1", "5432");
        const int userId = db.addUser("peter", "12345678");
        ASSERT_TRUE(userId != -1);
        std::string pass(db.getPassword(userId));
        ASSERT_EQ(pass, "12345678");
        ASSERT_TRUE(db.delUser(userId));
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        ASSERT_TRUE(false);
    }      
}


int main(int argc, char* argv[]) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}