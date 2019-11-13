const int ldr = A0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ldr,INPUT);
}

void loop() {
  Serial.println(analogRead(ldr));
  // put your main code here, to run repeatedly:
  delay(500);

}
