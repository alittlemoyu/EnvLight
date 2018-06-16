#include <LiquidCrystal.h>
#include <MsTimer2.h> 
LiquidCrystal lcd(12,11,7,6,5,4);
int tick = 0;
int light = 0;
int lowdistance = 0;
int lowlight = 0;
int night = 0;
int waiting = 0;
int backlight;
int lcddisplay = 10;
int i=0;
const int TrigPin = 0;
const int EchoPin = 1;
const int LightPin = 2;
const int BacklightPin = 3;
float dist;
float temp;
float GetDist();
int GetLex();
void ControlLight();

void onTimer()  
{ 
  if ((light == 1)and(waiting == 0))
  {
    lcd.setCursor(0,0);
    lcd.print("Light is On.");
    Serial.println("Light is On.");
  }
  else if (light == 1)
  {
    lcd.setCursor(0,0);
    lcd.print("Waiting for you.");
    Serial.println("Waiting for you.");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Sun is alive.");
    Serial.println("Sun is alive.");
  }
  temp = analogRead(A1)*5*100/1024.00;
  Serial.println(temp);
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.setCursor(5,1);
  lcd.print("℃");
  if (backlight > 0)
  {
    backlight = backlight-1;
  }
  else
  {
    digitalWrite(BacklightPin,LOW);
  }
  if ((lcddisplay > 0)&&(night == 1))
  {
    lcddisplay = lcddisplay-1;
  }
  else
  {
    lcd.noDisplay();
  }
  if ((lcddisplay == 0)&&(night == 0))
  {
    lcddisplay = 10;
    lcd.display();
  }
} 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Link Start!");
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  pinMode(BacklightPin,OUTPUT);
  lcd.begin(16,2);
  lcd.print("Link Start!");
  lcd.setCursor(11,0); 
  lcd.blink(); 
  MsTimer2::set(1000, onTimer); 
  MsTimer2::start(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  GetDist();
  GetLex();
  if (lowdistance && lowlight == 1)
  {
    light = 1;
  }
  ControlLight();
  for(i=10;i>0;i--)
  {
    delay(850);
    GetDist();
    GetLex();
  }
  if (lowdistance == 1)
  {
    light = 1;
  }
  else
  {
    waiting = 1;
    for(i=60;i>0;i--)
    {
      delay(1000);
    }
    if (lowdistance == 0)
    {
      light = 0;
      ControlLight();
    } 
    waiting = 0;
  }
}

float GetDist()
{
  float distance;
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  distance = pulseIn(EchoPin,HIGH)/58.00;
  if (GetDist() < 120)
  {
    lowdistance = 1;
  }
  else
  {
    lowdistance = 0;
  }
  return distance;
}

int GetLex()
{ 
  int lex = 0;
  if (analogRead(lex) > 280)
  {
    lowlight = 1;
  }
  else
  {
    lowlight = 0;
  }
  if (analogRead(lex) > 800)
  {
    night = 1;
  }
  else
  {
    night = 0;
  }
  return lowlight;
}

void ControlLight()
{
  if (light == 1)
  {
    digitalWrite(LightPin,HIGH);
    Serial.println("Light");
  }
  else
  {
    digitalWrite(LightPin,LOW);
    Serial.println("Dark");
  }
  digitalWrite(BacklightPin,HIGH);
  backlight = 5;
}
