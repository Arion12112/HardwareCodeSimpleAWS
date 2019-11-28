#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <dht.h>
#include <Wire.h>
#include <SFE_BMP180.h>

SoftwareSerial s(5,6);
dht DHT;
SFE_BMP180 bmp180;

#define DHT11_PIN 7

const int ldr = A0;
const int rain = A1;
const int air = A2;
const int condition= 4;
float Po = 1013.77;

int lux;
int rainIntensity;
int chk;
double T, P;
int alt;
float humidity;
String Condition;
String Air;

String data= "";


 
void setup() {
s.begin(9600);
//Serial.begin(9600);
pinMode(ldr,INPUT);
pinMode(air, INPUT);
pinMode(rain, INPUT);
bmp180.begin();
}

void SensorRead()
  {
    lux = analogRead(ldr);
    rainIntensity = analogRead(rain);
    chk = DHT.read11(DHT11_PIN);
    humidity = DHT.humidity;
    char status;

    status = bmp180.startTemperature();

    if (status != 0) {
     delay(1000);
      status = bmp180.getTemperature(T);

     if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          alt = bmp180.altitude(P, Po);

        }
      }
    }
  }
    
    if(digitalRead(condition) == LOW) 
    {
    Condition = "Basah";
    delay(10); 
    }
    else
    {
    Condition = "Kering";
    delay(10); 
    }

    if(analogRead(air)>=1000)
    {
      Air = "Bahaya";
    }

    else if(analogRead(air)>=750)
    {
      Air = "Tidak Sehat";
    }
    
    else if(analogRead(air)>=500)
    {
      Air = "Normal";
    }

    
    else Air = "Sehat";
    
    
    data += String(T);
    data += String(",");
    data += String(P);
    data += String(",");
    data += String(alt);
    data += String(",");
    data += String(lux);
    data += String(",");
    data += Condition;
    data += String(",");
    data += Air;
    data += String(",");
    data += String(humidity);
  }
 
  void loop() {
yield();
SensorRead();
s.print(data);
s.flush();
data = "";


delay(59000);
}
