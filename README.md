# Project overview
Create a smart "plug", that can be controlled configured and programmed using the wifi. The plus can be connected to an existing wifi, or create its own standalone network as a backup when no connection is available.

The plug is equiped with a RTC, that can be synchronized trough NTP automatically when internet is available, or manually.

This current version controls an air extractor (VMC), and has a default behabiour of switching ON when things get worng. If it's not what you expect, you must edit the code accordingly.

# License
* Since 2021-28-09, the code is published under the [LGPL-3.0](https://www.gnu.org/licenses/lgpl-3.0.txt) license
* The code was previously licensed under GPL-3.0, this license is technically still valid, but as LGPL is less restrictive, please use it.

# Dependancies
* WARNING : the license are the one that were valid when this documentation was written, check the source project to be sur that they are still valid
* AceTime (MIT License) :
    * doc and code : https://github.com/bxparks/AceTime
    * doc: https://www.arduino.cc/reference/en/libraries/acetime/
* Arduino-esp8266 : concerns ESP8266WiFiMulti, ESP8266WiFi, ESP8266WebServer and LittleFS (LGPL-2.1 License)
    * code : https://github.com/esp8266/Arduino
    * doc : https://arduino-esp8266.readthedocs.io/en/latest/index.html
    * doc LittleFS : https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html
* RTCLib (MIT License)
    * code : https://github.com/adafruit/RTClib
* Wire (code in public domain)
    * doc : https://www.arduino.cc/en/reference/wire
* Arduino (LGPL 2.1)
    * code : https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h



# Hardware
* D1mini : Wemos mini D1, with esp8266
* RELAY (here : RelayShield for Wemos D1)
   * Load voltage must be >= 240V (here 250V)
   * Amperage must be > load consumption (here 10A)
   * low power side must be 5V.
   * The pins on the load side (220V) are called RELAY_comm for the common pin, RELAY_toggeled for the pin connected to RELAY_comm when the relay is powred and RELAY_default for the pin connected to RELAY_comm when the relay is not powered.
   * The pins on the low power side (5V) are RELAY_control that toggles the relay on(+5V) and off(0V), RELAY_GND for the ground, and RELAY_5V for the 5V power.
   * WARNING : Most shields use D1 as RELAY_control, which is reserved for the RTC, therefore you need a perfboard to correctly wire the relay instead of directly plugging it on top of the Wemos mini.
* 5VRTC (here DS3231 module, 5V)
   * RTC must be 5V
   * RTC must use I2C for communication
   * RTC must only provide seconds since epoch + powerloss detection. Alarm, temperature, memory or calendar are not required.
   * A coin battery is not required as long as time can be synchronized with NTP.
   * Any RTC with a not to crappy arduino library support does the trick with some extra coding and DS3231 works out of the box
* 220V AC to 5V DC converter (here Hi-Link HLK-5M05)
   * 5V Amperage must be > 0.6A
   * salvaging a phone charger does the trick.
   * The input pins on the 220V side are called : 220to5_AC1 and 220to5_AC2
   * The output pins on the 5V side are called 220to5_+5V and 220to5_GND
* FUSE + HOLDER (here 0.2A, 250V glass fuse)
   * Fuse Amperage should be slightly higer than 0.02A. But it's an uncommonly low value, so just put a small fuse.
   * Voltage must be >= 250V
* A Load that should be controlled (here a VMC)
   * The load is controlled trough the relay, that switches on/off its live. The relay must be chosen accordingly
   * The load in NOT protected by the fuse
   * WARNING : Here we want the load to be ON when something is wrong (ex unsynchronized RTC), if it's not the case you must patch the code and move the cable from RELAY_default to RELAY_toggeled. 



# Wires
![wires](https://github.com/pierreblavy2/esp8266-relay/blob/main/wires.png?raw=true)

## LOW POWER
* from D1mini_D1 to RTC_SCL  (I2C)
* from D1mini_D2 to RTC_SDA, (I2C)
* from D1mini_D5 to RELAY_control
* from 220to5_GND to RELAY_GND, D1mini_GND, RTC_GNC
* from 220to5_+5V to RELAY_VCC, D1mini_5V, RTC_VCC

## 220V RELAY and LOAD
* LIVE to RELAY_COMM
* RELAY_default to LOAD_LIVE
* RELAY_toggeled is not connected
* NEUTRAL to LOAD_NEUTRAL
* GROUNG wire is kept untouched and goes directly to the load

## 220V to 5V
* LIVE    to FUSE_1
* FUSE_2  to 220to5_convertor_AC1
* NEUTRAL to 220to5_convertor_AC2


# Screenshots
![screen1](https://github.com/pierreblavy2/esp8266-relay/blob/main/screenshots/screen1.jpg?raw=true)
![screen2](https://github.com/pierreblavy2/esp8266-relay/blob/main/screenshots/screen2.jpg?raw=true)
![screen3](https://github.com/pierreblavy2/esp8266-relay/blob/main/screenshots/screen3.jpg?raw=true)
![screen4](https://github.com/pierreblavy2/esp8266-relay/blob/main/screenshots/screen4.jpg?raw=true)


