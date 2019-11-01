#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>
 
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;
 
}
 
void loop() {
  const size_t capacity = JSON_OBJECT_SIZE(2) + 90;
 DynamicJsonDocument doc(capacity);
  auto error = deserializeJson(doc, s);
if (error) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return;
}
  Serial.println("JSON received and parsed");
  serializeJson(doc, s);
  Serial.print("key = ");
  int data1=doc["key"];
  Serial.println(data1);
  Serial.print("raw = ");
  int data2=doc["raw"];
  Serial.println(data2);
  Serial.println("");
}
