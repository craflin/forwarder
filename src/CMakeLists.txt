
set(sources
    Address.hpp
    Main.cpp
    Settings.cpp
    Settings.hpp
    TunnelClient.cpp
    TunnelClient.hpp
    TunnelListener.cpp
    TunnelListener.hpp
    TunnelServer.cpp
    TunnelServer.hpp
)

add_executable(tunnel
    ${sources}
)

target_link_libraries(tunnel PRIVATE
    libnstd::Socket
)

source_group("" FILES ${sources})

set_property(TARGET tunnel PROPERTY FOLDER "src")

install(TARGETS tunnel DESTINATION usr/sbin)

