#ifndef RTC_PIERRE_HPP_
#define RTC_PIERRE_HPP_

#include <Arduino.h>
#include <Wire.h>   //https://www.arduino.cc/en/reference/wire
//#include <DS3231.h> //https://github.com/NorthernWidget/DS3231
#include <RTClib.h> //https://github.com/adafruit/RTClib


class Rtc_pierre{
  public:
  typedef DateTime Rtc_time;
  
  RTC_DS3231 rtc;
  Rtc_pierre()=default;
  
  void begin();
  
  void     set_rtc    (const Rtc_time &t){rtc.adjust(t);}
  Rtc_time get_rtc    (){return rtc.now();}
  bool  lostPower(){return rtc.lostPower();}
  float get_temperature(){return rtc.getTemperature();}

};




//idem with AceTime timezone
/* EXAMPLE :
  Rtc_ace rtc;
  rtc.begin();

  //create a ZonedDateTime
  ace_time::ZonedDateTime tt = ace_time::ZonedDateTime::forComponents( 2019, 3, 10, 3, 0, 0, tz_utc);
  
  //set the RTC (tt is internally converted to UTC)
  rtc.set_rtc(tt);

  //get the RTC
  Serial.print("UTC:");   rtc.get_DateTime_utc().printTo(SERIAL_PORT_MONITOR);  Serial.println();
  Serial.print("Local:"); rtc.get_DateTime_local().printTo(SERIAL_PORT_MONITOR);  Serial.println();
 */


#include <AceTime.h>


class String_printer: public Print{
  public:
  String_printer(String &s):string(s){}
  String &string;

/*
  template<typename T>
  size_t write_t(const T&t){
    String tmp = String(t);
    string+=tmp;
    return tmp.length();
  }
 */
  
  size_t write(uint8_t u) override {
    string += char(u);
    return 1;
  }
  
};

inline String to_string(const ace_time::ZonedDateTime &x){
  String r;
  String_printer pr(r);
  x.printTo(pr);
  return r;
}


class Rtc_ace : public Rtc_pierre{
  public:
  Rtc_ace()=default;
  
  typedef DateTime Rtc_time;
  typedef ace_time::TimeZone TimeZone;
  typedef ace_time::ZonedDateTime AceTime; //https://bxparks.github.io/AceTime/html/classace__time_1_1ZonedDateTime.html

  //Local timezone
  void             set_tz(const TimeZone &tz){tz_local=tz;}
  const  TimeZone &get_tz()const             {return tz_local;}
  
  //Get zonned time
  static AceTime tz_convert(const AceTime& from, const TimeZone &tz);
  AceTime get_DateTime_tz   (const TimeZone &tz){return tz_convert(get_DateTime_utc(),tz);}
  AceTime get_DateTime_local(){return tz_convert(get_DateTime_utc(),tz_local);}
  AceTime get_DateTime_utc  ();

  //get timestamp
  ace_time::acetime_t get_unix(){return get_DateTime_utc().toUnixSeconds();}

  //Set RTC from zoned time
  static AceTime             from_rtc(const Rtc_pierre::Rtc_time &t);
  static Rtc_pierre::Rtc_time to_rtc  (const AceTime &t);

  using Rtc_pierre::set_rtc;
  void  set_rtc       (const AceTime &t){Rtc_pierre::set_rtc(to_rtc(t));}
  void  set_rtc_tz    (int16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, const TimeZone &timeZone);
  void  set_rtc_utc   (int16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second){set_rtc_tz(year, month, day, hour, minute, second,tz_utc);}
  void  set_rtc_local (int16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second){set_rtc_tz(year, month, day, hour, minute, second,tz_local);}
  void  set_rtc_unix  (ace_time::acetime_t timestamp); //set from unix timestamp (number of seconds since 1970-01-01)
 
  private:
  static ace_time::BasicZoneProcessor processor_local;
  static ace_time::BasicZoneProcessor processor_UTC;
  static ace_time::TimeZone tz_local;
  static ace_time::TimeZone tz_utc;
};

#endif
