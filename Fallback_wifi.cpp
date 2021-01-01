#include "Fallback_wifi.hpp"


//=== soft AP config (standalone) ===

void Fallback_wifi::ap_setAP(const String&ssid, const String pass){
   ap_ssid=ssid; 
   ap_pass=pass;
}

void Fallback_wifi::ap_cleanAP(){
   ap_ssid=""; 
   ap_pass="";
}

//=== connected to a station config ===

void Fallback_wifi::st_addAP(const String&ssid, const String pass){
  wifiMulti.addAP(ssid.c_str() ,pass.c_str() );
}


void Fallback_wifi::st_cleanAP(){
  wifiMulti.cleanAPlist();
}
  
  
  

//=== change mode ===

bool Fallback_wifi::mode_disconnect(){
    WiFi.disconnect(true);
    mode=Mode_e::MODE_DISCONNECT;
    return true;
}
  
  
bool Fallback_wifi::mode_ap(){
	Serial.print("Create Acces point...");
	bool ok = WiFi.softAP(ap_ssid,ap_pass);
	if(!ok){Serial.println("ERROR AP"); mode=MODE_DISCONNECT; return false;}
	Serial.print("SoftAP IP address: ");  Serial.println(WiFi.softAPIP());

	ap_last_connect=millis();
	mode=MODE_AP ;
	return true;
}
  
  
bool Fallback_wifi::mode_st(){
	Serial.println("Connecting to station...");
	unsigned int i = 0;
	while (wifiMulti.run() != WL_CONNECTED) { 
		// Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
		if(i*250>=st_timeout){break;}
		++i;
		delay(250);
		Serial.print('.');
	}

	if(wifiMulti.run() == WL_CONNECTED){
	  Serial.print("Connected to station, ssid=");
	  Serial.print(WiFi.SSID());
	  Serial.print(", IP=");
	  Serial.println(WiFi.localIP());
	  mode = MODE_ST;
	  return true;
	}else{
	  Serial.println("Cannot connect to station"); 
	  mode = MODE_DISCONNECT;
	  return false;
        }
}


  

//=== update ===

void Fallback_wifi::update(){
  	  if(mode==MODE_ST){
		  if(wifiMulti.run() == WL_CONNECTED){
		    Serial.print("Already connected to station, ssid=");
		    Serial.print(WiFi.SSID());
		    Serial.print(", IP=");
		    Serial.print(WiFi.localIP());
        Serial.print(", MAC=");
        Serial.println(WiFi.macAddress());
		    return;
		  }else{
		    Serial.print("Disconnected from station");
		  }
	  }

	  //if in access point mode, stay in it for a delay
	  if(mode==MODE_AP){
      auto delta = millis() - ap_last_connect;
	    if( delta < ap_stay){
	      Serial.print("Staying in ap mode, ssid="); Serial.print(WiFi.SSID());
	      Serial.print(", IP=");                     Serial.print(WiFi.softAPIP() );
	      Serial.print(", connections=");            Serial.print(WiFi.softAPgetStationNum());
	      Serial.print(", mac=");                    Serial.print(WiFi.softAPmacAddress().c_str());
        Serial.print(", timeout(s)=");             Serial.print(delta/1000);Serial.print("/");Serial.println(ap_stay/1000);
	      return;
	    }
          }
          
          //neither in mode_sr, nor in mode_ap before timeout => connect
          bool ok = mode_st();
	  if(!ok){
	    Serial.println("Fallback to access point");
	    mode_ap();
	  }
  
}
   



//=== debug information ===
String Fallback_wifi::str_mode()const{
	switch(mode){
	case MODE_DISCONNECT: return "Disconnected";
	case MODE_AP : return "Access point (standalone)";
	case MODE_ST : return "Connected to station " + WiFi.SSID();
	}
}

String Fallback_wifi::str_mac()const{
    return WiFi.macAddress();
}

String Fallback_wifi::str_ip()const{
	if(mode==MODE_ST){return WiFi.localIP().toString();}
	if(mode==MODE_AP){return WiFi.softAPIP().toString();}
	return "not connected";
}


String Fallback_wifi::str_stationNum()const{
	if(mode==MODE_AP){return String(WiFi.softAPgetStationNum());}
	return "not in AP mode";
} 

String Fallback_wifi::str_timeout()const{
	auto delta = millis() - ap_last_connect;
	if(mode==MODE_AP){return String(delta/1000)+"/"+String(ap_stay/1000);}
	return "not in AP mode";
} 

String Fallback_wifi::str_ssid()const{
	return WiFi.SSID() ;
}
 
 
 
