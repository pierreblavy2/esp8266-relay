#ifndef STATE_HPP_pierre_
#define STATE_HPP_pierre_

#include <Arduino.h>
#include "LittleFS.h"

namespace fs{class File;}

//--- persistant state ---
struct State {
    void make_default();
    void save(fs::File& f);
    void load(fs::File& f);


    void save();
    void load();
    

    
    void print()const;
    
    //--- wifi ssid and pass ---
    void set_wifi_ssid(const char*);
    void set_wifi_pass(const char*); 
    void set_wifi_ssid(const String&s){set_wifi_ssid(s.c_str());}
    void set_wifi_pass(const String&s){set_wifi_ssid(s.c_str());}
    const char* get_wifi_ssid()const{return wifi_ssid;}
    const char* get_wifi_pass()const{return wifi_pass;}

    //--- ntp ---
    static constexpr unsigned char NTP_ON  = 0;
    static constexpr unsigned char NTP_OFF = 1;
    
    void set_ntp(const char*);
    const char* get_ntp()const{return ntp_server;} 
    String str_ntp_mode()const;

    
    //--- program_mode ---
    static constexpr unsigned char MODE_ON = 0;
    static constexpr unsigned char MODE_OFF = 1;
    static constexpr unsigned char MODE_AUTO = 2;
    void          set_program_mode(const unsigned char x){program_mode=x%3;}
    unsigned char get_program_mode()const                {return program_mode;}
    String        str_program_mode()const{
        unsigned char m = get_program_mode();
        if(m==MODE_ON)  {return "Toujours ON";}
        if(m==MODE_OFF) {return "Toujours OFF";}
        if(m==MODE_AUTO){return "Programme";}
        return "MODE INVALIDE";
    }
    
    void set_mode_on()  {program_mode=MODE_ON;}
    void set_mode_off() {program_mode=MODE_OFF;}
    void set_mode_auto(){program_mode=MODE_AUTO;}
    
    bool is_mode_on()  const{return program_mode==MODE_ON;}
    bool is_mode_off() const{return program_mode==MODE_OFF;}
    bool is_mode_auto()const{return program_mode==MODE_AUTO;}



    
    //--- hours ---
    bool get_hh(const String &name)const;
    void set_hh(const String &name, bool b);
    static bool is_hh(const String &name);
    
    //--- DATA ---
    char wifi_ssid[33];
    char wifi_pass[128];
    char ntp_server[256];
    
    unsigned char program_mode : 2;
    unsigned char h00 : 1; unsigned char h01 : 1; unsigned char h02 : 1;
    unsigned char h03 : 1; unsigned char h04 : 1; unsigned char h05 : 1;
    unsigned char h06 : 1; unsigned char h07 : 1; unsigned char h08 : 1;
    unsigned char h09 : 1; unsigned char h10 : 1; unsigned char h11 : 1;
    unsigned char h12 : 1; unsigned char h13 : 1; unsigned char h14 : 1;
    unsigned char h15 : 1; unsigned char h16 : 1; unsigned char h17 : 1;
    unsigned char h18 : 1; unsigned char h19 : 1; unsigned char h20 : 1;
    unsigned char h21 : 1; unsigned char h22 : 1; unsigned char h23 : 1;
    
    unsigned char ntp_mode : 1;

    

    
};

#endif
