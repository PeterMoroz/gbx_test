#pragma once

#include <libpq-fe.h>

#include <memory>

namespace gbx
{

struct CloseConnection
{
    void operator()(PGconn* conn)
    {
        PQfinish(conn);
    }
};

// using connection_t = std::unique_ptr<PGconn, decltype(&PQfinish)>;
using connection_t = std::unique_ptr<PGconn, CloseConnection>;

}
