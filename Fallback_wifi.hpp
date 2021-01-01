#ifndef FALLBACK_WIFI_HPP
#define FALLBACK_WIFI_HPP

#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFi.h>


struct Fallback_wifi{

  bool begin(){return true;}
  void update();

  //--- connection mode ---
  enum Mode_e{MODE_DISCONNECT, MODE_AP, MODE_ST};
    //ap : access point (standalone)
    //st : connnected to a station
 
  Mode_e get_mode()const{return mode;}

  //change mode
  bool mode_disconnect();
  bool mode_ap();
  bool mode_st();
  

  //--- soft AP (standalone) ---
  void ap_setAP(const String&ssid, const String pass);
  void ap_cleanAP();
  long unsigned int ap_stay=10*60*1000; //after fallback stay in this mode for this number of milliseconds

  
  //--- station  ---
  //add an accesspoint (can be called multiple time)
  void st_addAP(const String&ssid, const String pass);
  void st_cleanAP();
  long unsigned int st_timeout=10000; //after this timeout, consider that the connection to station is a failure


  //--- debug strings ---
  String str_mode()const;
  String str_mac()const;
  String str_ip()const;
  String str_stationNum()const;
  String str_timeout()const;
  String str_ssid()const;


  //--- internal stuff ---
  private:
  Mode_e mode = MODE_DISCONNECT;
  String ap_ssid   = "";
  String ap_pass = "";
  long unsigned int ap_last_connect=0;
  
  ESP8266WiFiMulti wifiMulti;

};





#endif
