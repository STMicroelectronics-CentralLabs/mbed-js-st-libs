# mbed-js-devi2c
JavaScript wrappers for DevI2C by STMircroelectronics.

## About library
Helper class providing functions for DevI2C library (part of [X_NUCLEO_COMMON](https://os.mbed.com/teams/ST/code/X_NUCLEO_COMMON/)) in JavaScript.

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
npm install syed-zeeshan/mbed-js-lsm303agr
```

## Dependents
Install this library first if using I2C for connecting with the following devices:
* [mbed-js-hts221](https://www.github.com/syed-zeeshan/mbed-js-hts221)
* [mbed-js-lps22hb](https://www.github.com/syed-zeeshan/mbed-js-lps22hb)
* [mbed-js-lsm6dsl](https://www.github.com/syed-zeeshan/mbed-js-lsm6dsl)
* [mbed-js-lsm303agr](https://www.github.com/syed-zeeshan/mbed-js-lsm303agr)

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
