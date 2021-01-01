#include "Rtc_pierre.hpp"


ace_time::BasicZoneProcessor Rtc_ace::processor_local;
ace_time::BasicZoneProcessor Rtc_ace::processor_UTC;
ace_time::TimeZone Rtc_ace::tz_local = ace_time::TimeZone::forZoneInfo(&ace_time::zonedb::kZoneEurope_Paris, &processor_local);
ace_time::TimeZone Rtc_ace::tz_utc   = ace_time::TimeZone::forZoneInfo(&ace_time::zonedb::kZoneEtc_UTC     , &processor_UTC);

  

void Rtc_pierre::begin(){
  rtc.begin();
}



//----
Rtc_ace::AceTime Rtc_ace::from_rtc(const Rtc_pierre::Rtc_time &t){
    return AceTime::forComponents( 
      t.year(),   //[2000-2099]
      t.month(),  //[1-12]
      t.day(),    //[1-31]
      t.hour(),   //[0,23]
      t.minute(), //[0,59] 
      t.second(), //[0,59] 
      tz_utc
     );
}

Rtc_ace::Rtc_time Rtc_ace::to_rtc  (const Rtc_ace::AceTime &local_time){
    Rtc_ace::AceTime t = tz_convert(local_time,Rtc_ace::tz_utc);
    return Rtc_pierre::Rtc_time(
      t.year(),   //[yyyy]
      t.month(),  //[1-12]
      t.day(),    //[1-31]
      t.hour(),   //[0,23]
      t.minute(), //[0,59] 
      t.second() //[0,59] 
    );
}



  
auto Rtc_ace::tz_convert(const AceTime& from, const TimeZone &tz)->AceTime{
  return ace_time::ZonedDateTime::forEpochSeconds(from.toEpochSeconds(), tz);
}
  
auto Rtc_ace::get_DateTime_utc()->AceTime{
  Rtc_time r   = this->get_rtc();
  return from_rtc(r);
}


void  Rtc_ace::set_rtc_tz (int16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, const TimeZone &timeZone){
  AceTime a = ace_time::ZonedDateTime::forComponents (year, month, day, hour, minute, second, timeZone);
  set_rtc(a);
}


void  Rtc_ace::set_rtc_unix  (ace_time::acetime_t timestamp){
  AceTime a = ace_time::ZonedDateTime::forUnixSeconds(timestamp,tz_utc );
  set_rtc(a); 
}
