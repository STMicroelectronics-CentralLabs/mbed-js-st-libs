# mbed-js-st-network-interface
Network Interface Library for Javascript for Mbed OS.

## About library
This library does not provide wrappers, just includes these libraries so they can be used by other libraries.
* [easy-connect](https://github.com/ARMmbed/easy-connect)
* [mbed-http](https://developer.mbed.org/teams/sandbox/code/mbed-http)

## Requirements
This library is to be used with the following tools:
* [Mbed](https://www.mbed.com/en/platform/mbed-os/)
* [JerryScript](https://github.com/jerryscript-project/jerryscript)

See this project for more information: [mbed-js-example](https://github.com/ARMmbed/mbed-js-example)

## Installation
* Before installing this library, make sure you have a working JavaScript on Mbed project and the project builds for your target device.
Follow [mbed-js-example](https://github.com/ARMmbed/mbed-js-example) to create the project and learn more about using JavaScript on Mbed.

* Install this library using npm (Node package manager) with the following command:
```
cd project_path
npm install syed-zeeshan/mbed-js-st-network-interface
```
## Configuration
To use easy-connect, you have have to configure the connectivity method as shown [here](https://github.com/ARMmbed/easy-connect#specifying-the-connectivity-method).

## Usage
```
// Initialize
var network_interface = new NetworkInterface_JS();

// To connect to internet using easy-connect library
network_interface.connect();

```
