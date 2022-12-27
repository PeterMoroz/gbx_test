#include <handlers.h>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/URI.h>
#include <Poco/StringTokenizer.h>
#include <Poco/Net/HTMLForm.h>

#include <connection_pool.h>
#include <users_db.h>

using namespace gbx;


void GetRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp)
{
    Poco::URI uri(req.getURI());
    Poco::Util::Application& app = Poco::Util::Application::instance();
    app.logger().information("Requested URI: %s\tpath: %s", uri.toString(), uri.getPath());

    resp.setContentType("text/plain");
    std::ostream& os = resp.send();

    const std::string path(uri.getPath());
    if (path.find("/api/users/") != std::string::npos)
    {
        Poco::StringTokenizer st(path, "/", Poco::StringTokenizer::TOK_TRIM);
        const std::string id(*(--st.end()));

        int userId = -1;
        try {
            userId = std::stoi(id);
        } catch (const std::exception& ex) {
            ;
        }

        if (userId > 0)
        {
            try {
                ConnectionPool& connectionPool = ConnectionPool::getInstance();
                if (connectionPool.availableConnections() == 0)
                {
                    app.logger().error("DB connections pool limit exceeded.");
                    resp.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);
                }
                else
                {
                    UsersDatabase db(connectionPool);
                    const std::string username(db.getUsername(userId));
                    const std::string password(db.getPassword(userId));

                    resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    os << "username: " << username << ", password: " << password;
                }                
            } catch (const std::exception& ex) {
                app.logger().error("Exception: %s", std::string(ex.what()));
                resp.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            }
        }
        else
        {
            resp.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            os << "Not valid userId.";
        }
    }
    else
    {
        resp.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        os << "Unsupported API.";
    }

    os.flush();
}

void PutRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp)
{
    Poco::URI uri(req.getURI());
    Poco::Util::Application& app = Poco::Util::Application::instance();
    app.logger().information("Requested URI: %s\tpath: %s", uri.toString(), uri.getPath());
    resp.setContentType("text/plain");
    std::ostream& os = resp.send();
    

    const std::string path(uri.getPath());
    if (path.find("/api/users/") != std::string::npos)
    {
        Poco::Net::HTMLForm form(req, req.stream());
        const std::string username(form.get("username"));
        const std::string password(form.get("password"));

        if (!username.empty() && !password.empty())
        {
            try {
                ConnectionPool& connectionPool = ConnectionPool::getInstance();
                if (connectionPool.availableConnections() == 0)
                {
                    app.logger().error("DB connections pool limit exceeded.");
                    resp.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);
                }
                else
                {
                    UsersDatabase db(connectionPool);
                    db.changePassword(username, password);
                    resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                }                
            } catch (const std::exception& ex) {
                app.logger().error("Exception: %s", std::string(ex.what()));
                resp.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            }
        }
        else
        {
            resp.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            os << "No username and/or password.";
        }
    }
    else
    {
        resp.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        os << "Unsupported API.";
    }

    os.flush();
}


void DeleteRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp)
{
    Poco::URI uri(req.getURI());
    Poco::Util::Application& app = Poco::Util::Application::instance();
    app.logger().information("Requested URI: %s\tpath: %s", uri.toString(), uri.getPath());

    resp.setContentType("text/plain");
    std::ostream& os = resp.send();

    const std::string path(uri.getPath());
    if (path.find("/api/users/") != std::string::npos)
    {
        Poco::StringTokenizer st(path, "/", Poco::StringTokenizer::TOK_TRIM);
        const std::string id(*(--st.end()));

        int userId = -1;
        try {
            userId = std::stoi(id);
        } catch (const std::exception& ex) {
            ;
        }

        if (userId > 0)
        {
            try {
                ConnectionPool& connectionPool = ConnectionPool::getInstance();
                if (connectionPool.availableConnections() == 0)
                {
                    app.logger().error("DB connections pool limit exceeded.");
                    resp.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);
                }
                else
                {
                    UsersDatabase db(connectionPool);
                    db.delUser(userId);
                    resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                }
            } catch (const std::exception& ex) {
                app.logger().error("Exception: %s", std::string(ex.what()));
                resp.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            }
        }
        else
        {
            resp.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            os << "Not valid userId.";
        }
    }
    else
    {
        resp.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        os << "Unsupported API.";
    }

    os.flush();
}


void PostRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp)
{
    Poco::URI uri(req.getURI());
    Poco::Util::Application& app = Poco::Util::Application::instance();
    app.logger().information("Requested URI: %s\tpath: %s", uri.toString(), uri.getPath());

    resp.setContentType("text/plain");
    std::ostream& os = resp.send();

    const std::string path(uri.getPath());
    if (path.find("/api/users/") != std::string::npos)
    {
        Poco::Net::HTMLForm form(req, req.stream());
        const std::string username(form.get("username"));
        const std::string password(form.get("password"));

        if (!username.empty() && !password.empty())
        {
            try {
                ConnectionPool& connectionPool = ConnectionPool::getInstance();
                if (connectionPool.availableConnections() == 0)
                {
                    app.logger().error("DB connections pool limit exceeded.");
                    resp.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);
                }
                else
                {
                    UsersDatabase db(connectionPool);
                    db.addUser(username, password);
                    const int userId = db.getUserId(username);
                    resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    os << "userID: " << userId;
                }                
            } catch (const std::exception& ex) {
                app.logger().error("Exception: %s", std::string(ex.what()));
                resp.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            }
        }
        else
        {
            resp.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            os << "No username and/or password.";
        }
    }
    else
    {
        resp.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        os << "Unsupported API.";
    }

    os.flush();
}
