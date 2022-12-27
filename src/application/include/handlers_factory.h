#pragma once

#include <Poco/Net/HTTPRequestHandlerFactory.h>

namespace gbx
{

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
private:
    Poco::Net::HTTPRequestHandler* createRequestHandler(
        const Poco::Net::HTTPServerRequest& request) override;

};

}
