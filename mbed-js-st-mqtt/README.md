# mbed-js-mqtt
MQTT library for Javascript for Mbed OS.

## About library
Helper class providing functions for [MQTT](https://os.mbed.com/users/mapellil/code/MQTT) library in JavaScript.

## Requirements
This library is to be used with the following tools:
* [Mbed](https://www.mbed.com/en/platform/mbed-os/)
* [JerryScript](https://github.com/jerryscript-project/jerryscript)

See this project for more information: [mbed-js-x-nucleo-iks01a2-mqtt-example](https://github.com/syed-zeeshan/mbed-js-x-nucleo-iks01a2-mqtt-example)

## Installation
* Before installing this library, make sure you have a working JavaScript on Mbed project and the project builds for your target device.
Follow [mbed-js-x-nucleo-iks01a2-mqtt-example](https://github.com/syed-zeeshan/mbed-js-x-nucleo-iks01a2-mqtt-example) to create the project and learn more about using JavaScript on Mbed.

* Install this library using npm (Node package manager) with the following command:
```
cd project_path
npm install syed-zeeshan/mbed-js-mqtt
```

# Usage
```
// Instantiate HTS221 library 
var mqtt = new MQTT_JS();

// Initialize MQTT
mqtt.init(str_id, str_password, str_url, str_port);

// Subscribe to MQTT broker
mqtt.subscribe(str_topic);

// Set Subscription callback
mqtt.onSubscribe(fn_callback);

// Connect to MQTT broker
mqtt.connect();

// Publish data to MQTT broker
mqtt.publish(str_data);

// Yield data from MQTT broker
mqtt.yield(int_time);

```
 
# Example
```
// Instantiate HTS221 library 
var mqtt = new MQTT_JS();

// Initialize MQTT
mqtt.init('id', 'password', 'url', 'port');

// Subscribe to MQTT broker
mqtt.subscribe('topic');

// Set Subscription callback
mqtt.onSubscribefunction(data) {
    print('MQTT callback result: ' + data);
});

// Connect to MQTT broker
mqtt.connect();

// Publish data to MQTT broker
var data = {
  'key': 'value'
};
if(mqtt.publish(JSON.stringify(data)) == 0){
    print('Published successfully!');
}
else{
    print('Publishing failed!');
}

// Yield data from MQTT broker
mqtt.yield(500); // Wait for 500ms

```
