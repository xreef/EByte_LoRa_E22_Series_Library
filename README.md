# A complete tutorial on my site www.mischianti.org

 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: settings and basic usage
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: library
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: configuration
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: fixed transmission and RSSI
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: power saving and sending structured data
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: repeater mode and remote settings
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: WOR microcontroller and Arduino shield
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: WOR microcontroller and WeMos D1 shield
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: WOR microcontroller and esp32 dev v1 shield


# An Arduino UNO shield to simplify the use
![Arduino UNO shield](https://www.mischianti.org/wp-content/uploads/2019/12/ArduinoShieldMountedE32LoRa_min.jpg)

You can order the PCB  [here](https://www.pcbway.com/project/shareproject/LoRa_E32_Series_device_Arduino_shield.html) 

Instruction and assembly video on 6 part of the guide

# An WeMos D1 shield to simplify the use
![Arduino UNO shield](https://www.mischianti.org/wp-content/uploads/2020/01/WeMosD1ShieldMountedE32LoRa_min.jpg)

You can order the PCB  [here](https://www.pcbway.com/project/shareproject/LoRa_E32_Series_device_WeMos_D1_mini_shield_RF_8km_range.html) 

Instruction and assembly video on 6 part of the guide



# LoRa E22 (EBYTE LoRa SX1278/SX1276) series Library for Arduino, esp8266 and esp32-

I create a library to manage EBYTE E22 series of LoRa device, very powerfull, simple and cheap device.

LoRa or Long Range wireless data telemetry is a technology pioneered by Semtech that operates at a lower frequency than NRF24L01 (433 MHz, 868 MHz or 916 MHz agains 2.4 GHz for the NRF24L01) but at thrice the distance (from 4000m to 10000m).

![](https://www.mischianti.org/wp-content/uploads/2020/08/Ebyte-LoRa-E22-device-for-Arduino-esp32-or-esp8266-3-devices-module-SMD-768x439.jpg)

LoRa E22

<p>You can find here <a href="https://s.click.aliexpress.com/e/_dSqbrK5" target="_blank">AliExpress (433MHz 4Km)</a> - <a href="https://s.click.aliexpress.com/e/_dTTkQtn" target="_blank">AliExpress (433MHz 10Km)</a></p>

Please refer to my article to get updated Schema

### Library

You can find my library here.

To download.

Click the DOWNLOADS button in the top right corner, rename the uncompressed folder LoRa_E22.

Check that the LoRa_E22 folder contains LoRa_E22.cpp and LoRa_E22.h.

Place the LoRa_E22 library folder your /libraries/ folder.

You may need to create the libraries subfolder if its your first library.

Restart the IDE.

#### Pinout

![](https://www.mischianti.org/wp-content/uploads/2019/09/sx1278-sx1276-wireless-lora-uart-module-serial-3000m-arduino-433-rf-robotedu-1705-13-robotedu@101.jpg)

E22 



<table class="wp-block-advgb-table advgb-table-frontend is-style-stripes" style="border-collapse:collapse"><thead><tr><th style="background-color:#8ed1fc">Pin No. </th><th style="background-color:#8ed1fc"> Pin item </th><th style="background-color:#8ed1fc"> Pin direction </th><th style="background-color:#8ed1fc"> Pin application </th></tr></thead><tbody><tr class="alt"><td>1</td><td>M0</td><td>Input（weak pull-up）</td><td>Work with M1 &amp; decide the four operating modes.Floating is not allowed, can be ground.</td></tr><tr><td>2</td><td>M1</td><td>Input（weak pull-up）</td><td>Work with M0 &amp; decide the four operating modes.Floating is not allowed, can be ground.</td></tr><tr class="alt"><td>3</td><td>RXD</td><td>Input</td><td>TTL UART inputs, connects to external (MCU, PC) TXD outputpin. Can be configured as open-drain or pull-up input.</td></tr><tr><td>4</td><td>TXD</td><td>Output</td><td>TTL UART outputs, connects to external RXD (MCU, PC) inputpin. Can be configured as open-drain or push-pull output</td></tr><tr class="alt"><td><br>5</td><td><br>AUX</td><td><br>Output</td><td>Per indicare lo stato di funzionamento del modulo e riattivare l’MCU esterno. Durante la procedura di inizializzazione di autocontrollo, il pin emette una bassa tensione. Può essere configurato come uscita open-drain o output push-pull (è consentito non metterlo a terra, ma se hai problemi, ad esempio ti si freeze il dispositivo è preferibile mettere una restistenza di pull-up da 4.7k o meglio collegarlo al dispositivo).</td></tr><tr><td>6</td><td>VCC</td><td><br></td><td style="vertical-align:middle">Power supply 2.3V~5.5V DC</td></tr><tr class="alt"><td>7</td><td>GND</td><td><br></td><td>Ground</td></tr></tbody></table>

As you can see you can set various modes via M0 and M1 pins.


<table class="wp-block-advgb-table advgb-table-frontend is-style-stripes"><thead><tr><th style="background-color:#8ed1fc"><strong>Mode</strong> </th><th style="background-color:#8ed1fc"><strong>M1</strong> </th><th style="background-color:#8ed1fc"><strong>M0</strong> </th><th style="background-color:#8ed1fc"><strong>Explanation</strong> </th></tr></thead><tbody><tr class="alt"><td>Normal</td><td>0</td><td>0</td><td>UART and wireless channel are open, transparent transmission is on (Supports configuration over air via special command)</td></tr><tr><td>WOR Mode</td><td>0</td><td>1</td><td>Can be defined as WOR transmitter and WOR receiver</td></tr><tr class="alt"><td>Configuration mode</td><td>1</td><td>0</td><td>Users can access the register through the serial port to
control the working state of the module</td></tr><tr><td>Deep sleep mode</td><td>1</td><td>1</td><td>Sleep mode</td></tr></tbody></table>

As you can see there are some pins that can be use in a static way, but If you connect It to the library you gain in performance and you can control all mode via software, but we are going to explain better next.

### Fully connected schema

As I already say It’s not important to connect all pin to the output of microcontroller, you can put M0 and M1 pins to HIGH or LOW to get desidered configuration, and  **if you don’t connect AUX the library set a reasonable delay to be sure that the operation is complete**.

#### AUX pin

When transmitting data can be used to wake up external MCU and return HIGH on data transfer finish.

![](https://www.mischianti.org/wp-content/uploads/2019/10/e32auxPinOnTransmission-1024x269.jpg)

LoRa E22 AUX Pin on transmission

When receiving AUX going LOW and return HIGH when buffer is empty.

![](https://www.mischianti.org/wp-content/uploads/2019/10/e32auxPinOnReception-1024x342.jpg)

LoRa e22 AUX pin on reception

It’s also used for self checking to restore normal operation (on power-on and sleep/program mode).

![](https://www.mischianti.org/wp-content/uploads/2019/10/e32auxPinOnSelfCheck-1024x312.jpg)

LoRa e22 AUX pin on self-check

esp8266 connection schema is more simple because It work at the same voltage of logical communications (3.3v).

![](https://www.mischianti.org/wp-content/uploads/2019/10/LoRa_E32-TTL-100_WemosD1_VD_PU_FullyConnected_bb-e1570517387323-768x560.jpg)

LoRa E22 TTL 100 Wemos D1 fully connected

It’s important to add pull-up resistor (4,7Kohm) to get good stability.

<figure class="wp-block-table is-style-stripes"><table><thead><tr class="alt"><th>E22</th><th>esp8266</th></tr></thead><tbody><tr><td>M0</td><td>D7</td></tr><tr class="alt"><td>M1</td><td>D6</td></tr><tr><td>TX</td><td>PIN D2 (PullUP 4,7KΩ)</td></tr><tr class="alt"><td>RX</td><td>PIN D3 (PullUP 4,7KΩ)</td></tr><tr><td>AUX</td><td>PIN D5 (PullUP 4,7KΩ)</td></tr><tr class="alt"><td>VCC</td><td>5V (but work with less power in 3.3v)</td></tr><tr><td>GND</td><td>GND</td></tr><tr class="alt"><td></td><td></td></tr></tbody></table></figure>

Similar connection schema for esp32, but for RX and TX we use RX2 and TX2, because by default esp32 doesn’t have SoftwareSerial but have 3 Serial.

![](https://www.mischianti.org/wp-content/uploads/2020/08/Ebyte-LoRa-E22-device-esp32-dev-kit-v1-breadboard-full-connection-768x668.jpg)

Ebyte LoRa E22 device esp32 dev kit v1 breadboard full connection

<table><thead><tr><th>E22</th><th>esp32</th></tr></thead><tbody><tr class="alt"><td>M0</td><td>D21</td></tr><tr><td>M1</td><td>D19</td></tr><tr class="alt"><td>TX</td><td>PIN RX2 (PullUP 4,7KΩ)</td></tr><tr><td>RX</td><td>PIN TX3 (PullUP 4,7KΩ)</td></tr><tr class="alt"><td>AUX</td><td>PIN D18 (PullUP 4,7KΩ)</td></tr><tr><td>VCC</td><td>5V (but work with less power in 3.3v)</td></tr><tr class="alt"><td>GND</td><td>GND</td></tr><tr><td></td><td></td></tr></tbody></table>

Arduino working voltage is 5v, so we need to add a voltage divider on RX pin M0 and M1 of LoRa module to prevent damage, you can get more information here  [Voltage divider: calculator and application](https://www.mischianti.org/2019/06/15/voltage-divider-calculator-and-application/).

You can use a 2Kohm resistor to GND and 1Kohm from signal than put together on RX.

![](https://www.mischianti.org/wp-content/uploads/2019/10/LoRa_E32-TTL-100_Arduino_VD_PU_FullyConnected_bb-e1570517268668.jpg)

LoRa E22 TTL 100 Arduino fully connected

<table><tbody><tr class="alt"><td>M0</td><td>7 (voltage divider)</td></tr><tr><td>M1</td><td>6 (voltage divider)</td></tr><tr class="alt"><td>TX</td><td>PIN 2 (PullUP 4,7KΩ)</td></tr><tr><td>RX</td><td>PIN 3 (PullUP 4,7KΩ &amp; Voltage divider)</td></tr><tr class="alt"><td>AUX</td><td>PIN 5 (PullUP 4,7KΩ)</td></tr><tr><td>VCC</td><td>5V</td></tr><tr class="alt"><td>GND</td><td>GND</td></tr><tr><td></td><td></td></tr></tbody></table>

## Constructor

I made a set of quite numerous constructors, because we can have more options and situations to manage.

```cpp
LoRa_E22(byte rxPin, byte txPin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);

LoRa_E22(byte rxPin, byte txPin, byte auxPin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);

LoRa_E22(byte rxPin, byte txPin, byte auxPin, byte m0Pin, byte m1Pin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
```

First set of constructor are create to delegate the manage of Serial and other pins to the library.

<ul><li><code>txE22pin</code> and <code>rxE22pin</code> is the pin to connect to UART and they are <strong>mandatory</strong>.</li><li><code>auxPin </code>is a pin that check the operation, transmission and receiving status (we are going to explain better next), that pin <strong>It isn’t mandatory</strong>, if you don’t set It I apply a delay to permit the operation to complete itself (with latency,  i<strong>f you have trouble, like freeze device, you must put a pull-up 4.7k resistor or better connect to the device</strong> ).</li><li><code>m0pin </code>and <code>m1Pin </code>are the pins to change operation MODE (see the table upper), I think <strong>this pins in “production” are going to connect directly HIGH or LOW</strong>, but for test they are usefully to be managed by the library.</li><li><code>bpsRate </code>is the boudrate of SoftwareSerial normally is 9600 (the only baud rate in programmin/sleep mode)</li></ul>

A simple example is

```cpp
#include "LoRa_E22.h"
LoRa_E22 e22ttl100(2, 3); // RX, TX
// LoRa_E22 e22ttl100(2, 3, 5, 6, 7); // RX, TX
```

We can use directly a SoftwareSerial with another constructor

```cpp
LoRa_E22(HardwareSerial* serial, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
LoRa_E22(HardwareSerial* serial, byte auxPin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
LoRa_E22(HardwareSerial* serial, byte auxPin, byte m0Pin, byte m1Pin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
```

The example upper with this constructor can be do like so.

```cpp
#include <SoftwareSerial.h>
#include "LoRa_E22.h"
SoftwareSerial mySerial(2, 3); // RX, TX
LoRa_E22 e22ttl100(mySerial);
// LoRa_E22 e22ttl100(&amp;mySerial, 5, 7, 6);
```

The last set of constructor is to permit to use an HardwareSerial instead of SoftwareSerial.

```cpp
LoRa_E22(SoftwareSerial* serial, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
LoRa_E22(SoftwareSerial* serial, byte auxPin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
LoRa_E22(SoftwareSerial* serial, byte auxPin, byte m0Pin, byte m1Pin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
```

## Begin

The begin command is used to startup Serial and pins in input and output mode.

```cpp
void begin();
```

in execution is

```cpp
// Startup all pins and UART
e22ttl100.begin();
```

### Configuration and information method

There a set of methods for manage configuration and get information of the device.

```cpp
ResponseStructContainer getConfiguration();
ResponseStatus setConfiguration(Configuration configuration, PROGRAM_COMMAND saveType = WRITE_CFG_PWR_DWN_LOSE);
ResponseStructContainer getModuleInformation();
void printParameters(struct Configuration configuration);
```

#### Response container

To simplify the manage of response I create a set of container, for me very usefully to manage errors and return generic data.

##### ResponseStatus

This is a status container and have 2 simple entry point, with this you can get the status code and the description of status code

```cpp
Serial.println(c.getResponseDescription()); // Description of code
Serial.println(c.code); // 1 if Success
```

The code are

```cpp
SUCCESS = 1,
ERR_E22_UNKNOWN,
ERR_E22_NOT_SUPPORT,
ERR_E22_NOT_IMPLEMENT,
ERR_E22_NOT_INITIAL,
ERR_E22_INVALID_PARAM,
ERR_E22_DATA_SIZE_NOT_MATCH,
ERR_E22_BUF_TOO_SMALL,
ERR_E22_TIMEOUT,
ERR_E22_HARDWARE,
ERR_E22_HEAD_NOT_RECOGNIZED
```

##### ResponseContainer

This container is created to manage String response and have 2 entry point.

`data` with the string returned from message and  `status` an instance of  `RepsonseStatus`.

```cpp
ResponseContainer rs = e22ttl.receiveMessage();
String message = rs.data;
Serial.println(rs.status.getResponseDescription());
Serial.println(message);
```

##### ResponseStructContainer

This is the more “complex” container, I use this to manage structure, It has the same entry point of ResponseContainer but data is a void pointer to manage complex structure.

```cpp
ResponseStructContainer c;
c = e22ttl100.getConfiguration();
// It's important get configuration pointer before all other operation
Configuration configuration = *(Configuration*) c.data;
Serial.println(c.status.getResponseDescription());
Serial.println(c.status.code);
c.close();
```

#### getConfiguration and setConfiguration

The first method is getConfiguration, you can use It to retrive all data stored on device.

```cpp
ResponseStructContainer getConfiguration();
```

Here an usage example.

```cpp
ResponseStructContainer c;
c = e22ttl100.getConfiguration();
// It's important get configuration pointer before all other operation
Configuration configuration = *(Configuration*) c.data;
Serial.println(c.status.getResponseDescription());
Serial.println(c.status.code);
Serial.println(configuration.SPED.getUARTBaudRate());
c.close();
```

![Get configuration](https://www.mischianti.org/wp-content/uploads/2019/12/E32_request_configuration_logic_analyzer-1024x319.jpg)

Structure of configuration have all data of settings, and I add a series of function to get all description of single data.

```cpp
configuration.ADDL = 0x03; // First part of address
configuration.ADDH = 0x00; // Second part
configuration.NETID = 0x00; // NETID used for repeater function
 
configuration.CHAN = 23; // Communication channel
 
configuration.SPED.uartBaudRate = UART_BPS_9600; // Serial baud rate
configuration.SPED.airDataRate = AIR_DATA_RATE_010_24; // Air baud rate
configuration.SPED.uartParity = MODE_00_8N1; // Parity bit
 
configuration.OPTION.subPacketSetting = SPS_240_00; // Packet size
configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED; // Need to send special command
configuration.OPTION.transmissionPower = POWER_22; // Device power
 
configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED; // Enable RSSI info
configuration.TRANSMISSION_MODE.fixedTransmission = FT_TRANSPARENT_TRANSMISSION; // Transmission type
configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED; // Enable repeater mode
configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED; // Check interference
configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER; // Enable WOR mode
configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011; // WOR timing
```

You have the equivalent function to get all description:

```cpp
DEBUG_PRINT(F("HEAD : "));  DEBUG_PRINT(configuration.COMMAND, HEX);DEBUG_PRINT(" ");DEBUG_PRINT(configuration.STARTING_ADDRESS, HEX);DEBUG_PRINT(" ");DEBUG_PRINTLN(configuration.LENGHT, HEX);
DEBUG_PRINTLN(F(" "));
DEBUG_PRINT(F("AddH : "));  DEBUG_PRINTLN(configuration.ADDH, HEX);
DEBUG_PRINT(F("AddL : "));  DEBUG_PRINTLN(configuration.ADDL, HEX);
DEBUG_PRINT(F("NetID : "));  DEBUG_PRINTLN(configuration.NETID, HEX);
DEBUG_PRINTLN(F(" "));
DEBUG_PRINT(F("Chan : "));  DEBUG_PRINT(configuration.CHAN, DEC); DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.getChannelDescription());
DEBUG_PRINTLN(F(" "));
DEBUG_PRINT(F("SpeedParityBit     : "));  DEBUG_PRINT(configuration.SPED.uartParity, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.SPED.getUARTParityDescription());
DEBUG_PRINT(F("SpeedUARTDatte     : "));  DEBUG_PRINT(configuration.SPED.uartBaudRate, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.SPED.getUARTBaudRateDescription());
DEBUG_PRINT(F("SpeedAirDataRate   : "));  DEBUG_PRINT(configuration.SPED.airDataRate, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.SPED.getAirDataRateDescription());
DEBUG_PRINTLN(F(" "));
DEBUG_PRINT(F("OptionSubPacketSett: "));  DEBUG_PRINT(configuration.OPTION.subPacketSetting, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.OPTION.getSubPacketSetting());
DEBUG_PRINT(F("OptionTranPower    : "));  DEBUG_PRINT(configuration.OPTION.transmissionPower, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.OPTION.getTransmissionPowerDescription());
DEBUG_PRINT(F("OptionRSSIAmbientNo: "));  DEBUG_PRINT(configuration.OPTION.RSSIAmbientNoise, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.OPTION.getRSSIAmbientNoiseEnable());
DEBUG_PRINTLN(F(" "));
DEBUG_PRINT(F("TransModeWORPeriod : "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.WORPeriod, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getWORPeriodByParamsDescription());
DEBUG_PRINT(F("TransModeTransContr: "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.WORTransceiverControl, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getWORTransceiverControlDescription());
DEBUG_PRINT(F("TransModeEnableLBT : "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.enableLBT, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getLBTEnableByteDescription());
DEBUG_PRINT(F("TransModeEnableRSSI: "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.enableRSSI, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getRSSIEnableByteDescription());
DEBUG_PRINT(F("TransModeEnabRepeat: "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.enableRepeater, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getRepeaterModeEnableByteDescription());
DEBUG_PRINT(F("TransModeFixedTrans: "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.fixedTransmission, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getFixedTransmissionDescription());
```

At same way setConfiguration want a configuration strucutre, so I think the better way to manage configuration is to retrieve the current one, apply the only change you need and set It again.

```cpp
ResponseStatus setConfiguration(Configuration configuration, PROGRAM_COMMAND saveType = WRITE_CFG_PWR_DWN_LOSE);
```

`configuration` is the strucutre previsiouly show,  `saveType` permit to you to choiche if the change become permanently of only for the current session.

```cpp
ResponseStructContainer c;
c = e32ttl100.getConfiguration();
// It's important get configuration pointer before all other operation
Configuration configuration = *(Configuration*) c.data;
Serial.println(c.status.getResponseDescription());
Serial.println(c.status.code);
 
printParameters(configuration);
configuration.ADDL = 0x03; // First part of address
configuration.ADDH = 0x00; // Second part
configuration.NETID = 0x00; // NETID used for repeater function
 
configuration.CHAN = 23; // Communication channel
 
configuration.SPED.uartBaudRate = UART_BPS_9600; // Serial baud rate
configuration.SPED.airDataRate = AIR_DATA_RATE_010_24; // Air baud rate
configuration.SPED.uartParity = MODE_00_8N1; // Parity bit
 
configuration.OPTION.subPacketSetting = SPS_240_00; // Packet size
configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED; // Need to send special command
configuration.OPTION.transmissionPower = POWER_22; // Device power
 
configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED; // Enable RSSI info
configuration.TRANSMISSION_MODE.fixedTransmission = FT_TRANSPARENT_TRANSMISSION; // Transmission type
configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED; // Enable repeater mode
configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED; // Check interference
configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER; // Enable WOR mode
configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011; // WOR timing
 
// Set configuration changed and set to not hold the configuration
ResponseStatus rs = e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_LOSE);
Serial.println(rs.getResponseDescription());
Serial.println(rs.code);
printParameters(configuration);
c.close()
```

The parameter all all managed as constant:

#### Basic configuration option

<table class="wp-block-advgb-table advgb-table-frontend"><tbody><tr class="alt"><td style="background-color:#eeeeee">ADDH</td><td>High address byte of module (the default 00H)</td><td>00H-FFH</td></tr><tr><td style="background-color:#eeeeee">ADDL</td><td>Low address byte of module (the default 00H)</td><td>00H-FFH</td></tr><tr class="alt"><td style="background-color:#eeeeee">SPED</td><td>Information about data rate parity bit and Air data rate</td><td></td></tr><tr><td style="background-color:#eeeeee">CHAN</td><td>Communication channel（410M + CHAN*1M）, default 17H (433MHz), <strong>valid only for 433MHz device</strong> chek below to check the correct frequency of your device</td><td>00H-1FH</td></tr><tr class="alt"><td style="background-color:#eeeeee">OPTION</td><td>Type of transmission, packet size, allow special message</td><td></td></tr><tr><td style="background-color:#eeeeee">TRANSMISSION_MODE</td><td>A lot of parameter that specify the transmission modality</td><td></td></tr></tbody></table>

OPTION

Type of transmission, pull-up settings, wake-up time, FEC, Transmission power

#### SPED detail

UART Parity bit:  _UART mode can be different between communication parties_

<table class="wp-block-advgb-table advgb-table-frontend"><tbody><tr class="alt"><td style="background-color:#8ed1fc">4</td><td style="background-color:#8ed1fc">3</td><td style="background-color:#8ed1fc">UART parity bit</td><td style="background-color:#fcb900">Constant value</td></tr><tr><td>0</td><td>0</td><td>8N1 (default)</td><td>MODE_00_8N1</td></tr><tr class="alt"><td>0</td><td>1</td><td>8O1</td><td>MODE_01_8O1</td></tr><tr><td>1</td><td>0</td><td>8 E1</td><td>MODE_10_8E1</td></tr><tr class="alt"><td>1</td><td>1</td><td>8N1 (equal to 00)</td><td>MODE_11_8N1</td></tr></tbody></table>

UART baud rate: UART baud rate can be different between communication parties, The UART baud rate has nothing to do with wireless transmission parameters & won’t affect the wireless transmit / receive features.

<table class="wp-block-advgb-table advgb-table-frontend"><tbody><tr><td style="background-color:#8ed1fc">7</td><td style="background-color:#8ed1fc">6</td><td style="background-color:#8ed1fc">5</td><td style="background-color:#8ed1fc">TTL UART baud rate（bps）</td><td style="background-color:#fcb900"> Constant value </td></tr><tr class="alt"><td>0</td><td>0</td><td>0</td><td>1200</td><td>UART_BPS_1200</td></tr><tr><td>0</td><td>0</td><td>1</td><td>2400</td><td>UART_BPS_2400</td></tr><tr class="alt"><td>0</td><td>1</td><td>0</td><td>4800</td><td>UART_BPS_4800</td></tr><tr><td>0</td><td>1</td><td>1</td><td>9600 (default)</td><td>UART_BPS_9600</td></tr><tr class="alt"><td>1</td><td>0</td><td>0</td><td>19200</td><td>UART_BPS_19200</td></tr><tr><td>1</td><td>0</td><td>1</td><td>38400</td><td>UART_BPS_38400</td></tr><tr class="alt"><td>1</td><td>1</td><td>0</td><td>57600</td><td>UART_BPS_57600</td></tr><tr><td>1</td><td>1</td><td>1</td><td>115200</td><td>UART_BPS_115200</td></tr></tbody></table>

Air data rate: The lower the air data rate, the longer the transmitting distance, better anti- interference performance and longer transmitting time, The air data rate must keep the same for both communication parties.

<table class="wp-block-advgb-table advgb-table-frontend"><tbody><tr class="alt"><td style="background-color:#8ed1fc">2</td><td style="background-color:#8ed1fc">1</td><td style="background-color:#8ed1fc">0</td><td style="background-color:#8ed1fc">Air data rate（bps）</td><td style="background-color:#fcb900"> Constant value </td></tr><tr><td>0</td><td>0</td><td>0</td><td>0.3k</td><td>AIR_DATA_RATE_000_03</td></tr><tr class="alt"><td>0</td><td>0</td><td>1</td><td>1.2k</td><td>AIR_DATA_RATE_001_12</td></tr><tr><td>0</td><td>1</td><td>0</td><td>2.4k (default)</td><td>AIR_DATA_RATE_010_24</td></tr><tr class="alt"><td>0</td><td>1</td><td>1</td><td>4.8k</td><td>AIR_DATA_RATE_011_48</td></tr><tr><td>1</td><td>0</td><td>0</td><td>9.6k</td><td>AIR_DATA_RATE_100_96</td></tr><tr class="alt"><td>1</td><td>0</td><td>1</td><td>19.2k</td><td>AIR_DATA_RATE_101_192</td></tr><tr><td>1</td><td>1</td><td>0</td><td>38.4k</td><td>AIR_DATA_RATE_110_384</td></tr><tr class="alt"><td>1</td><td>1</td><td>1</td><td>62.5k</td><td>AIR_DATA_RATE_111_625</td></tr></tbody></table>

#### OPTION detail

####Sub packet setting

This is the max lenght of the packet.

When the data is smaller than the sub packet length, the serial output of the receiving end is an uninterrupted continuous output. When the data is larger than the sub packet length, the receiving end serial port will output the sub packet.

<table class="wp-block-advgb-table advgb-table-frontend"><tbody><tr><td style="background-color:#8ed1fc">7</td><td style="background-color:#8ed1fc">6</td><td style="background-color:#8ed1fc">Packet size</td><td style="background-color:#fcb900">  Constant value  </td></tr><tr class="alt"><td>0</td><td>0</td><td>240bytes (default)</td><td>SPS_240_00</td></tr><tr><td>0</td><td>1</td><td>128bytes</td><td>SPS_128_01</td></tr><tr class="alt"><td>1</td><td>0</td><td>64bytes</td><td>SPS_064_10</td></tr><tr><td>1</td><td>1</td><td>32bytes</td><td>SPS_032_11</td></tr></tbody></table>

####RSSI Ambient noise enable

This command can enable/disable the management type of RSSI, It’s important to manage the remote configuration, pay attention isn’t the RSSI parameter in the message.

When enabled, the C0 C1 C2 C3 command can be sent in the transmitting mode or WOR transmitting mode to read the register. Register 0x00: Current ambient noise rssi Register 0X01: rssi when the data was received last time.

<table class="wp-block-advgb-table advgb-table-frontend"><tbody><tr class="alt"><td style="background-color:#8ed1fc">5</td><td style="background-color:#8ed1fc">RSSI Ambient noise enable</td><td style="background-color:#fcb900"> Constant value </td></tr><tr><td>0</td><td>Enable</td><td>RSSI_AMBIENT_NOISE_ENABLED</td></tr><tr class="alt"><td>1</td><td>Disable (default)</td><td>RSSI_AMBIENT_NOISE_DISABLED</td></tr></tbody></table>

####Transmission power

You can change this set of constant by apply a define like so:

```cpp
#define E22_22 // default value without set 
#define E22_30
```

You can configure Channel frequency olso with this define:

```cpp
// One of

#define FREQUENCY_433
#define FREQUENCY_170
#define FREQUENCY_470
#define FREQUENCY_868
#define FREQUENCY_915
```

### TRANSMISSION_MODE Detail

####Enable RSSI

When enabled, the module receives wireless data and it will follow an RSSI strength byte after output via the serial port TXD

####Transmission type

Transmission mode: in fixed transmission mode, the first three bytes of each user’s data frame can be used as high/low address and channel. The module changes its address and channel when transmit. And it will revert to original setting after complete the process.

####Enable repeater function

####Monitor data before transmission

When enabled, wireless data will be monitored before it is transmitted, which can avoid interference to a certain extent, but may cause data delay.

####WOR

WOR transmitter: the module receiving and transmitting functions are turned on, and a wake-up code is added when transmitting data. Receiving is turned on.

WOR receiver: the module is unable to transmit data and works in WOR monitoring mode. The monitoring period is as follows (WOR cycle), which can save a lot of power.

####WOR cycle

If WOR is transmitting: after the WOR receiver receives the wireless data and outputs it through the serial port, it will wait for 1000ms before entering the WOR again. Users can input the serial port data and return it via the wireless during this period. Each serial byte will be refreshed for 1000ms. Users must transmit the first byte within 1000ms.

 - Period T = (1 + WOR) * 500ms, maximum 4000ms, minimum 500ms
 - The longer the WOR monitoring interval period, the lower the average power consumption, but
the greater the data delay
 - Both the transmitter and the receiver must be the same (very important).



### Send receive message

First we must introduce a simple but usefully method to check if something is in the receiving buffer

```cpp
int available();
```

It’s simply return how many bytes you have in the current stream.

#### Normal transmission mode

Normal/Transparent transmission mode is used to send messages to all device with same address and channel.

![](https://www.mischianti.org/wp-content/uploads/2019/10/LoRa_E32_transmittingScenarios.jpg)

LoRa E22 transmitting scenarios, lines are channels

There are a lot of method to send/receive message, we are going to explain in detail:

```cpp
ResponseStatus sendMessage(const String message);
```

```cpp
ResponseContainer receiveMessage();
```

First method is sendMessage and is used to send a String to a device in  **Normal mode**.

```cpp
ResponseStatus rs = e22ttl.sendMessage("Prova");
Serial.println(rs.getResponseDescription());
```

The other device simply do on the loop


```cpp
if (e22ttl.available() > 1){
ResponseContainer rs = e22ttl.receiveMessage();
String message = rs.data;` `// First ever get the data
Serial.println(rs.status.getResponseDescription());
Serial.println(message);
}
```

#### Manage structure

If you want send a complex strucuture you can use this method


```cpp
ResponseStatus sendMessage(const void *message, const uint8_t size);

ResponseStructContainer receiveMessage(const uint8_t size);
```

It’s used to send strucutre, for example:

```cpp
struct Messaggione {

char type[5];

char message[8];

bool mitico;

};

struct Messaggione messaggione = {"TEMP", "Peple", true};

ResponseStatus rs = e22ttl.sendMessage(&amp;messaggione, sizeof(Messaggione));

Serial.println(rs.getResponseDescription());
```

and the other side you can receive the message so

```cpp
ResponseStructContainer rsc = e22ttl.receiveMessage(sizeof(Messaggione));

struct Messaggione messaggione = *(Messaggione*) rsc.data;

Serial.println(messaggione.message);

Serial.println(messaggione.mitico);
```

##### Read partial strucure

If you want read first part of the message to manage more type of strucutre you can use this method.


```cpp
ResponseContainer receiveInitialMessage(const uint8_t size);
```

I create It to receive a string with type or other to identify the strucuture to load.

```cpp
struct Messaggione { // Partial strucutre without type

char message[8];

bool mitico;

};

char type[5]; // first part of structure

ResponseContainer rs = e22ttl.receiveInitialMessage(sizeof(type));

// Put string in a char array (not needed)

memcpy ( type, rs.data.c_str(), sizeof(type) );

Serial.println("READ TYPE: ");

Serial.println(rs.status.getResponseDescription());

Serial.println(type);

// Read the rest of structure

ResponseStructContainer rsc = e22ttl.receiveMessage(sizeof(Messaggione));

struct Messaggione messaggione = *(Messaggione*) rsc.data;
```

#### Fixed mode instead of normal mode

At same manner I create a set of method to use with fixed transmission

#### Fixed transmission

**You need to change only the sending method, because the destination device don’t receive the preamble with Address and Channel.**

So for String message you have

```cpp
ResponseStatus sendFixedMessage(byte ADDL, byte ADDH, byte CHAN, const String message);

ResponseStatus sendBroadcastFixedMessage(byte CHAN, const String message);
```

and for structure you have

```cpp
ResponseStatus sendFixedMessage(byte ADDL, byte ADDH, byte CHAN, const void *message, const uint8_t size);

ResponseStatus sendBroadcastFixedMessage(byte CHAN, const void *message, const uint8_t size );
```

Here a simple example

```cpp
ResponseStatus rs = e22ttl.sendFixedMessage(0, 0, 0x17, &amp;messaggione, sizeof(Messaggione));

// ResponseStatus rs = e22ttl.sendFixedMessage(0, 0, 0x17, "Ciao");
```

Fixed transmission have more scenarios

![](https://www.mischianti.org/wp-content/uploads/2019/10/LoRa_E32_transmittingScenarios.jpg)

LoRa E22 transmitting scenarios, lines are channels

If you send to a specific device (second scenarios Fixed transmission) you must add ADDL, ADDH and CHAN to identify It directly.

```cpp
ResponseStatus rs = e22ttl.sendFixedMessage(2, 2, 0x17, "Message to a device");
```

If you want send a message to all device in a specified Channel you can use this method.

```cpp
ResponseStatus rs = e22ttl.sendBroadcastFixedMessage(0x17, "Message to a devices of a channel");
```

If you want receive all broadcast message in the network you must set your  `ADDH` and  `ADDL` with  `BROADCAST_ADDRESS`.

```cpp
ResponseStructContainer c;

c = e22ttl100.getConfiguration();

// It's important get configuration pointer before all other operation

Configuration configuration = *(Configuration*) c.data;

Serial.println(c.status.getResponseDescription());

Serial.println(c.status.code);

printParameters(configuration);

configuration.ADDL = BROADCAST_ADDRESS;

configuration.ADDH = BROADCAST_ADDRESS;

// Set configuration changed and set to not hold the configuration

ResponseStatus rs = e22ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_LOSE);

Serial.println(rs.getResponseDescription());

Serial.println(rs.code);

printParameters(configuration);
c.close();
```

###Wireless configuration

This device support wireless configuration with sepecial command, but seems not work, i ask to EBYTE but no response received.

I implement a command that send the packet in the correct way (tested with logic analizer) but seems not work.


 
By the way, first you muset activate RSSI noise environment, than you can use the command like so:

```cpp
    Configuration configuration;
 
  configuration.ADDL = 0x13;
  configuration.ADDH = 0x13;
  configuration.NETID = 0x00;
 
  configuration.CHAN = 23;
 
  configuration.SPED.uartBaudRate = UART_BPS_9600;
  configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
  configuration.SPED.uartParity = MODE_00_8N1;
 
  configuration.OPTION.subPacketSetting = SPS_240_00;
  configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
  configuration.OPTION.transmissionPower = POWER_22;
 
  configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
  configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
  configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
  configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
  configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_TRANSMITTER;
  configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
 ```
 

## Thanks

Now you have all information to do your work, but I think It’s important to show some realistic examples to undestand better all the possibility.

 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: settings and basic usage
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: library
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: configuration
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: fixed transmission and RSSI
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: power saving and sending structured data
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: repeater mode and remote settings
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: WOR microcontroller and Arduino shield
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: WOR microcontroller and WeMos D1 shield
 - Ebyte LoRa E22 device for Arduino, esp32 or esp8266: WOR microcontroller and esp32 dev v1 shield

-
