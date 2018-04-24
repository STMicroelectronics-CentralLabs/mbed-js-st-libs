# mbed-js-lps22hb
LPS22HB library wrappers for Javascript on Mbed

## About library
Helper class providing functions for [LPS22HB](https://os.mbed.com/teams/ST/code/LPS22HB/) sensor library (part of [X_NUCLEO_IKS01A2](https://os.mbed.com/teams/ST/code/X_NUCLEO_IKS01A2/)) in JavaScript.

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
npm install syed-zeeshan/mbed-js-lps22hb
```

## Usage
```
/*****************
 * Instantiation *
 *****************/
// Instantiate LPS22HB library 
var lps22hb = LPS22HB_JS();

/******************
 * Initialization *
 ******************/
// Initialize using DevI2C
lps22hb.init_i2c(dev_i2c);

// Initialize using DevI2C, address and int pin
lps22hb.init_i2c(dev_i2c, address, int_pin);

// Initialize using SPI and CS pin
lps22hb.init_spi(spi, cs_pin);

// Initialize using SPI, CS pin, int pin and SPI type
lps22hb.init_spi(spi, cs_pin, int_pin, spi_type);

/***********************
 * Reading sensor data *
 ***********************/
// To read temperature data (string output)
lps22hb.get_temperature();

// To read pressure data (string output)
lps22hb.get_pressure();

```

## Example using DevI2C (Nucleo-F429ZI)
```
// Initialize DevI2C with SDA and SCL pins
var dev_i2c = DevI2C(D14, D15);

// Instantiate LPS22HB library 
var lps22hb = LPS22HB_JS();

// Initialize LPS22HB library
lps22hb.init_i2c(dev_i2c);

// Print sensor data
var temp = lps22hb.get_temperature();
var press = lps22hb.get_pressure();

print("[Temperature]: [" + temp + "]");
print("[Pressure]: [" + press + "]");
```

## Example using SPI (Nucleo-F476RG)
```
// Initialize SPI with MOSI, MISO, SCLK pins
var spi = SPI(PB_15, NC, PB_13);

// Instantiate LPS22HB library 
var lps22hb = LPS22HB_JS();

// Initialize using SPI and CS pin
lps22hb.init_spi(spi, PA_3, NC, 3);

// Print sensor data
var temp = lps22hb.get_temperature();
var press = lps22hb.get_pressure();

print("[Temperature]: [" + temp + "]");
print("[Pressure]: [" + press + "]");
```
