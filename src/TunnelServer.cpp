
#include "TunnelServer.hpp"

#include <nstd/Error.hpp>

TunnelServer::TunnelServer(const Settings &settings) : _settings(settings)
{
    _server.setReuseAddress(true);
    _server.setKeepAlive(true);
    _server.setNoDelay(true);
}

bool TunnelServer::start(Address &failedAddress)
{
    for (List<Settings::Tunnel>::Iterator i = _settings.tunnels.begin(), end = _settings.tunnels.end(); i != end; ++i)
    {
        const Settings::Tunnel &tunnel = *i;
        TunnelListener &listener = _listeners.append<Server &, const String &, uint16>(_server, tunnel.targetHost, tunnel.targetPort);
        if (!_server.listen(tunnel.listenAddr.addr, tunnel.listenAddr.port, listener))
        {
            failedAddress = tunnel.listenAddr;
            return false;
        }
    }
    return true;
}
