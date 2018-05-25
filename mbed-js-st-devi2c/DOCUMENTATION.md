# [mbed-js-st-devi2c](https://github.com/STMicroelectronics-CentralLabs/mbed-js-st-libs#readme) *1.0.0*

> JavaScript library for DevI2C on Mbed OS


### DEVI2C_JS/DevI2C-js.js


#### DECLARE_CLASS_FUNCTION(frequency) 

DevI2C#frequency (native JavaScript method)




##### Parameters

| Name | Type | Description |  |
| ---- | ---- | ----------- | -------- |
| frequency |  | New DevI2C Frequency | &nbsp; |




##### Returns


- `Void`



#### DECLARE_CLASS_FUNCTION(ack, address, data, length) 

DevI2C#read (native JavaScript method)




##### Parameters

| Name | Type | Description |  |
| ---- | ---- | ----------- | -------- |
| ack |  | indicates if the byte is to be acknowledged (1 => acknowledge) | &nbsp; |
| address |  | DevI2C address to read from | &nbsp; |
| data |  | Array to read into | &nbsp; |
| length |  | Length of data to read | &nbsp; |




##### Returns


-  array: Data read from the DevI2C bus
-  array: Data read from the DevI2C bus



#### DECLARE_CLASS_FUNCTION(data, address, data, length, repeated) 

DevI2C#write (native JavaScript method)




##### Parameters

| Name | Type | Description |  |
| ---- | ---- | ----------- | -------- |
| data |  | Data byte to write to the DevI2C bus | &nbsp; |
| address |  | 8-bit DevI2C slave address | &nbsp; |
| data |  | Array of bytes to send | &nbsp; |
| length |  | Length of data to write | &nbsp; |
| repeated |  | (optional) If true, do not send stop at end. | &nbsp; |




##### Returns


-  1 on success, 0 on failure
-  0 on success, non-0 on failure



#### DECLARE_CLASS_FUNCTION() 

DevI2C#start (native JavaScript method)






##### Returns


- `Void`



#### DECLARE_CLASS_FUNCTION() 

DevI2C#stop (native JavaScript method)






##### Returns


- `Void`



#### DevI2C(sda_pin, scl_pin) 

DevI2C (native JavaScript constructor)




##### Parameters

| Name | Type | Description |  |
| ---- | ---- | ----------- | -------- |
| sda_pin | `number`  | - The SDA pin. | &nbsp; |
| scl_pin | `number`  | - The SCL pink. | &nbsp; |




##### Returns


- `object`  - A JavaScript object representing the DevI2C bus.




*Documentation generated with [doxdox](https://github.com/neogeek/doxdox).*
