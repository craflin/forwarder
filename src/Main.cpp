
#include <nstd/Log.hpp>
#include <nstd/Thread.hpp>
#include <nstd/Process.hpp>
#include <nstd/Console.hpp>
#include <nstd/Error.hpp>

#include "TunnelServer.hpp"

int main(int argc, char* argv[])
{
  String logFile;
  String configFile("/etc/tunnel.conf");

  // parse parameters
    {
        Process::Option options[] = {
            {'b', "daemon", Process::argumentFlag | Process::optionalFlag},
            {'c', "config", Process::argumentFlag},
            {'h', "help", Process::optionFlag},
        };
        Process::Arguments arguments(argc, argv, options);
        int character;
        String argument;
        while(arguments.read(character, argument))
            switch(character)
            {
            case 'b':
                logFile = argument.isEmpty() ? String("/dev/null") : argument;
                break;
            case 'c':
                configFile = argument;
                break;
            case '?':
                Console::errorf("Unknown option: %s.\n", (const char*)argument);
                return -1;
            case ':':
                Console::errorf("Option %s required an argument.\n", (const char*)argument);
                return -1;
            default:
                Console::errorf("Usage: %s [-b] [-c <file>]\n\
\n\
    -b, --daemon[=<file>]\n\
        Detach from calling shell and write output to <file>.\n\
\n\
    -c <file>, --config[=<file>]\n\
        Load configuration from <file>. (Default is /etc/tunnel.conf)\n\
\n", argv[0]);
              return -1;
        }
    }

    Log::setLevel(Log::debug);

    // load settings
    Settings settings;
    Settings::loadSettings(configFile, settings);

    // daemonize process
#ifndef _WIN32
    if(!logFile.isEmpty())
    {
        Log::infof("Starting as daemon...");
        if(!Process::daemonize(logFile))
        {
            Log::errorf("Could not daemonize process: %s", (const char*)Error::getErrorString());
            return -1;
        }
        Log::setDevice(Log::syslog);
        Log::setLevel(Log::info);
    }
#endif
    // start tunnel server
    TunnelServer server(settings);
    {
        Address failedAddress;
        if (!server.start(failedAddress))
            return Log::errorf("Could not start tunnel server on TCP port %s:%hu: %s", (const char*)Socket::inetNtoA(failedAddress.addr), (uint16)failedAddress.port, (const char*)Socket::getErrorString()), 1;
    }
    for (List<Settings::Tunnel>::Iterator i = settings.tunnels.begin(), end = settings.tunnels.end(); i != end; ++i)
        Log::infof("Listening on TCP port %hu...", (uint16)i->listenAddr.port);

    // run tunnel  server
    server.run();
    return 1;
}
