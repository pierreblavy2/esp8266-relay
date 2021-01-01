# esp8266-relay
Smart plug, with en esp8266, a DS3231 RTC, and a relay

# Hardware
* D1mini : Wemos mini D1, with esp8266
* RELAY (here : RelayShield for Wemos D1)
   * Voltage must be >= 240V (here 250V)
   * Amperage must be > load consumption (here 10A)
   * Control and low power must be 5V. Here the control pin is called RELAY_COMM
   * WARNING : Most shields use D1 as RELAY_COMM, which is reserved for the RTC, therefore you need a perfboard to correctly wire the relay instead of directly plugging it on top of the Wemos mini.
* 5VRTC (here DS3231 module, 5V)
   * RTC must be 5V
   * RTC must use I2C for communication
   * RTC must only provide seconds since epoch. Alarm, temperature, memory or calendar are not required.
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
   * The load is controlled trough the relay, that switches on/off its phase
   * The load in NOT protected by the fuse
   * Relay must be chosen accordingly to the load.



# Wires
## LOW POWER
* from D1mini_D1 to RTC_SCL  (I2C)
* from D1mini_D2 to RTC_SDA, (I2C)
* from D1mini_D5 to RELAY_D1 (0=default, 1=toggeled);
* from 220to5_GND to RELAY_GND, D1mini_GND, RTC_GNC
* from 220to5_+5V to RELAY_VCC, D1mini_5V, RTC_VCC

## 220V RELAY
* LIVE to RELAY_COMM
* RELAY_default to LOAD_LIVE
* RELAY_toggeled is not connected

## 220V to 5V
* LIVE    to FUSE_1
* FUSE_2  to 220to5_convertor_AC1
* NEUTRAL to 220to5_convertor_AC2




