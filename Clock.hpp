#ifndef NTP_CLOCK_HPP_123_
#define NTP_CLOCK_HPP_123_

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTClib.h> 
#include <Timezone.h>

//https://github.com/ropg/ezTime

struct Ntp_rtc_clock{

  bool force_update=false;
  bool clock_ok(){return !rtc.lostPower() and !force_update; }
  
  DateTime now(){return rtc.now();}

  bool begin(){return true;}
  

  bool update(){
    if(clock_ok()){return true;}

     //try to get time from ntp
     bool ok = timeClient.update();
     if(!ok){Serial.println("Cannot access to NTP"); return false;}
     
     //set the rtc from ntp time   
     //DateTime dt(ntp_getYear(), ntp_getMonth(), ntp_getDay(), ntp_getHour(), ntp_getMinutes(), ntp_getSeconds() );       
     DateTime dt=timeClient.getEpochTime();

     rtc.adjust(dt);
     Serial.print("RTC ajusted to"); Serial.println(dt.timestamp());
  }
  
  Ntp_rtc_clock():
    rtc(),
    ntpUDP(),
    timeClient(this->ntpUDP, "pool.ntp.org", 0)
  {
    //start rtc
    while (! rtc.begin() ) {
      Serial.println("Couldn't find RTC (missing hardware), waiting 30s");
      Serial.flush();
      delay(30000);  
    }
    
    rtc.disable32K(); //
  }
  
  
  RTC_DS3231 rtc;
  WiFiUDP    ntpUDP;
  NTPClient  timeClient;
  
  /*
  int ntp_getYear() {
    //https://github.com/arduino-libraries/NTPClient/issues/36
    time_t rawtime = timeClient.getEpochTime();
    struct tm * ti;
    ti = localtime (&rawtime);
    int year = ti->tm_year + 1900;
    return year;
  }
  
  
  int ntp_getMonth() {
    time_t rawtime = timeClient.getEpochTime();
    struct tm * ti;
    ti = localtime (&rawtime);
    int month = (ti->tm_mon + 1) < 10 ? 0 + (ti->tm_mon + 1) : (ti->tm_mon + 1);
    
    return month;
  } 
  
  
  int ntp_getDay() {
    time_t rawtime = timeClient.getEpochTime();
    struct tm * ti;
    ti = localtime (&rawtime);
    int d = (ti->tm_mday) < 10 ? 0 + (ti->tm_mday) : (ti->tm_mday);
    return d;
  }

  int ntp_getHour    () {return timeClient.getHours();}
  int ntp_getMinutes () {return timeClient.getMinutes();}
  int ntp_getSeconds () {return timeClient.getSeconds();}
*/


};//end class Clock


#endif   
