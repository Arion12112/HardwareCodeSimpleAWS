#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
 
void setup() {
s.begin(9600);
}
 
void loop() {
const size_t capacity = JSON_OBJECT_SIZE(2) + 90;
DynamicJsonDocument doc(capacity);
doc["key"] = 100;
doc["raw"] = 200;
if(s.available()>0)
{
serializeJson(doc, s);
}
delay(1000);
}
