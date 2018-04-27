# mbed-js-spi
JavaScript wrappers for SPI by STMircroelectronics.

## About library
Helper class providing functions for SPI library (part of [X_NUCLEO_COMMON](https://os.mbed.com/teams/ST/code/X_NUCLEO_COMMON/)) in JavaScript.

## Requirements
This library is to be used with the following tools:
* [Mbed](https://www.mbed.com/en/platform/mbed-os/)
* [JerryScript](https://github.com/jerryscript-project/jerryscript)

See this project for more information: [mbed-js-x-nucleo-iks01a2-example](https://github.com/STMicroelectronics-CentralLabs/mbed-js-st-examples/tree/master/mbed-js-x-nucleo-iks01a2-example)

## Installation
* Before installing this library, make sure you have a working JavaScript on Mbed project and the project builds for your target device.
Follow [mbed-js-x-nucleo-iks01a2-example](https://github.com/STMicroelectronics-CentralLabs/mbed-js-st-examples/tree/master/mbed-js-x-nucleo-iks01a2-example) to create the project and learn more about using JavaScript on Mbed.

* Install this library using npm (Node package manager) with the following command:
```
cd project_path
npm install mbed-js-st-spi --save
```

## Dependents
Install this library first if using I2C for connecting with the following devices:
* [mbed-js-st-hts221](https://www.npmjs.com/package/mbed-js-st-hts221)
* [mbed-js-st-lps22hb](https://www.npmjs.com/package/mbed-js-st-lps22hb)
* [mbed-js-st-lsm6dsl](https://www.npmjs.com/package/mbed-js-st-lsm6dsl)
* [mbed-js-st-lsm303agr](https://www.npmjs.com/package/mbed-js-st-lsm303agr)

# Usage
```
// To initialize SPI with mosi, miso, sclk pins
var spi = SPI(mosi_pin, miso_pin, sclk_pin);

//sample (Nucleo-F476RG)
var spi = SPI(PB_15, NC, PB_13);

```
