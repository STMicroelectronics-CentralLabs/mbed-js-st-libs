## Class

<dl>
<dt><a href="#DevI2C">DevI2C</a></dt>
<dd></dd>
</dl>

## Functions

<dl>
<dt><a href="#frequency">frequency(frequency)</a></dt>
<dd><p>Sets the frequency of the DevI2C bus.</p>
</dd>
<dt><a href="#start">start()</a></dt>
<dd><p>Creates a start condition on the DevI2C bus.</p>
</dd>
<dt><a href="#stop">stop()</a></dt>
<dd><p>Creates a stop condition on the DevI2C bus.</p>
</dd>
<dt><a href="#read">read(acknowledge)</a> ⇒</dt>
<dd><p>Reads from DevI2C bus.</p>
</dd>
<dt><a href="#read">read(address, data, length)</a> ⇒</dt>
<dd><p>Reads from DevI2C bus.</p>
</dd>
<dt><a href="#read">read(address, data, length, repeated)</a> ⇒</dt>
<dd><p>Reads from DevI2C bus.</p>
</dd>
<dt><a href="#write">write(data)</a> ⇒</dt>
<dd><p>Writes to DevI2C bus.</p>
</dd>
<dt><a href="#write">write(address, data, length)</a> ⇒</dt>
<dd><p>Writes to DevI2C bus.</p>
</dd>
<dt><a href="#write">write(address, data, length, repeated)</a> ⇒</dt>
<dd><p>Writes to DevI2C bus.</p>
</dd>
</dl>

<a name="DevI2C"></a>

## DevI2C
**Kind**: global class
<a name="new_DevI2C_new"></a>

### new DevI2C(sda_pin, scl_pin)
Create a new DevI2C instance

**Returns**: <code>object</code> - - A JavaScript object representing the DevI2C bus.

| Param | Type | Description |
| --- | --- | --- |
| sda_pin | <code>number</code> | The SDA pin. |
| scl_pin | <code>number</code> | The SCL pink. |

<a name="frequency"></a>

## frequency(frequency)
Sets the frequency of the DevI2C bus.

**Kind**: global function

| Param | Type | Description |
| --- | --- | --- |
| frequency | <code>number</code> | New DevI2C Frequency |

<a name="start"></a>

## start()
Creates a start condition on the DevI2C bus.

**Kind**: global function
<a name="stop"></a>

## stop()
Creates a stop condition on the DevI2C bus.

**Kind**: global function
<a name="read"></a>

## read(acknowledge) ⇒
Reads from DevI2C bus.

**Kind**: global function
**Returns**: array: Data read from the DevI2C bus

| Param | Type | Description |
| --- | --- | --- |
| acknowledge | <code>number</code> | Indicates if the byte is to be acknowledged (1 => acknowledge) |

<a name="read"></a>

## read(address, data, length) ⇒
Reads from DevI2C bus.

**Kind**: global function
**Returns**: array: Data read from the DevI2C bus

| Param | Type | Description |
| --- | --- | --- |
| address | <code>number</code> | DevI2C address to read from |
| data | <code>array</code> | Array to read into |
| length | <code>number</code> | Length of data to read |

<a name="read"></a>

## read(address, data, length, repeated) ⇒
Reads from DevI2C bus.

**Kind**: global function
**Returns**: array: Data read from the DevI2C bus

| Param | Type | Description |
| --- | --- | --- |
| address | <code>number</code> | DevI2C address to read from |
| data | <code>array</code> | Array to read into |
| length | <code>number</code> | Length of data to read |
| repeated | <code>bool</code> | If true, do not send stop at end. |

<a name="write"></a>

## write(data) ⇒
Writes to DevI2C bus.

**Kind**: global function
**Returns**: 1 on success, 0 on failure

| Param | Type | Description |
| --- | --- | --- |
| data | <code>number</code> | Data byte to write to the DevI2C bus |

<a name="write"></a>

## write(address, data, length) ⇒
Writes to DevI2C bus.

**Kind**: global function
**Returns**: 0 on success, non-0 on failure

| Param | Type | Description |
| --- | --- | --- |
| address | <code>number</code> | 8-bit DevI2C slave address |
| data | <code>array</code> | Array of bytes to send |
| length | <code>number</code> | Length of data to write |

<a name="write"></a>

## write(address, data, length, repeated) ⇒
Writes to DevI2C bus.

**Kind**: global function
**Returns**: 0 on success, non-0 on failure

| Param | Type | Description |
| --- | --- | --- |
| address | <code>number</code> | 8-bit DevI2C slave address |
| data | <code>array</code> | Array of bytes to send |
| length | <code>number</code> | Length of data to write |
| repeated | <code>bool</code> | If true, do not send stop at end. |
