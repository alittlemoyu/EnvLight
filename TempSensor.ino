float temp;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = analogRead(A1)*5*100/1024.00;
  Serial.println(temp);
  delay(300);
}
