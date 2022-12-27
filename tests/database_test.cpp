#include <gtest/gtest.h>
#include <iostream>

#include <connection_pool.h>
#include <users_db.h>

using namespace gbx;

TEST(DatabaseTest, InitPool)
{
    ConnectionPool& connectionPool = ConnectionPool::getInstance();
    const int numConnections = 10;
    const int actualNumConnections = 
        connectionPool.init(numConnections, "gbx", "postgres", "pguser", "127.0.0.1", "5432");
    ASSERT_EQ(numConnections, actualNumConnections);
}

TEST(DatabaseTest, AddUser)
{
    try {
        ConnectionPool& connectionPool = ConnectionPool::getInstance();
        if (connectionPool.availableConnections() == 0)
        {
            const int numConnections = 1;
            const int actualNumConnections = 
                connectionPool.init(numConnections, "gbx", "postgres", "pguser", "127.0.0.1", "5432");
            ASSERT_EQ(numConnections, actualNumConnections);            
        }
        
        UsersDatabase db(connectionPool);
        db.addUser("peter", "12345678");
        const int userId = db.getUserId("peter");
        ASSERT_TRUE(userId > 0);
        db.delUser(userId);
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        ASSERT_TRUE(false);
    }
}

TEST(DatabaseTest, GetUsername)
{
    try {
        ConnectionPool& connectionPool = ConnectionPool::getInstance();
        if (connectionPool.availableConnections() == 0)
        {
            const int numConnections = 1;
            const int actualNumConnections = 
                connectionPool.init(numConnections, "gbx", "postgres", "pguser", "127.0.0.1", "5432");
            ASSERT_EQ(numConnections, actualNumConnections);            
        }

        UsersDatabase db(connectionPool);
        db.addUser("peter", "12345678");
        const int userId = db.getUserId("peter");
        ASSERT_TRUE(userId > 0);        
        const std::string name(db.getUsername(userId));
        ASSERT_EQ(name, "peter");
        db.delUser(userId);
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        ASSERT_TRUE(false);
    }
}

TEST(DatabaseTest, GetPassword)
{
    try {
        ConnectionPool& connectionPool = ConnectionPool::getInstance();
        if (connectionPool.availableConnections() == 0)
        {
            const int numConnections = 1;
            const int actualNumConnections = 
                connectionPool.init(numConnections, "gbx", "postgres", "pguser", "127.0.0.1", "5432");
            ASSERT_EQ(numConnections, actualNumConnections);            
        }

        UsersDatabase db(connectionPool);
        db.addUser("peter", "12345678");
        const int userId = db.getUserId("peter");
        ASSERT_TRUE(userId > 0);
        const std::string pass(db.getPassword(userId));
        ASSERT_EQ(pass, "12345678");
        db.delUser(userId);
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        ASSERT_TRUE(false);
    }      
}
TEST(DatabaseTest, ChangePassword)
{
    try {
        ConnectionPool& connectionPool = ConnectionPool::getInstance();
        if (connectionPool.availableConnections() == 0)
        {
            const int numConnections = 1;
            const int actualNumConnections = 
                connectionPool.init(numConnections, "gbx", "postgres", "pguser", "127.0.0.1", "5432");
            ASSERT_EQ(numConnections, actualNumConnections);            
        }

        UsersDatabase db(connectionPool);
        db.addUser("peter", "12345678");
        const int userId = db.getUserId("peter");
        ASSERT_TRUE(userId > 0);
        {
            const std::string pass(db.getPassword(userId));
            ASSERT_EQ(pass, "12345678");
        }

        {
            db.changePassword("peter", "1234567890");
            const std::string pass(db.getPassword(userId));
            ASSERT_EQ(pass, "1234567890");
        }

        db.delUser(userId);
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