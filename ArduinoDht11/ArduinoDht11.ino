#include <dht.h>
#include <eRCaGuy_Timer2_Counter.h>

dht DHT;

unsigned long seconds = 1000L; // !!! SEE THE CAPITAL "L" USED!!!
unsigned long minutes = seconds * 60;
unsigned long hours = minutes * 60; 

#define DHT11_PIN 7

void setup(){
  Serial.begin(9600);
  timer2.setup(); //this MUST be done before the other Timer2_Counter functions work; Note: since this messes up PWM outputs on pins 3 & 11, as well as 
                  //interferes with the tone() library (http://arduino.cc/en/reference/tone), you can always revert Timer2 back to normal by calling 
                  //timer2.unsetup()A
}

void loop()
{
  static unsigned long t_start = timer2.get_count(); //units of 0.5us; the count accumulated by Timer2_Counter
  
  //acquire time stamps
  unsigned long t_micros = micros();
  unsigned long t_T2_count = timer2.get_count(); //units of 0.5us; the count accumulated by Timer2_Counter
  float t_T2_micros = timer2.get_micros(); //us; the time value accumulated by Timer2_Counter (this is the exact same as doing timer2.get_count()/2.0;)
  

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(float(DHT.temperature,2));
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(5000);
}
