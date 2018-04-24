# mbed-js-lsm6dsl
LSM6DSL library wrappers for Javascript on Mbed

## About library
Helper class providing functions for [LSM6DSL](https://os.mbed.com/teams/ST/code/LSM6DSL/) sensor library (part of [X_NUCLEO_IKS01A2](https://os.mbed.com/teams/ST/code/X_NUCLEO_IKS01A2/)) in JavaScript.

## Requirements
This library is to be used with the following tools:
* [Mbed](https://www.mbed.com/en/platform/mbed-os/)
* [JerryScript](https://github.com/jerryscript-project/jerryscript)

See this project for more information: [mbed-js-example](https://github.com/ARMmbed/mbed-js-example)

## Dependencies
You need to install dependencies before installing this library.
* If using SPI: [mbed-js-spi](https://github.com/syed-zeeshan/mbed-js-spi)
* If using DevI2C: [mbed-js-devi2c](https://github.com/syed-zeeshan/mbed-js-devi2c)

## Installation
* Before installing this library, make sure you have a working JavaScript on Mbed project and the project builds for your target device.
Follow [mbed-js-example](https://github.com/ARMmbed/mbed-js-example) to create the project and learn more about using JavaScript on Mbed.

* Install this library using npm (Node package manager) with the following command:
```
cd project_path
npm install syed-zeeshan/mbed-js-lsm6dsl
```

## Usage
```
/*****************
 * Instantiation *
 *****************/
// Instantiate LSM6DSL library 
var lsm6dsl = LSM6DSL_JS();

/******************
 * Initialization *
 ******************/
// Initialize using DevI2C
lsm6dsl.init_i2c(dev_i2c);

// Initialize using DevI2C, int1 pin and int2 pin
lsm6dsl.init_i2c(dev_i2c, int1_pin, int2_pin);

// Initialize using DevI2C, int1 pin, int2 pin and address
lsm6dsl.init_i2c(dev_i2c, int1_pin, int2_pin, address);

// Initialize using SPI and CS pin
lsm6dsl.init_spi(spi, cs_pin);

// Initialize using SPI, CS pin, int1 pin, int2 pin and SPI type
lsm6dsl.init_spi(spi, cs_pin, int1_pin, int2_pin, spi_type);

/***********************
 * Reading sensor data *
 ***********************/
// To read accelerometer data (JSON output)
lsm6dsl.get_accelerometer_axes();

// To read gyroscope data (JSON output)
lsm6dsl.get_gyroscope_axes();

```

## Example using DevI2C (Nucleo-F429ZI)
```
// Initialize DevI2C with SDA and SCL pins
var dev_i2c = DevI2C(D14, D15);

// Instantiate LSM6DSL library 
var lsm6dsl = LSM6DSL_JS();

// Initialize LSM6DSL library
lsm6dsl.init_i2c(dev_i2c);

// Print sensor data
var acc = lsm6dsl.get_accelerometer_axes();
var gyr = lsm6dsl.get_gyroscope_axes();

print("[Accelerometer]: [" + acc.x + ", " + acc.y + ", " + acc.z + "]");
print("[Gyroscope]: [" + gyr.x + ", " + gyr.y + ", " + gyr.z + "]");
```

## Example using SPI (Nucleo-F476RG)
```
// Initialize SPI with MOSI, MISO, SCLK pins
var spi = SPI(PB_15, NC, PB_13);

// Instantiate LSM6DSL library 
var lsm6dsl = LSM6DSL_JS();

// Initialize using SPI and CS pin
lsm6dsl.init_spi(spi, PB_12, NC, PA_2, 3);

// Print sensor data
var acc = lsm6dsl.get_accelerometer_axes();
var gyr = lsm6dsl.get_gyroscope_axes();

print("[Accelerometer]: [" + acc.x + ", " + acc.y + ", " + acc.z + "]");
print("[Gyroscope]: [" + gyr.x + ", " + gyr.y + ", " + gyr.z + "]");
```
