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
NTPClient ntp(ntpUDP, "europe.pool.ntp.org", 0, 60000); //ntp.void setPoolServerName(const char* poolServerName);

Relay relay(PIN_RELAY);
State state;






void setup () {
  relay.begin();

  //Serial
  Serial.begin(9600); delay(500);
  
  //--- SPIFFS, State ---
  if(!SPIFFS.begin()){ Serial.println("SPIFF begin error"); }
  state.load();
  
  //--- Time ---
  rtc.begin();
  ntp.begin();
  

  //This code should be run once, to initialise the SPIF state file with correct values.
  //AS SPIF is persistant, you should remove this code from your final build
  #ifdef INIT_SPIFF
    state.begin();
    { File f = SPIFFS.open("config", "w");
      state.save(f);
      f.close();
    }
  #endif
  
  //--- WIFI (depends on filesystem) ---
  //fallback_wifi.st_addAP("Livebox-B906", "A4rgYpfYfhHSbzcc4T");
  //fallback_wifi.ap_setAP("VMC_wifi","");
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


void update_relay(){

  //relay state 
  if(state.is_mode_on()) {relay.switch_on();}
  if(state.is_mode_off()){relay.switch_off();}
  //TODO mode_auto here
  
}

void loop () {
  Serial.println("loop");
  fallback_wifi.update();
  server.handleClient();

  update_relay();

  if(rtc.lostPower() ){
      Serial.print("RTC is not synched: ");
      bool ntpok = ntp.forceUpdate();
      if(ntpok){
        Serial.println("Synchronizing from NTP");
        auto ntp_epoch = ntp.getEpochTime();
        Serial.print("NTP timestamp: ");Serial.println(ntp_epoch);
        rtc.set_rtc_unix(ntp.getEpochTime());
      }else{
         Serial.print("NTP is not available");
      }

  }
  

  
 
  Serial.print("rtc UTC      : "); rtc.get_DateTime_utc().printTo(SERIAL_PORT_MONITOR);  Serial.println();
  Serial.print("rtc Local    : "); rtc.get_DateTime_local().printTo(SERIAL_PORT_MONITOR);  Serial.println();
  Serial.println();
  
  delay(5000);


 
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

  //--- change state according to args ---
  debug_GET();
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
      if( arg_name=="wifi_ssid")                   {state.set_wifi_ssid( arg_value ); continue;}
      if( arg_name=="wifi_pass" and arg_value!="" ){state.set_wifi_pass( arg_value ); continue;}
  
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
      
    }//end for
    
    state.save();
    update_relay();
    state.print();
  }//end if(server.args()>1)
  
  //--- serve page ---
  Serial.println("serve_page");
  String p = page();

  //--- mode ---
  p.replace("$mode$",state.str_program_mode());
  p.replace("$status_relay$",relay.is_on()?"ON":"OFF");
  p.replace("$status_once$","???");

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
    

  //--- clock ---
  p.replace("$local_time$",to_string(rtc.get_DateTime_local() ) );
  p.replace("$utc_time$"  ,to_string(rtc.get_DateTime_utc()   ) );
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
