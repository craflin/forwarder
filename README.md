
# Forwarder

[![Build Status](http://iocp.hopto.org:8080/buildStatus/icon?job=craflin%2Fforwarder%2Fmaster)](http://iocp.hopto.org:8080/job/craflin/job/forwarder/job/master/)

A very simple TCP v4 port forwarder daemon.

The daemon accepts TCP connections on configured ports and forwards them to another address.

## Build Instructions

* Clone the repository and initialize submodules.
* Build the project with `cmake`.
* You can build a `deb` package using the target `package` in CMake.

## Setup

* Install `tunnel` from the `deb` package.
* Configure TCP tunnels in `/etc/forwarder.conf`.
* Start the `tunnel` daemon with `sudo systemctl start tunnel`.
    * You can use `sudo systemctl enable tunnel` to start the daemon automatically after a system restart.
