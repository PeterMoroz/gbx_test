#include <handlers_factory.h>
#include <handlers.h>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>

using namespace gbx;

Poco::Net::HTTPRequestHandler* 
RequestHandlerFactory::createRequestHandler(
    const Poco::Net::HTTPServerRequest& request)
{
    const std::string method(request.getMethod());

    Poco::Util::Application& app = Poco::Util::Application::instance();
    app.logger().information("Request of type %s\tfrom %s", method, request.clientAddress().toString());

    if (method == Poco::Net::HTTPRequest::HTTP_GET)
    {
        return new GetRequestHandler();
    }

    if (method == Poco::Net::HTTPRequest::HTTP_PUT)
    {
        return new PutRequestHandler();
    }

    if (method == Poco::Net::HTTPRequest::HTTP_DELETE)
    {
        return new DeleteRequestHandler();
    }    

    if (method == Poco::Net::HTTPRequest::HTTP_POST)
    {
        return new PostRequestHandler();
    }

    return NULL;
}