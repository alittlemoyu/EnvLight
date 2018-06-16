#include <LiquidCrystal.h>
#include <MsTimer2.h> 
LiquidCrystal lcd(12,11,8,7,6,5);
int tick = 0;
int light = 0;
int lowdistance = 0;
int lowlight = 0;
int night = 0;
int waiting = 0;
int backlight = 5;
int lcddisplay = 10;
int i=0;
const int TrigPin = 0;
const int EchoPin = 1;
const int pinInterrupt = 2; 
const int LightPin = 3;
const int BacklightPin = 4;
float dist;
float temp;
float distance;

void onChange()  
{  
  digitalWrite(BacklightPin,HIGH);
  backlight = 5;
} 

void onTimer()  
{ 
  Serial.println(lowdistance);
  Serial.println(lowlight);
  if ((light == 1)and(waiting == 0))
  {
    lcd.setCursor(0,0);
    lcd.print("Light is On.");
    Serial.print("Light is On.");
    Serial.println();
  }
  else if (light == 1)
  {
    lcd.setCursor(0,0);
    lcd.print("Waiting for you.");
    Serial.print("Waiting for you.");
    Serial.println();
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Gone.");
    Serial.print("Gone.");
    Serial.println();
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
  if ((lcddisplay>0)&&(night == 1))
  {
    lcddisplay = lcddisplay - 1;
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

float GetDist()
{
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  distance = pulseIn(EchoPin,HIGH)/58.00;
  if (distance<120)
  {
    lowdistance = 1;
  }
  else
  {
    lowdistance = 0;
  }
  Serial.println(distance);
  return distance;
}

int GetLex()
{ 
  if (analogRead(0)>280)
  {
    lowlight = 1;
  }
  else
  {
    lowlight = 0;
  }
  if (analogRead(0)>800)
  {
    night = 1;
  }
  else
  {
    night = 0;
  }
  Serial.println(analogRead(0));
  return lowlight;
}

int ControlLight()
{
  if (light == 1)
  {
    digitalWrite(LightPin,HIGH);
  }
  else
  {
    digitalWrite(LightPin,LOW);
  }
  Serial.println("Fuck!");
  return 0;
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Link Start");
  Serial.println();
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  pinMode(BacklightPin,OUTPUT);
  pinMode(pinInterrupt, INPUT);
  digitalWrite(BacklightPin,HIGH);
  lcd.begin(16,2);
  lcd.print("Link Start!");
  lcd.setCursor(11,0); 
  lcd.blink(); 
  MsTimer2::set(1000, onTimer); 
  MsTimer2::start(); 
  attachInterrupt( digitalPinToInterrupt(pinInterrupt), onChange, CHANGE); 
}

void loop() 
{
  // put your main code here, to run repeatedly:
  distance = GetDist();
  lowlight = GetLex();
  if (lowdistance && lowlight == 1)
  {
    light = 1;
  }
  i = ControlLight();
  for(i=10;i>0;i--)
  {
    delay(850);
    distance = GetDist();
    lowlight = GetLex();
  }
  if (lowdistance == 1)
  {
    light = 1;
  }
  else
  {
    waiting = 1;
    for(i=180;i>0;i--)
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
