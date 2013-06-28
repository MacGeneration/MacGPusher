# MacGPusher #

This is a small C++11 project for interacting with the Apple Push Notification Service (APNS).


## Installation ##

First set your certificates paths in **global.hpp**.

#### OS X: ####

Just open *MacGPusher.xcodeproj* and click the build button.


#### Linux: ####

You need a compiler that supports C++11, and to link to **libssl** and **libcrypto**.

*gcc:*

	g++ MMGAPNSConnection.cpp MMGSSLConnection.cpp MMGDevice.cpp MMGTools.cpp MMGPayload.cpp main.cpp -lssl -lcrypto -std=c++11 -o MacGPusher

*clang:*

*Some users reported problem building with clang on Debian 7.0 (see #1)*

	clang++ MMGAPNSConnection.cpp MMGSSLConnection.cpp MMGDevice.cpp MMGTools.cpp MMGPayload.cpp main.cpp -lssl -lcrypto -std=c++11 -o MacGPusher


## Usage ##

Look at **main.cpp** to see a very basic example of sending a notification to a single device.

Fetching a list of devices is up to you. I use this project with **libmysqlclient** to fetch a list of *~100k* devices and send the notifications with good performances.


## TODO: ##

- Adding support for the Feedback service.
- A Makefile for Linux users, I don't like doing this stuff so..


## License ##

***MacGPusher*** is released under the *Simplified BSD license*, see **LICENSE.txt**.

Blog : <http://www.cocoaintheshell.com/>

Twitter : @Nyx0uf
