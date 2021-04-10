
#include "Settings.hpp"

#include <nstd/File.hpp>
#include <nstd/List.hpp>
#include <nstd/Log.hpp>

Settings::Settings() { }

void Settings::loadSettings(const String& file, Settings& settings)
{
    String conf;
    if (!File::readAll(file, conf))
        return;
    List<String> lines;
    conf.split(lines, "\n\r");
    for (List<String>::Iterator i = lines.begin(), end = lines.end(); i != end; ++i)
    {
        String line = *i;
        const char* lineEnd = line.find('#');
        if (lineEnd)
            line.resize(lineEnd - (const char*)line);
        line.trim();
        if (line.isEmpty())
            continue;
        List<String> tokens;
        line.split(tokens, " \t");
        if (tokens.size() < 2)
            continue;
        const String& option = *tokens.begin();
        const String& value = *(++tokens.begin());
        if (option == "forward")
        {
            List<String> tokens;
            value.split(tokens, ":", false);
            if (tokens.size() < 3)
                Log::warningf("Invalid forwarder arguments: %s", (const char*)value);
            else
            {
                Settings::Tunnel tunnel;
                List<String>::Iterator args = tokens.begin();
                if (tokens.size() >= 4)
                {
                    tunnel.listenAddr.addr = Socket::inetAddr(*args);
                    ++args;
                }
                tunnel.listenAddr.port = args->toUInt();
                ++args;
                tunnel.targetHost = *args;
                ++args;
                tunnel.targetPort = args->toUInt();
                settings.tunnels.append(tunnel);
            }
        }
        else
            Log::warningf("Unknown option: %s", (const char*)option);
    }
}
