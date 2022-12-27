#include <iostream>

#include <application.h>
#include <connection_pool.h>

int main(int argc, char* argv[])
{
    gbx::ConnectionPool& connectionPool = gbx::ConnectionPool::getInstance();
    const int numConnections = 10;
    const int actualNumConnections = 
        connectionPool.init(numConnections, "gbx", "postgres", "pguser", "127.0.0.1", "5432");
    
    if (actualNumConnections < numConnections)
    {
        std::cerr << "Could not init DB connection pool." << std::endl;
        return -1;
    }

    gbx::Application application;
    return application.run(argc, argv);
}