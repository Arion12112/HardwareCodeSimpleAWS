#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

char t[32];

void setup() 
{
  Serial.begin(115200);
  Wire.begin(5, 4);   //Setting wire (5 untuk SDA dan 4 untuk SCL)

  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));  //Setting Time
  
  // Kalian dapat menambahkan bagian dibawah ini untuk set manual jam
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

}

void loop()
{
  DateTime now = rtc.now();       //Menampilkan RTC pada variable now

  Serial.print("Tanggal : ");
  Serial.print(now.day());        //Menampilkan Tanggal
  Serial.print("/");
  Serial.print(now.month());      //Menampilkan Bulan
  Serial.print("/");
  Serial.print(now.year());       //Menampilkan Tahun
  Serial.print(" ");
  
  Serial.print("Jam : ");
  Serial.print(now.hour());       //Menampilkan Jam
  Serial.print(":");
  Serial.print(now.minute());     //Menampilkan Menit
  Serial.print(":");
  Serial.print(now.second());     //Menampilkan Detik
  Serial.println();

  delay(1000);
}
