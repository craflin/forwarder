
#include "Client.hpp"

#include <nstd/Error.hpp>
#include <nstd/Log.hpp>
#include <nstd/Socket/Socket.hpp>

Client::Client(Server& server, Server::Client& client, const Address& address, ICallback& callback)
    : _server(server)
    , _client(client)
    , _address(address)
    , _callback(callback)
    , _destinationPort(0)
    , _establisher(nullptr)
    , _uplinkCallback(*this)
    , _uplink(nullptr)
{
    client.suspend();
}

Client::~Client()
{
    _server.remove(_client);
    if (_establisher)
        _server.remove(*_establisher);
    if (_uplink)
        _server.remove(*_uplink);
}

bool Client::connect(const String& host, uint16 port)
{
    _destinationHost = host;
    _destinationPort = port;
    _establisher = _server.connect(host, port, *this);
    if (!_establisher)
        return false;
    return true;
}

void Client::forward(Server::Client& from, Server::Client& to)
{
    usize size;
    byte buffer[262144];
    if (!from.read(buffer, sizeof(buffer), size))
        return;
    usize postponed;
    if (!to.write(buffer, size, &postponed))
        return;
    if (postponed)
        from.suspend();
}

Server::Client::ICallback* Client::onConnected(Server::Client& client)
{
    Log::infof("%s: Established connection with %s:%hu", (const char*)Socket::inetNtoA(_address.addr),
        (const char*)_destinationHost, _destinationPort);

    _client.resume();
    _uplink = &client;
    return &_uplinkCallback;
}

void Client::onAbolished()
{
    Log::infof("%s: Failed to establish connection with %s:%hu: %s", (const char*)Socket::inetNtoA(_address.addr),
        (const char*)_destinationHost, _destinationPort, (const char*)Error::getErrorString());

    _callback.onClosed(*this);
}
