#pragma once

#include <Poco/Net/HTTPRequestHandler.h>

namespace gbx
{

class GetRequestHandler : public Poco::Net::HTTPRequestHandler
{
private:
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp) override;
};

class PutRequestHandler : public Poco::Net::HTTPRequestHandler
{
private:
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp) override;
};

class DeleteRequestHandler : public Poco::Net::HTTPRequestHandler
{
private:
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp) override;
};

class PostRequestHandler : public Poco::Net::HTTPRequestHandler
{
private:
    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp) override;
};

}