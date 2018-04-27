# mbed-js-st-serial-interface
Library to communicate with serial terminal.

## About library
This library allows using Serial port as an JavaScript editor based on [mbed-js-repl-example](https://github.com/ARMmbed/mbed-js-repl-example). The JS program can be written and viewed using Serial port in real-time Serial port terminal. 

## Requirements
This library is to be used with the following tools:
* [Mbed](https://www.mbed.com/en/platform/mbed-os/)
* [JerryScript](https://github.com/jerryscript-project/jerryscript)

See this project for more information: [mbed-js-st-fw-mqtt-example](https://github.com/STMicroelectronics-CentralLabs/mbed-js-st-examples/tree/master/mbed-js-st-fw-mqtt-example)

## Installation
* Before installing this library, make sure you have a working JavaScript on Mbed project and the project builds for your target device.
Follow [mbed-js-st-fw-mqtt-example](https://github.com/STMicroelectronics-CentralLabs/mbed-js-st-examples/tree/master/mbed-js-st-fw-mqtt-example) to create the project and learn more about using JavaScript on Mbed.

* Install this library using npm (Node package manager) with the following command:
```
cd project_path
npm install mbed-js-st-serial-interface --save
```

## Usage
To use this library, you have to initialize in your main.js as follows:
```
// Initialize serial interface library
var serial_interface = new SerialInterface();

```
After initializing, you can connect device with any serial terminal and start coding, the code can be seen in real-time.

* __Run JavaScript program in real-time:__

    To run the program, press `Ctrl+R`. This will execute the JS program and will display the output at serial terminal.

* __Flash JavaScript program to ROM:__

    You can also flash the program currently being written using [mbed-js-st-js-manager](https://www.npmjs.com/package/mbed-js-st-js-manager) library. To flash the code, use `Ctrl+F` key to flash the code to ROM memory of the device.

