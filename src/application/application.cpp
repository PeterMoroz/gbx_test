#include <application.h>
#include <handlers_factory.h>


#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocketImpl.h>

#include <Poco/Logger.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/AutoPtr.h>



using namespace gbx;

int Application::main(const std::vector<std::string>& )
{
    Poco::AutoPtr<Poco::SimpleFileChannel> simpleFileChannel(new Poco::SimpleFileChannel());
    simpleFileChannel->setProperty("path", "gbx_test_service.log");
    simpleFileChannel->setProperty("rotation", "2 K");

    Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter());
    patternFormatter->setProperty("pattern", "[%p] %Y-%m-%d %H:%M:%S: %t");

    Poco::AutoPtr<Poco::FormattingChannel> formattingChannel(
        new Poco::FormattingChannel(patternFormatter, simpleFileChannel));

    logger().setChannel(formattingChannel);

    Poco::Net::HTTPServerParams::Ptr parameters = new Poco::Net::HTTPServerParams();
    parameters->setTimeout(10000);
    parameters->setMaxQueued(100);
    parameters->setMaxThreads(4);

    const Poco::Net::ServerSocket socket(8000);
    Poco::Net::HTTPServer server(new RequestHandlerFactory(), socket, parameters);

    server.start();
    logger().information("HTTP server started on port 8000.");
    waitForTerminationRequest();
    logger().information("Stopping HTTP server...");
    server.stop();

    return 0;
}