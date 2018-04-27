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

See this project for more information: [mbed-js-st-fw-mqtt-example](https://github.com/STMicroelectronics-CentralLabs/mbed-js-st-examples/tree/master/mbed-js-st-fw-mqtt-example)

## Installation
* Before installing this library, make sure you have a working JavaScript on Mbed project and the project builds for your target device.
Follow [mbed-js-st-fw-mqtt-example](https://github.com/STMicroelectronics-CentralLabs/mbed-js-st-examples/tree/master/mbed-js-st-fw-mqtt-example) to create the project and learn more about using JavaScript on Mbed.

* Install this library using npm (Node package manager) with the following command:
```
cd project_path
npm install mbed-js-st-network-interface --save
```

## Configuration
To use easy-connect, you have have to configure the connectivity method as shown [here](https://github.com/ARMmbed/easy-connect#specifying-the-connectivity-method).

Open build/jerryscript/targets/mbedos5/mbed_app.json (which will be created when you will build the project using gulp for the first time) and modify the file as follows:

```
{
    "config": {
        "network-interface": {
            "help": "options are ETHERNET,WIFI_ESP8266,WIFI_ODIN,MESH_LOWPAN_ND,MESH_THREAD",
            "value": "ETHERNET"
        },
        "mesh_radio_type": {
        	"help": "options are ATMEL, MCR20",
        	"value": "ATMEL"
        },
        "esp8266-tx": {
            "help": "Pin used as TX (connects to ESP8266 RX)",
            "value": "D1"
        },
        "esp8266-rx": {
            "help": "Pin used as RX (connects to ESP8266 TX)",
            "value": "D0"
        },
        "esp8266-debug": {
            "value": false
        },
        "wifi-ssid": {
            "value": "\"SSID\""
        },
        "wifi-password": {
            "value": "\"Password\""
        }
    },
    "macros": ["MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES",
               "JERRY_JS_PARSER 1", "JSMBED_USE_RAW_SERIAL", "JSMBED_OVERRIDE_JERRY_PORT_CONSOLE"],
    "target_overrides": {
        "*": {
            "target.features_add": ["NANOSTACK", "LOWPAN_ROUTER"],
            "mbed-mesh-api.6lowpan-nd-channel-page": 0,
            "mbed-mesh-api.6lowpan-nd-channel": 12,
            "mbed-trace.enable": 0,
            "mbed-http.http-buffer-size": 2048,
            "platform.stdio-baud-rate": 115200,
            "platform.stdio-convert-newlines": true
        },
        "NUCLEO_F429ZI": {
            "target.restrict_size": "0x80000"
        }
    }
}

```

## Usage
```
// Initialize
var network_interface = new NetworkInterface_JS();

// To connect to internet using easy-connect library
network_interface.connect();

```
