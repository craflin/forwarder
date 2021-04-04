
#pragma once

#include "Settings.hpp"
#include "TunnelListener.hpp"

#include <nstd/Socket/Server.hpp>
#include <nstd/PoolList.hpp>

class TunnelServer
{
public:
    TunnelServer(const Settings& settings);

    bool start(Address& failedAddress);

    void run() {_server.run();}

private:
    const Settings& _settings;
    Server _server;
    PoolList<TunnelListener> _listeners;
};
