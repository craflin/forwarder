
#pragma once

#include "Address.hpp"

#include <nstd/Socket/Server.hpp>

class Client : public Server::Client::ICallback
    , public Server::Establisher::ICallback
{
public:
    class ICallback
    {
    public:
        virtual void onClosed(Client& client) = 0;

    protected:
        ICallback() { }
        ~ICallback() { }
    };

public:
    Client(Server& server, Server::Client& client, const Address& address, ICallback& callback);
    ~Client();

    bool connect(const String& host, uint16 port);

public: // Server::Client::ICallback
    void onRead() override { forward(_client, *_uplink); }
    void onWrite() override { _uplink->resume(); }
    void onClosed() override { _callback.onClosed(*this); }

public: // Server::Establisher::ICallback
    Server::Client::ICallback* onConnected(Server::Client& client) override;
    void onAbolished() override;

private:
    class Uplink : public Server::Client::ICallback
    {
    public:
        Uplink(Client& client)
            : _client(client)
        {
        }

    public: // Server::Client::ICallback
        void onRead() override { forward(*_client._uplink, _client._client); }
        void onWrite() override { _client._client.resume(); }
        void onClosed() override { _client._callback.onClosed(_client); }

    private:
        Client& _client;
    };

private:
    Server& _server;
    Server::Client& _client;
    const Address _address;
    ICallback& _callback;
    String _destinationHost;
    uint16 _destinationPort;
    Server::Establisher* _establisher;
    Uplink _uplinkCallback;
    Server::Client* _uplink;

private:
    static void forward(Server::Client& from, Server::Client& to);
};
