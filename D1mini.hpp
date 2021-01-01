#ifndef D1MINI_HPP_
#define D1MINI_HPP_


//    RST       TX
// 17 A0        RX
// 16 D0        D1 5
// 14 D5        D2 4
// 12 D6        D3 0
// 13 D7        D4 2 LED (low=on)
// 15 D8        G
//    3v3 [usb] 5v





//Cardtype : LOLIN(wemos) D1 RD & mini
//Upload speed 921600
//CPU Frequency : 80MHz
//Flash Size : 4MB, ( FS:2MB OTA:~1019KB)
//Debug port : Disabled
//Debug level : None
//IwIP Variant : v2 Lower memory
//VTables : Flash
//Exceptions : Legacy (new ca return nullptr)
//Erase Flash : Only Sketch
//SSL Support : All SSL Ciphers (most compatible)


#define D1mini_D3 0
//1 is valid but is not an output pin
#define D1mini_D4  2
#define D1mini_LED 2
#define D1mini_LED_ON  LOW
#define D1mini_LED_OFF HIGH
#define D1mini_D2  4
#define D1mini_D1  5
// 6, 7, 8 , 9  //wdt reset
//10 is valid but is not an output pin
//11 wdt reset
#define D1mini_D6 12
#define D1mini_D7 13
#define D1mini_D5 14
#define D1mini_D8 15
#define D1mini_D0 16
#define D1mini_A0 17 //min0; max 1024

//18 is valid but is not an output pin
//19 is valid but is not an output pin

//---I2c ---
#define D1mini_SDA D1mini_D2
#define D1mini_SCL D1mini_D1

// SDA => D2
// SCL => D1



//--- CURSED PINS ---
// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

/*
D0  GPIO16  no interrupt  no PWM or I2C support HIGH at boot
used to wake up from deep sleep
D1  GPIO5 OK  OK  often used as SCL (I2C)
D2  GPIO4 OK  OK  often used as SDA (I2C)
D3  GPIO0 pulled up OK  connected to FLASH button, boot fails if pulled LOW
D4  GPIO2 pulled up OK  HIGH at boot
connected to on-board LED, boot fails if pulled LOW
D5  GPIO14  OK  OK  SPI (SCLK)
D6  GPIO12  OK  OK  SPI (MISO)
D7  GPIO13  OK  OK  SPI (MOSI)
D8  GPIO15  pulled to GND OK  SPI (CS)
Boot fails if pulled HIGH
RX  GPIO3 OK  RX pin  HIGH at boot
TX  GPIO1 TX pin  OK  HIGH at boot
debug output at boot, boot fails if pulled LOW
*/




///--- PIN TEST CODE ---
/*
#define TEST_ME 17

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);  //115200

  pinMode(TEST_ME, OUTPUT); digitalWrite(TEST_ME,LOW);

  Serial.println("END of setup");

}

void loop() {

  Serial.println("---Loop---");



  auto pin_test=[](pin_t pin, String s){
    Serial.print(s);
    Serial.print(" "); 
    Serial.println(pin);

    //blink
    digitalWrite(pin,HIGH);
    delay(250);
    digitalWrite(pin,LOW); 
    delay(250);

    pinMode(pin,INPUT);
    auto d = digitalRead(pin);
    auto a = analogRead(pin);
    Serial.print("digital:"); Serial.println(d);
    Serial.print("analog:"); Serial.println(a);
    pinMode(pin,OUTPUT);

    };
  
  pin_test(TEST_ME,"?");


}
*/

#endif
