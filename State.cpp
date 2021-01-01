#include "State.hpp"
#include "LittleFS.h"    // https://projetsdiy.fr/esp8266-lire-ecrire-modifier-fichier-librairie-littlefs/   
#include<cctype> //isdigit


void State::save(){
      //File f = SPIFFS.open("config", "w");
      File f = LittleFS.open("config", "w");
      if(f){
        this->save(f);
        Serial.println("State saved");
        //this->print();
        f.close();        
      }else{
        Serial.println("ERROR cannot save state");
      }      
}


void State::load(){
    //File f = SPIFFS.open("config", "r");
    File f = LittleFS.open("config", "r");
    if(f){
      Serial.println("State loaded");
      this->load(f);
      //Serial.println("---loaded as---");
      //this->print();
    }else{
      Serial.println("No configuration file, create default state");
      this->make_default();
    }
    f.close();
}



void State::make_default(){
    //default initialisation
    memset(this, 0, sizeof(State) );
    set_wifi_ssid("MY_SSID");
    set_wifi_pass("MY_PASSWORD");
    set_ntp("europe.pool.ntp.org");
}


void State::set_wifi_ssid(const char*s){
  static constexpr size_t n = sizeof(wifi_ssid)/sizeof(char);
  strncpy(wifi_ssid,s, n);
  wifi_ssid[n-1]='\0';
}


void State::set_wifi_pass(const char*s){
  static constexpr size_t n = sizeof(wifi_pass)/sizeof(char);
  strncpy(wifi_pass,s, n);
  wifi_pass[n-1]='\0';
}



void State::set_ntp(const char*s){
  static constexpr size_t n = sizeof(ntp_server)/sizeof(char);
  strncpy(ntp_server,s, n);
  ntp_server[n-1]='\0';
}
    
String State::str_ntp_mode()const{
  if(ntp_mode==NTP_ON){return "NTP";}
  else                {return "Manuel";}
}
 
bool State::is_hh(const String &name){
  return name.length()==3
     and name[0]=='h'
     and isdigit(name[1])
     and isdigit(name[2]);
}
    
bool State::get_hh(const String &name)const{
	if(name=="h00"){return h00==1;}  if(name=="h01"){return h01==1;} if(name=="h02"){return h02==1;}
	if(name=="h03"){return h03==1;}  if(name=="h04"){return h04==1;} if(name=="h05"){return h05==1;}
	if(name=="h06"){return h06==1;}  if(name=="h07"){return h07==1;} if(name=="h08"){return h08==1;}
	if(name=="h09"){return h09==1;}  if(name=="h10"){return h10==1;} if(name=="h11"){return h11==1;}
	if(name=="h12"){return h12==1;}  if(name=="h13"){return h13==1;} if(name=="h14"){return h14==1;}
	if(name=="h15"){return h15==1;}  if(name=="h16"){return h16==1;} if(name=="h17"){return h17==1;}
	if(name=="h18"){return h18==1;}  if(name=="h19"){return h19==1;} if(name=="h20"){return h20==1;}
	if(name=="h21"){return h21==1;}  if(name=="h22"){return h22==1;} if(name=="h23"){return h23==1;}
	Serial.print("ERROR : wrong name in get_hh, name="); Serial.println(name);
	return false;
}

void State::set_hh(const String &name, bool b){
	if(name=="h00"){h00=b?1:0;return;}  if(name=="h01"){h01=b?1:0;return;} if(name=="h02"){h02=b?1:0;return;}
	if(name=="h03"){h03=b?1:0;return;}  if(name=="h04"){h04=b?1:0;return;} if(name=="h05"){h05=b?1:0;return;}
	if(name=="h06"){h06=b?1:0;return;}  if(name=="h07"){h07=b?1:0;return;} if(name=="h08"){h08=b?1:0;return;}
	if(name=="h09"){h09=b?1:0;return;}  if(name=="h10"){h10=b?1:0;return;} if(name=="h11"){h11=b?1:0;return;}
	if(name=="h12"){h12=b?1:0;return;}  if(name=="h13"){h13=b?1:0;return;} if(name=="h14"){h14=b?1:0;return;}
	if(name=="h15"){h15=b?1:0;return;}  if(name=="h16"){h16=b?1:0;return;} if(name=="h17"){h17=b?1:0;return;}
	if(name=="h18"){h18=b?1:0;return;}  if(name=="h19"){h19=b?1:0;return;} if(name=="h20"){h20=b?1:0;return;}
	if(name=="h21"){h21=b?1:0;return;}  if(name=="h22"){h22=b?1:0;return;} if(name=="h23"){h23=b?1:0;return;}
	Serial.print("ERROR : wrong name in set_hh, name="); Serial.println(name);
}


void State::print()const{
	Serial.print("SSID:"); Serial.println(wifi_ssid);
	//Serial.print("PASS:"); Serial.println(wifi_pass);
	Serial.print("program_mode:");Serial.println(program_mode);
	Serial.print("h00:");Serial.println(h00); Serial.print("h01:");Serial.println(h01); Serial.print("h02:");Serial.println(h02);
	Serial.print("h03:");Serial.println(h03); Serial.print("h04:");Serial.println(h04); Serial.print("h05:");Serial.println(h05);
	Serial.print("h06:");Serial.println(h06); Serial.print("h07:");Serial.println(h07); Serial.print("h08:");Serial.println(h08);
	Serial.print("h09:");Serial.println(h09); Serial.print("h10:");Serial.println(h10); Serial.print("h11:");Serial.println(h11);
	Serial.print("h12:");Serial.println(h12); Serial.print("h13:");Serial.println(h13); Serial.print("h14:");Serial.println(h14);
	Serial.print("h15:");Serial.println(h15); Serial.print("h16:");Serial.println(h16); Serial.print("h17:");Serial.println(h17);
	Serial.print("h18:");Serial.println(h18); Serial.print("h19:");Serial.println(h19); Serial.print("h20:");Serial.println(h20);
	Serial.print("h21:");Serial.println(h21); Serial.print("h22:");Serial.println(h22); Serial.print("h23:");Serial.println(h23);
  
  Serial.print("ntp_mode:");Serial.println(ntp_mode);
  Serial.print("ntp:");Serial.println(get_ntp() );

  /*Serial.print("raw ");
  Serial.print( sizeof(State) );
  Serial.print("{");
  const char* x = reinterpret_cast<const char*>(this);
  String s;
  for(size_t i = 0; i < sizeof(State); ++i){
    s+=String(int(x[i])) + " ";
  }
  Serial.print(s);
  Serial.println("}");*/
 
	Serial.println();
}




static_assert(std::is_trivial<State>::value, "State::save and State::load implementation expect a trivial class");
void State::save(fs::File& f){ 
  f.write    (reinterpret_cast<char*>(this), sizeof(State) );

}

void State::load(fs::File& f){ f.readBytes(reinterpret_cast<char*>(this), sizeof(State) ); }
