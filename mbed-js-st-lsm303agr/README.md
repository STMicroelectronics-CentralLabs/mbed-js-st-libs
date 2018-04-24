# mbed-js-lsm303agr
LSM303AGR library wrappers for Javascript on Mbed

## About library
Helper class providing functions for [LSM303AGR](https://os.mbed.com/teams/ST/code/LSM303AGR/) sensor library (part of [X_NUCLEO_IKS01A2](https://os.mbed.com/teams/ST/code/X_NUCLEO_IKS01A2/)) in JavaScript.

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
npm install syed-zeeshan/mbed-js-lsm303agr
```

## Usage
```
/*****************
 * Instantiation *
 *****************/
// Instantiate LSM303AGR library 
var lsm303agr = LSM303AGR_JS();

/******************
 * Initialization *
 ******************/
// Initialize Accelerometer using DevI2C
lsm303agr.init_acc_i2c(dev_i2c);

// Initialize Accelerometer using DevI2C, int1 pin and int2 pin
lsm303agr.init_acc_i2c(dev_i2c, int1_pin, int2_pin);

// Initialize Accelerometer using DevI2C, int1 pin, int2 pin and address
lsm303agr.init_acc_i2c(dev_i2c, int1_pin, int2_pin, address);
        
// Initialize Accelerometer using SPI and CS pin
lsm303agr.init_acc_spi(spi, cs_pin);

// Initialize Accelerometer using SPI, CS pin, int1 pin and int2 pin
lsm303agr.init_acc_spi(spi, cs_pin, int1_pin, int2_pin);
    
// Initialize Magnetometer using DevI2C
lsm303agr.init_mag_i2c(dev_i2c);

// Initialize Magnetometer using DevI2C and int pin
lsm303agr.init_mag_i2c(dev_i2c, int_pin);

// Initialize Magnetometer using DevI2C, int pin and address
lsm303agr.init_mag_i2c(dev_i2c, int_pin, address);
        
// Initialize Magnetometer using SPI and CS pin
lsm303agr.init_mag_i2c(spi, cs_pin);

// Initialize Magnetometer using SPI, CS pin and int pin
lsm303agr.init_mag_i2c(spi, cs_pin, int_pin);

/***********************
 * Reading sensor data *
 ***********************/
// To read accelerometer data (JSON output)
lsm303agr.get_accelerometer_axes();

// To read magnetometer data (JSON output)
lsm303agr.get_magnetometer_axes();

```

## Example using DevI2C (Nucleo-F429ZI)
```
// Initialize DevI2C with SDA and SCL pins
var dev_i2c = DevI2C(D14, D15);

// Instantiate LSM303AGR library 
var lsm303agr = LSM303AGR_JS();

// Initialize LSM303AGR library
lsm303agr.init_acc_i2c(dev_i2c);
lsm303agr.init_mag_i2c(dev_i2c);

// Print sensor data
var acc = lsm303agr.get_accelerometer_axes();
var mag = lsm303agr.get_magnetometer_axes();

print("[Accelerometer]: [" + acc.x + ", " + acc.y + ", " + acc.z + "]");
print("[Magnetometer]: [" + mag.x + ", " + mag.y + ", " + mag.z + "]");
```

## Example using SPI (Nucleo-F476RG)
```
// Initialize SPI with MOSI, MISO, SCLK pins
var spi = SPI(PB_15, NC, PB_13);

// Instantiate LSM303AGR library 
var lsm303agr = LSM303AGR_JS();

// Initialize Accelerometer using SPI and CS pin
lsm303agr.init_acc_spi(spi, PC_4);

// Initialize Magnetometer using SPI
lsm303agr.init_mag_spi(spi, PB_1);

// Print sensor data
var acc = lsm303agr.get_accelerometer_axes();
var mag = lsm303agr.get_magnetometer_axes();

print("[Accelerometer]: [" + acc.x + ", " + acc.y + ", " + acc.z + "]");
print("[Magnetometer]: [" + mag.x + ", " + mag.y + ", " + mag.z + "]");
```
