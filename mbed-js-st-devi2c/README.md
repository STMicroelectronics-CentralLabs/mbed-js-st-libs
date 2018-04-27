# mbed-js-st-devi2c
JavaScript wrappers for DevI2C by STMircroelectronics.

## About library
Helper class providing functions for DevI2C library (part of [X_NUCLEO_COMMON](https://os.mbed.com/teams/ST/code/X_NUCLEO_COMMON/)) in JavaScript.

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
npm install mbed-js-st-devi2c --save
```

## Dependents
Install this library first if using I2C for connecting with the following devices:
* [mbed-js-st-hts221](https://www.npmjs.com/package/mbed-js-st-hts221)
* [mbed-js-st-lps22hb](https://www.npmjs.com/package/mbed-js-st-lps22hb)
* [mbed-js-st-lsm6dsl](https://www.npmjs.com/package/mbed-js-st-lsm6dsl)
* [mbed-js-st-lsm303agr](https://www.npmjs.com/package/mbed-js-st-lsm303agr)

## Usage
```
// Initialize with SDA and SCL pins
var dev_i2c = DevI2C(sda_pin, scl_pin);

// To set the frequency
dev_i2c.frequency(int_hz);

// To read data array from DecI2C bus using ack (1 if acknowledge, 0 otherwise)
dev_i2c.read(ack);

// To read data array from DecI2C bus using address, data_array and len_array
dev_i2c.read(address, data_array, len_array);

// To read data array from DecI2C bus using address, data_array, len_array and bool_repeated
dev_i2c.read(address, data_array, len_array, bool_repeated);

// To write data array to DecI2C bus using single byte
// returns 1 on success
dev_i2c.write(int);

// To write data array to DecI2C bus using slave address, data_array and len_array
//returns 0 on success, non-0 on failure
dev_i2c.write(address_slave, data_array, len_array);

// To write data array to DecI2C bus using slave address, data_array, len_array and bool_repeated
//returns 0 on success, non-0 on failure
dev_i2c.write(address_slave, data_array, len_array, bool_repeated);

// To start the bus
dev_i2c.start();

// To stop the bus
dev_i2c.stop();

```
