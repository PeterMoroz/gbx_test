#include <application.h>
#include <handlers_factory.h>

#include <iostream>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocketImpl.h>


namespace gbx
{

class ServerSocketImpl : public Poco::Net::ServerSocketImpl
{
public:
    using Poco::Net::SocketImpl::init;
};

class Socket : public Poco::Net::Socket
{
public:
    Socket(const std::string& address)
        : Poco::Net::Socket(new ServerSocketImpl())
    {
        const Poco::Net::SocketAddress socket_address(address);
        ServerSocketImpl* socket = static_cast<ServerSocketImpl*>(impl());
        socket->init(socket_address.af());
        socket->setReuseAddress(true);
        socket->setReusePort(false);
        socket->bind(socket_address, false);
        socket->listen();
    }

};

}

using namespace gbx;

int Application::main(const std::vector<std::string>& )
{
    // Poco::Net::HTTPServerParams::Ptr parameters = new Poco::Net::HTTPServerParams();
    // parameters->setTimeout(10000);
    // parameters->setMaxQueued(100);
    // parameters->setMaxThreads(4);

    // const Poco::Net::ServerSocket socket(Socket("localhost:8000"));
    // Poco::Net::HTTPServer server(new RequestHandlerFactory(), socket, parameters);

    // std::cout << "Start HTTP server on port 8000." << std::endl;
    // server.start();
    // waitForTerminationRequest();
    // server.stopAll();

    Poco::Net::HTTPServer server(new RequestHandlerFactory(), 8000);
    server.start();
    logger().information("HTTP server started on port 8000.");
    waitForTerminationRequest();
    logger().information("Stopping HTTP server...");
    server.stop();

    return 0;
}