
cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0048 NEW)

project(forwarder VERSION 0.2.0)

set(CDEPLOY_NO_DEBUG_BUILD True)
set(CDEPLOY_NO_COMPILER True)

include(CDeploy)

add_subdirectory(3rdparty)
add_subdirectory(src)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT "Colin Graf <colin.graf@sovereign-labs.com>")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A very simple TCP v4 port forwarder daemon")
set(CPACK_PACKAGING_INSTALL_PREFIX "/")
#set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/craflin/forwarder")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.15)")
set(CPACK_DEBIAN_PACKAGE_SECTION "net")

include(CPack)

install(FILES etc/forwarder.conf DESTINATION etc)
install(FILES etc/default/forwarder DESTINATION etc/default)
install(PROGRAMS etc/init.d/forwarder DESTINATION etc/init.d)
