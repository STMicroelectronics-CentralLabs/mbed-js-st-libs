# mbed-js-hts221
HTS221 library wrappers for Javascript on Mbed

## About library
Helper class providing functions for [HTS221](https://os.mbed.com/teams/ST/code/HTS221/) sensor library (part of [X_NUCLEO_IKS01A2](https://os.mbed.com/teams/ST/code/X_NUCLEO_IKS01A2/)) in JavaScript.

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
npm install syed-zeeshan/mbed-js-hts221
```

## Usage
```
/*****************
 * Instantiation *
 *****************/
// Instantiate HTS221 library 
var hts221 = HTS221_JS();

/******************
 * Initialization *
 ******************/
// Initialize using DevI2C
hts221.init_i2c(dev_i2c);

// Initialize using DevI2C, address and drdy pin
hts221.init_i2c(dev_i2c, address, drdy_pin);

// Initialize using SPI
hts221.init_spi(spi);

// Initialize using SPI, CS pin and drdy pin
hts221.init_spi(spi, cs_pin, drdy_pin);

/***********************
 * Reading sensor data *
 ***********************/
// To read temperature data (string output)
hts221.get_temperature();

// To read humidity data (string output)
hts221.get_humidity();

```

## Example using DevI2C (Nucleo-F429ZI)
```
// Initialize DevI2C with SDA and SCL pins
var dev_i2c = DevI2C(D14, D15);

// Instantiate HTS221 library 
var hts221 = HTS221_JS();

// Initialize HTS221 library
hts221.init_i2c(dev_i2c);

// Print sensor data
var temp = hts221.get_temperature();
var hum = hts221.get_humidity();

print("[Temperature]: [" + temp + "]");
print("[Humidity]: [" + hum + "]");
```
