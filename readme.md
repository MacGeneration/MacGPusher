# MacGPusher #

This is a small C++11 project for interacting with the Apple Push Notification Service (APNS). You can send push notifications to iOS devices or Safari browser (OS X 10.9 only). It also handles the Feedback service.


## Installation ##

First set your certificates paths in **global.hpp**.

#### OS X: ####

Just open *MacGPusher.xcodeproj* and click the build button.


#### Linux: ####

You need a compiler that supports C++11, and to link to **libssl** and **libcrypto**, then just run **make** (Thanks to ***lledey*** for the Makefile)

If you want to build it by hand :

*gcc:*

	g++ MMGAPNSConnection.cpp MMGSSLConnection.cpp MMGDevice.cpp MMGTools.cpp MMGPayload.cpp MMGSafariPayload.cpp MMGIOSPayload.cpp main.cpp -lssl -lcrypto -std=c++11 -o MacGPusher

*clang:*

*Some users reported problem building with clang on Debian 7.0 (see #1)*

	clang++ MMGAPNSConnection.cpp MMGSSLConnection.cpp MMGDevice.cpp MMGTools.cpp MMGPayload.cpp MMGSafariPayload.cpp MMGIOSPayload.cpp main.cpp -lssl -lcrypto -std=c++11 -o MacGPusher


## Usage ##

Look at **main.cpp** to see a very basic example of sending a notification to a single device.

Look at **feedback.cpp** to see how to use the feedback service.

Fetching a list of devices is up to you. I use this project with **libmysqlclient** to fetch a list of *~100k* devices and send the notifications with good performances.


## License ##

***MacGPusher*** is released under the *Simplified BSD license*, see **LICENSE.txt**.

Twitter : @MacGeneration
