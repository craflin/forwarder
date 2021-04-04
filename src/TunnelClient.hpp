
#pragma once

#include "Address.hpp"

#include <nstd/Socket/Server.hpp>

class TunnelClient : public Server::Client::ICallback, public Server::Establisher::ICallback
{
public:
    class ICallback
    {
    public:
        virtual void onClosed(TunnelClient &client) = 0;

    protected:
        ICallback() {}
        ~ICallback() {}
    };

public:
    TunnelClient(Server &server, Server::Client &client, const Address &address, ICallback &callback);
    ~TunnelClient();

    bool connect(const String &host, uint16 port);

public: // Server::Client::ICallback
    void onRead() override { forward(_client, *_uplink); }
    void onWrite() override { _uplink->resume(); }
    void onClosed() override { _callback.onClosed(*this); }

public: // Server::Establisher::ICallback
    Server::Client::ICallback *onConnected(Server::Client &client) override;
    void onAbolished() override;

private:
    class Uplink : public Server::Client::ICallback
    {
    public:
        Uplink(TunnelClient &client) : _client(client) {}

    public: // Server::Client::ICallback
        void onRead() override { forward(*_client._uplink, _client._client); }
        void onWrite() override { _client._client.resume(); }
        void onClosed() override { _client._callback.onClosed(_client); }

    private:
        TunnelClient &_client;
    };

private:
    Server &_server;
    Server::Client &_client;
    const Address _address;
    ICallback &_callback;
    String _destinationHost;
    uint16 _destinationPort;
    Server::Establisher *_establisher;
    Uplink _uplinkCallback;
    Server::Client *_uplink;

private:
    static void forward(Server::Client &from, Server::Client &to);
};
