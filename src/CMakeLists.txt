
set(sources
    Address.hpp
    Main.cpp
    Settings.cpp
    Settings.hpp
    Client.cpp
    Client.hpp
    Listener.cpp
    Listener.hpp
)

add_executable(forwarder
    ${sources}
)

target_link_libraries(forwarder PRIVATE
    libnstd::Socket
)

source_group("" FILES ${sources})

set_property(TARGET forwarder PROPERTY FOLDER "src")

install(TARGETS forwarder DESTINATION usr/sbin)

