# esp8266-relay
Smart plug, with en esp8266, a DS3231 RTC, and a relay

# Hardware
* D1mini : Wemos mini D1, with esp8266
* RELAY (here : RelayShield for Wemos D1)
   * Voltage must be >= 240V (here 250V)
   * Amperage must be > load consumption (here 10A)
   * Control and low power must be 5V. Here the control pin is called RELAY_D1
   * WARNING : Most shields use D1, which is reserved for the RTC, therefore you need a perfboard to correctly wire the relay.
* RTC : DS3231 module, 5V
* 220V to 5 V (here Hi-Link HLK-5M05)
   * 5V Amperage must be > 0.6A
   * salvaging a phone charger does the trick.
* FUSE + HOLDER (here 0.2A glass fuse)
   * Amperage slightly higer than 0.02A, it's really low so put the smalles fuse you've got.
   * >250 V

## LOW POWER WIRES
* from D1mini_D1 to RTC_SCL  (I2C)
* from D1mini_D2 to RTC_SDA, (I2C)
* from D1mini_D5 to RELAY_D1 (0=default, 1=toggeled);
* from ground    to RELAY_GND, D1mini_GND, RTC_GNC
* from +5V       to RELAY_VCC, D1mini_5V, RTC_VCC

## 220V RELAY
* LIVE to RELAY_COMM
* RELAY_default to LOAD_LIVE
* RELAY_toggeled is not connected

## 220V to 5V
* LIVE    to FUSE_1
* FUSE_2  to 220to5_convertor_AC1
* NEUTRAL to 220to5_convertor_AC2




