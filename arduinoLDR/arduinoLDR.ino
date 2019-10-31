const int ldr = 4;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ldr,INPUT);
}

void loop() {
  Serial.println(digitalRead(ldr));
  // put your main code here, to run repeatedly:
  delay(500);

}
