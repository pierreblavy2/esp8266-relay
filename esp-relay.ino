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

//SETUP : libraries  
//RTClib       https://github.com/adafruit/RTClib/
//NTPClient    https://lastminuteengineers.com/esp8266-ntp-server-date-time-tutorial/


#include   <ESP8266WebServer.h>

#include "D1mini.hpp"
#define PIN_RELAY D1mini_D5
#define RTC_SDA   D1mini_D2 
#define RTC_SCL   D1mini_D1

#include "Fallback_wifi.hpp"
#include "Rtc_pierre.hpp"
#include "Relay.hpp"
#include "State.hpp"
#include "page.hpp"


#include <NTPClient.h>

//--- WIFI ---
Fallback_wifi fallback_wifi;
void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();
ESP8266WebServer server(80); 

//--- RTC ----
Rtc_ace rtc;

//--- NTP ---
WiFiUDP   ntpUDP;

Relay relay(PIN_RELAY);
State state;

//--- filesystem ---
#include "LittleFS.h"


void setup () {


  relay.begin();

  //Serial
  Serial.begin(9600); delay(500);
  
  //--- filesystem ---
  if(!LittleFS.begin()){ 
    Serial.println("LittleFS ERROR");  
  }else{
        Serial.println("LittleFS OK");  
  }
  
  state.load();


  //=== This code should be run once, to initialise the filesystem ===
  /*
    state.set_wifi_ssid("xxxx");
    state.set_wifi_pass("xxxx");
    LittleFS.format();
    state.make_default();
    state.save();
  */

  

  //--- Time ---
  rtc.begin();
  
  
  //--- WIFI (depends on filesystem) ---
  //fallback_wifi.begin();
  fallback_wifi.st_addAP(state.get_wifi_ssid(), state.get_wifi_pass() );
  fallback_wifi.ap_setAP("VMC_wifi","");
  fallback_wifi.begin();
    
  //--- server (depends on wifi) ---
  server.on        ("/", handleRoot);       // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  server.begin();
  Serial.println("HTTP server started");

}

bool rtc_ok=false;


unsigned long run_once=0;
unsigned long last_time=0;

void update_relay(){
  if(state.is_mode_on()) {relay.switch_on(); return;}
  if(state.is_mode_off()){relay.switch_off(); return;}
  if(state.is_mode_auto() ){
    if( rtc.lostPower() ){relay.switch_on(); Serial.println("RTC error => relay ON"); return;}
    if(run_once>0){relay.switch_on(); Serial.println("run_once"); return;}
    auto hh = rtc.get_DateTime_local().hour();
    if(hh==0 ){if(state.h00==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==1 ){if(state.h01==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==2 ){if(state.h02==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==3 ){if(state.h03==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==4 ){if(state.h04==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==5 ){if(state.h05==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==6 ){if(state.h06==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==7 ){if(state.h07==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==8 ){if(state.h08==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==9 ){if(state.h09==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==10){if(state.h10==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==11){if(state.h11==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==12){if(state.h12==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==13){if(state.h13==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==14){if(state.h14==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==15){if(state.h15==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==16){if(state.h16==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==17){if(state.h17==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==18){if(state.h18==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==19){if(state.h19==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==20){if(state.h20==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==21){if(state.h21==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==22){if(state.h22==0){relay.switch_off();}else{relay.switch_on();} return; }
    if(hh==23){if(state.h00==0){relay.switch_off();}else{relay.switch_on();} return; }


    
  }
  //in doubt (something wrong)
  relay.switch_on();
}


void update_rtc(bool force=false){
  if(rtc.lostPower() or force ){
      Serial.print("RTC is not synched: ");
      NTPClient ntp(ntpUDP, state.get_ntp(), 0, 60000); //ntp.void setPoolServerName(const char* poolServerName);
      ntp.begin();
      bool ntpok = ntp.forceUpdate();
      if(ntpok){
        Serial.println("Synchronizing from NTP");
        auto ntp_epoch = ntp.getEpochTime();
        Serial.print("NTP timestamp: ");Serial.println(ntp_epoch);
        rtc.set_rtc_unix(ntp.getEpochTime());
        Serial.print("Sychronized to "); Serial.println(to_string(rtc.get_DateTime_utc()));
      }else{
         Serial.print("NTP is not available");
      }
  }
}


unsigned char frame_id=0;
void loop () {
  ++frame_id;
  
  unsigned long current_time = millis();
  unsigned long delta = current_time - last_time;
  last_time=current_time;
  if(delta>=run_once){run_once=0;}else{run_once-=delta;}
  

  server.handleClient();
  
  update_rtc();
  update_relay();

  if(frame_id%10==0){
    fallback_wifi.update();
    Serial.println("loop");
    Serial.print("rtc UTC      : "); rtc.get_DateTime_utc().printTo(SERIAL_PORT_MONITOR);  Serial.println();
    Serial.print("rtc Local    : "); rtc.get_DateTime_local().printTo(SERIAL_PORT_MONITOR);  Serial.println();
    Serial.println();
  }
  
  delay(500);


 
}


void debug_GET(){
  //doc: https://techtutorialsx.com/2016/10/22/esp8266-webserver-getting-query-parameters/
  Serial.print("number_of_args:");
  Serial.println(server.args());
  Serial.println("Args:");
  for (int i = 0; i < server.args(); i++) {
    Serial.print(i);Serial.print(":");
    Serial.print( server.argName(i));
    Serial.print("->");
    Serial.println(server.arg(i));
  } 
  Serial.println("end of Args");
}


void handleRoot() {
  Serial.println("serving/");
  debug_GET();

  //--- change state according to args ---
  debug_GET();
  bool wifi_change = false;
  bool ntp_change =false;
  bool ntp_mode;
  String ntp_server;
  String clock_date;
  String clock_time;
  
  if(server.args()>1){
    //note : there is an argument called plain, that contains the full get query
    
    //reset hh
    state.h00=0; state.h01=0; state.h02=0; state.h03=0; state.h04=0; state.h05=0; 
    state.h06=0; state.h07=0; state.h08=0; state.h09=0; state.h10=0; state.h11=0; 
    state.h12=0; state.h13=0; state.h14=0; state.h15=0; state.h16=0; state.h17=0; 
    state.h18=0; state.h19=0; state.h20=0; state.h21=0; state.h22=0; state.h23=0;
    
    for (int i = 0; i < server.args(); i++) {
      const auto & arg_name   = server.argName(i);
      const auto & arg_value  = server.arg(i);
      //Serial.print(arg_name); Serial.print("->"); Serial.println(arg_value);
  
      //wifi ssid and pass 
      if( arg_name=="wifi_ssid")  {
        Serial.println("X");
        if(arg_value==state.get_wifi_ssid()){continue;}//no change
        //change
        state.set_wifi_ssid( arg_value ); 
        wifi_change=true;
        continue;
      }
      
      if( arg_name=="wifi_pass" and arg_value!="" ){
        if(arg_value==state.get_wifi_pass()){continue;}//no change
        //change
        state.set_wifi_pass( arg_value ); 
        wifi_change=true;
        continue;
      }

  
      //program_mode 
      if( arg_name=="mode"){
        if(arg_value=="mode_on"  ){state.set_mode_on();   continue;}
        if(arg_value=="mode_off" ){state.set_mode_off();  continue;}
        if(arg_value=="mode_auto"){state.set_mode_auto(); continue;}
        Serial.print("ERROR : wrong mode, mode=");Serial.println(arg_value);
        continue;
      }
  
      //hours
      if( state.is_hh( arg_name ) ){
        bool b = arg_value=="on";
        state.set_hh(arg_name,b);
      }//end hours

      //once
      if( arg_name=="once"){
        if( arg_value=="once_nochange")  {continue;}
        if( arg_value=="once_0")  {run_once= 0;          continue;}
        if( arg_value=="once_15m"){run_once= 15*60*1000; continue;}
        if( arg_value=="once_30m"){run_once= 30*60*1000; continue;}
        if( arg_value=="once_1h" ){run_once= 60*60*1000; continue;}
        if( arg_value=="once_2h") {run_once=120*60*1000; continue;}
      }

      //clock
      if( arg_name=="ntp_mode"){
        if( arg_value=="ntp_nochange")  {continue;}
        if( arg_value=="ntp_on") {ntp_change=true; ntp_mode=true; }
        if( arg_value=="ntp_off"){ntp_change=true; ntp_mode=false; }
      }
      if( arg_name=="ntp_server"){ntp_server = arg_value;}
      if( arg_name=="date")      {clock_date = arg_value;}
      if( arg_name=="time")      {clock_time = arg_value;}

      
    }//end for

    if(wifi_change){
        //reconnect
        Serial.print("RESET WIFI to "); Serial.println(state.get_wifi_ssid());
        //WiFi.mode(WIFI_OFF);
        fallback_wifi.mode_disconnect();
        fallback_wifi.st_cleanAP();
        fallback_wifi.st_addAP(state.get_wifi_ssid(),state.get_wifi_pass());    
    }

    if(ntp_change){
      if(ntp_mode){
        state.ntp_mode=state.NTP_ON;
        state.set_ntp(ntp_server.c_str());
        update_rtc(true);
      }else{
        state.ntp_mode=state.NTP_OFF;
        //substring index are inclusive, exclusive
        //date->2010-02-01
        //time->15:16
        //index 0123456789
        int16_t yyyy=  int16_t(clock_date.substring(0,4).toInt()); 
        uint8_t MM  =  uint8_t(clock_date.substring(5,7).toInt());
        uint8_t dd  =  uint8_t(clock_date.substring(8,10).toInt());
        uint8_t hh  =  uint8_t(clock_time.substring(0,2).toInt());
        uint8_t mm  =  uint8_t(clock_time.substring(3,5).toInt());
        ace_time::ZonedDateTime x=ace_time::ZonedDateTime::forComponents(yyyy,MM,dd,hh,mm,0, rtc.get_tz() );//localtime
        if(x.isError()){Serial.print("Invalid date and time :"); Serial.print(clock_date);Serial.print(" ");Serial.println(clock_time); }
        else           {  rtc.set_rtc(x); }
      } 
    }

      
    
    state.save();
    update_relay();
    state.print();
  }//end if(server.args()>1)
  
  //--- serve page ---
  Serial.println("serve_page");
  String p = page();

  //--- mode ---
  String once_str;
  if(run_once==0){once_str="Non (0 secondes)";}
  else{
    auto s=run_once/1000;
    auto mm = s/60;
    auto ss = s%60;
    once_str = "$m$ minutes et $s$ secondes";
    once_str.replace("$m$",String(mm));
    once_str.replace("$s$",String(ss));
  }
  
  p.replace("$mode$",state.str_program_mode());
  p.replace("$status_relay$",relay.is_on()?"ON":"OFF");
  p.replace("$status_once$",once_str);

  String checked_mode_on   = "";
  String checked_mode_off  = "";
  String checked_mode_auto = "";
  if(state.program_mode==0){checked_mode_on  = "checked";}
  if(state.program_mode==1){checked_mode_off = "checked";}
  if(state.program_mode==2){checked_mode_auto= "checked";}
  p.replace("$checked_mode_on$",  checked_mode_on);
  p.replace("$checked_mode_off$", checked_mode_off);
  p.replace("$checked_mode_auto$",checked_mode_auto);

  //--- hours ---
  #define MK_HOURS(xxx) if(state.xxx){p.replace("$checked_"#xxx"$","checked");}else{p.replace("$checked_"#xxx"$","");}
  MK_HOURS(h00);MK_HOURS(h01); MK_HOURS(h02);MK_HOURS(h03);MK_HOURS(h04);MK_HOURS(h05);
  MK_HOURS(h06);MK_HOURS(h07); MK_HOURS(h08);MK_HOURS(h09);MK_HOURS(h10);MK_HOURS(h11);
  MK_HOURS(h12);MK_HOURS(h13); MK_HOURS(h14);MK_HOURS(h15);MK_HOURS(h16);MK_HOURS(h17);
  MK_HOURS(h18);MK_HOURS(h19); MK_HOURS(h20);MK_HOURS(h21);MK_HOURS(h22);MK_HOURS(h23);
  #undef MK_HOURS

  //--- wifi ---
  p.replace("$wifi_mode$",        fallback_wifi.str_mode());
  p.replace("$wifi_mac$" ,        fallback_wifi.str_mac());
  p.replace("$wifi_ip$"  ,        fallback_wifi.str_ip());
  p.replace("$wifi_ssid$",        fallback_wifi.str_ssid());
  p.replace("$wifi_stationNum$",  fallback_wifi.str_stationNum());
  p.replace("$wifi_timeout$",     fallback_wifi.str_timeout());
  p.replace("$wifi_pass$",""); //dont't show password in page

  p.replace("$wifi_st_ssid$",state.wifi_ssid);


  //--- ntp ---
  p.replace("$ntp_server$",state.get_ntp());
  p.replace("$ntp_mode$",state.str_ntp_mode());

  



  //--- clock ---
  p.replace("$local_time$",  to_string(rtc.get_DateTime_local() ) );
  p.replace("$utc_time$"  ,  to_string(rtc.get_DateTime_utc()   ) );
  p.replace("$status_rtc$"  ,rtc.lostPower()?"ERREUR : non synchronisée":"OK");
  p.replace("$rtc_temperature$",String(rtc.get_temperature()) );
  
  
  server.sendHeader("Cache-Control"," no-cache");
  server.send(200, "text/html", p);

 
}


void handleNotFound(){
  Serial.println("ERROR 404 => root");
  handleRoot();
  //server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
