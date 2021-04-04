
#include "TunnelListener.hpp"

#include <nstd/Log.hpp>

Server::Client::ICallback *TunnelListener::onAccepted(Server::Client &client_, uint32 ip, uint16 port)
{
    Log::debugf("%s: Accepted client for %s:%hu", (const char*)Socket::inetNtoA(ip),
        (const char*)_destinationHost, _destinationPort);

    Address addr;
    addr.addr = ip;
    addr.port = port;
    TunnelClient &client = _clients.append<Server &, Server::Client &, const Address &, TunnelClient::ICallback &>(_server, client_, addr, *this);
    if (!client.connect(_destinationHost, _destinationPort))
    {
        _clients.remove(client);
        return nullptr;
    }

    return &client;
}

void TunnelListener::onClosed(TunnelClient &client)
{
    _clients.remove(client);
}
