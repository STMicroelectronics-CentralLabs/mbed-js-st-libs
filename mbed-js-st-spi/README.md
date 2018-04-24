# mbed-js-spi
JavaScript wrappers for SPI by STMircroelectronics.


## About library
Helper class providing functions for DevSPI library (part of [X_NUCLEO_COMMON](https://os.mbed.com/teams/ST/code/X_NUCLEO_COMMON/)) in JavaScript.

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
npm install syed-zeeshan/mbed-js-spi
```

## Dependents
Install this library first if using I2C for connecting with the following devices:
* [mbed-js-hts221](https://www.github.com/syed-zeeshan/mbed-js-hts221)
* [mbed-js-lps22hb](https://www.github.com/syed-zeeshan/mbed-js-lps22hb)
* [mbed-js-lsm6dsl](https://www.github.com/syed-zeeshan/mbed-js-lsm6dsl)
* [mbed-js-lsm303agr](https://www.github.com/syed-zeeshan/mbed-js-lsm303agr)

# Usage
```
// To initialize SPI with mosi, miso, sclk pins
var spi = SPI(mosi_pin, miso_pin, sclk_pin);

//sample (Nucleo-F476RG)
var spi = SPI(PB_15, NC, PB_13);

```
