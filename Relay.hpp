struct Relay{
  Relay(int pin_):pin(pin_){}
  void begin();
  void switch_on();
  void switch_off();
  
  bool is_on() const{return status==ON;}
  bool is_off()const{return status==OFF;}

  private:
  bool status;
  static constexpr bool ON  = true;
  static constexpr bool OFF = false;
  
  int pin;
};



inline void Relay::begin(){
	pinMode     (pin,OUTPUT);
	digitalWrite(pin,LOW);
	status=ON;
}

inline void Relay::switch_on(){
	if(status==ON){return;}
	digitalWrite(pin,LOW);
	status=ON;
	delay(1000); //safety don't blink
}


inline void Relay::switch_off(){
	if(status==OFF){return;}
	digitalWrite(pin,HIGH);
	status=OFF;
	delay(1000); //safety don't blink
}



