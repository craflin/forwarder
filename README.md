
# Forwarder

[![Build Status](http://xaws6t1emwa2m5pr.myfritz.net:8080/buildStatus/icon?job=craflin%2Fforwarder%2Fmaster)](http://xaws6t1emwa2m5pr.myfritz.net:8080/job/craflin/job/forwarder/job/master/)

A very simple TCP v4 port forwarder daemon.

The daemon accepts TCP connections on configured ports and forwards them to another address.

## Build Instructions

* Clone the repository and initialize submodules.
* Build the project with `cmake`.
* You can build a `deb` package using the target `package` in CMake.

## Setup

* Install `forwarder` from the `deb` package.
* Configure TCP tunnels in `/etc/forwarder.conf`.
* Start the `forwarder` daemon with `sudo systemctl start forwarder`.
    * You can use `sudo systemctl enable forwarder` to start the daemon automatically after a system restart.
