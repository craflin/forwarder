
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

add_executable(ndtunnel
    ${sources}
)

target_link_libraries(ndtunnel PRIVATE
    libnstd::Core libnstd::Socket
)

source_group("" FILES ${sources})

set_property(TARGET ndtunnel PROPERTY FOLDER "src")

install(TARGETS ndtunnel DESTINATION usr/sbin)

