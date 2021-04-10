
#include "Listener.hpp"

#include <nstd/Log.hpp>

Server::Client::ICallback* Listener::onAccepted(Server::Client& client_, uint32 ip, uint16 port)
{
    Log::debugf("%s: Accepted client for %s:%hu", (const char*)Socket::inetNtoA(ip),
        (const char*)_destinationHost, _destinationPort);

    Address addr;
    addr.addr = ip;
    addr.port = port;
    Client& client = _clients.append<Server&, Server::Client&, const Address&, Client::ICallback&>(_server, client_, addr, *this);
    if (!client.connect(_destinationHost, _destinationPort))
    {
        _clients.remove(client);
        return nullptr;
    }

    return &client;
}

void Listener::onClosed(Client& client)
{
    _clients.remove(client);
}
