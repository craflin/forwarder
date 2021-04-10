
#pragma once

#include "Client.hpp"

#include <nstd/PoolList.hpp>
#include <nstd/Socket/Server.hpp>

class Listener : public Server::Listener::ICallback
    , public Client::ICallback
{
public:
    Listener(Server& server, const String& destinationHost, uint16 destinationPort)
        : _server(server)
        , _destinationHost(destinationHost)
        , _destinationPort(destinationPort)
    {
    }

public: // Server::Listener::ICallback
    Server::Client::ICallback* onAccepted(Server::Client& client, uint32 ip, uint16 port) override;

public: // Client::ICallback
    void onClosed(Client& client) override;

private:
    Server& _server;
    const String _destinationHost;
    const uint16 _destinationPort;
    PoolList<Client> _clients;
};
