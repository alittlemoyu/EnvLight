const int TrigPin = 2;
const int EchoPin = 3;
float distance;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  Serial.println("Ultrasonic sensor:");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  distance = pulseIn(EchoPin,HIGH)/58.00;
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(500);
}
