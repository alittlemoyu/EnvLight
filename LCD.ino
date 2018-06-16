#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
int D5;
int D4;
int D3;
int D2;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("EnvLight");
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  D5 = digitalRead(5);
  D4 = digitalRead(4);
  D3 = digitalRead(3);
  D2 = digitalRead(2);
  Serial.print(D5);
  Serial.print(D4);
  Serial.print(D3);
  Serial.println(D2);
  delay(500);
}
