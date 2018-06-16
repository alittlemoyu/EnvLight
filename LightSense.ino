int light = 0;
int val = 0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  val = analogRead(light);
  Serial.print(val);
  Serial.println();
  delay(100);
}

