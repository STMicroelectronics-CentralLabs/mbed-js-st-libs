# mbed-js-manager
JS Manager for Javascript on Mbed

## About library
Helper class providing functions for using flash storage for reading and writing JS programs in JavaScript on Mbed.

## Requirements
This library is to be used with the following tools:
* [Mbed](https://www.mbed.com/en/platform/mbed-os/)
* [JerryScript](https://github.com/jerryscript-project/jerryscript)

See this project for more information: [mbed-js-example](https://github.com/ARMmbed/mbed-js-example)

## Dependencies
You need to install dependencies before installing this library.
* [mbed-js-st-network-interface](https://github.com/syed-zeeshan/mbed-js-st-network-interface) 


## Installation
* Before installing this library, make sure you have a working JavaScript on Mbed project and the project builds for your target device.
Follow [mbed-js-example](https://github.com/ARMmbed/mbed-js-example) to create the project and learn more about using JavaScript on Mbed.

* Install this library using npm (Node package manager) with the following command:
```
cd project_path
npm install syed-zeeshan/mbed-js-manager
```

## Configuration
To use JS Manager, you need to configure the memory size you want to reserve from flash storage to be used for storing JS program. Open `mbed_app.json` and set the field `target.restrict-size` to restrict the main program size.

**Example for Nucleo-F429ZI:**

```
{
    "target_overrides": {
        "NUCLEO_F429ZI": {
            "target.restrict_size": "0x80000"
        }
    }
}
```

## Usage
```
// Initialize
var js_manager = new JSManager();

// To erase flash memory (removes all JS programs written to flash storage)
js_manager.erase_flash();

// To run JS prgram from flash memory.
js_manager.run_js_flash();

// To write JS prgram to flash memory using string.
js_manager.write_to_flash(str_prgram);

// To reboot device.
js_manager.reboot();

// To download and flash JS prgram from a given url.
js_manager.load_http_program(url);

// To connect to internet using mbed-js-st-network-interface library
js_manager.connect_to_network();

```
