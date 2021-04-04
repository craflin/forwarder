
#pragma once

#include <nstd/String.hpp>
#include <nstd/List.hpp>

#include "Address.hpp"

struct Settings
{
    struct Tunnel
    {
        Address listenAddr;
        String targetHost;
        uint16 targetPort;

        Tunnel() : targetPort() {}
    };

    List<Tunnel> tunnels;

    Settings();

    static void loadSettings(const String& file, Settings& settings);
};

