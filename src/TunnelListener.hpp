
#pragma once

#include "TunnelClient.hpp"

#include <nstd/PoolList.hpp>
#include <nstd/Socket/Server.hpp>

class TunnelListener : public Server::Listener::ICallback
    , public TunnelClient::ICallback
{
public:
    TunnelListener(Server& server, const String& destinationHost, uint16 destinationPort)
        : _server(server)
        , _destinationHost(destinationHost)
        , _destinationPort(destinationPort)
    {
    }

public: // Server::Listener::ICallback
    Server::Client::ICallback* onAccepted(Server::Client& client, uint32 ip, uint16 port) override;

public: // TunnelClient::ICallback
    void onClosed(TunnelClient& client) override;

private:
    Server& _server;
    const String _destinationHost;
    const uint16 _destinationPort;
    PoolList<TunnelClient> _clients;
};
