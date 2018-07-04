#include <LiquidCrystal.h>
#include <MsTimer2.h> 
LiquidCrystal lcd(12,11,7,6,5,4);
int tick = 0;
int tock = 0;
int light = 0;
int lowdistance = 0;
int lowlight = 0;
int night = 0;
int waiting = 0;
int backlight = 5;
int lcddisplay = 10;
int i;
const int TrigPin = 13;
const int EchoPin = 10;
const int pinInterrupt = 2; 
const int BluePin = 9;
const int BacklightPin = 8;
float dist;
int temp;
int check;
int check0;
int ans = 0;
int keep;
int sjmp = 0;
int tick_ans;

void onChange()  
{  
  digitalWrite(BacklightPin,HIGH);
  backlight = 5;
  lcddisplay = 10;
  Serial.println("You want me DISPLAY?");
  lcd.setCursor(0,0);
  lcd.print("LCD YES!    ");
} 

void onTimer()
{ 
  GetDist();
  GetLex();
  
  if (((lowdistance and lowlight) == 1) or (tick > 0))
  {
    light = 1;
    keep = 1;
    Serial.println("Pass");
  }
  else
  {
    if (keep == 1)
    {
      light = 1;
      keep = 0;
      check0 = 1;
    }
    else light = 0;
  }   
  
  if (lowdistance == 1)
  {
    waiting = 0;
    tick = 0;
    tock = 0;
    sjmp = 0;
  }

  if (lowlight == 0)
  {
    waiting = 0;
    tick = 0;
    tock = 0;
    check0 = 0;
  }  
  
  if (waiting > 0)
  {
    Serial.print("Waiting changes from ");
    Serial.print(waiting);
    waiting = waiting - 1;
    Serial.print(" to ");
    Serial.println(waiting);
    if (waiting == 0)
    {
      tock = 1;
    }
  }

  if ((ans - light) == 1)
  {
    Serial.println("We are losing the light.");
  }
  ans = light;
      
  if (check0 == 1)
  {
    check = 1;
    Serial.println("Doulble Check 1 !!!");
    check0 = 0;
  }
  else if (tock == 1)
  {
    check = 1;
    Serial.println("Doulble Check 2 !!!");
  }
  else check = 0;
  
  ControlLight();
  
  Serial.print("Lowdistance is ");
  Serial.print(lowdistance);
  Serial.print(".And lowlight is ");
  Serial.print(lowlight);
  Serial.print(".Tick is ");
  Serial.print(tick);
  Serial.print(".Tock is ");
  Serial.print(tock);
  Serial.print(".Now waiting is ");
  Serial.println(waiting);
      
  if ((light == 1) and (tick == 0))
  {  
    if ((tick_ans - tick) > 0)
    {
      lcd.setCursor(0,0);
      lcd.print("Welcome back!");
      Serial.print("Welcome back!");
      Serial.println();
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.print("Light is On.");
      Serial.print("Light is On.");
      Serial.println();
    }
  }
  else if ((light == 1) and (tick == 1))
  {
    lcd.setCursor(0,0);
    lcd.print("Where're you?   ");
    Serial.print("Where're you?");
    Serial.println();
  }
  else if ((light == 1) and (tick == 2))
  {
    lcd.setCursor(0,0);
    lcd.print("Waiting...     ");
    Serial.print("Waiting...");
    Serial.println();
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Gone.        ");
    Serial.print("Gone.");
    Serial.println();
  }  

  tick_ans = tick;
  
  temp = round(analogRead(A1)*5*100/1024.00);
  Serial.print("Temp is ");
  Serial.print(temp);
  Serial.println(" Celsius");
  Serial.println();
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.setCursor(2,1);
  lcd.print(" Celsius!");
  if (backlight > 0)
  {
    backlight = backlight-1;
  }
  else
  {
    digitalWrite(BacklightPin,LOW);
  }
  Serial.print("lcddisplay is ");
  Serial.print(lcddisplay);
  Serial.print(" and night is ");
  Serial.print(night);  
  if ((lcddisplay > 0) and (night == 1))
  {
    lcddisplay = lcddisplay - 1;
    Serial.println(" LCD -1");
  }
  else if (night == 0)
  {
    lcddisplay = 10;
    lcd.display();
    Serial.println(" LCD on");
  }
  else
  {
    lcd.noDisplay();
    Serial.println(" LCD off");
  }
} 

float GetDist()
{
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  dist = pulseIn(EchoPin,HIGH)/58.00;
  if (dist<80)
  {
    lowdistance = 1;
  }
  else
  {
    lowdistance = 0;
  }
  Serial.print("The distance is ");
  Serial.println(dist);
  return dist;
}

int GetLex()
{ 
  if (analogRead(0)>240)
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
    Serial.println("It's night");
  }
  else
  {
    night = 0;
  }
  Serial.print("Light is ");
  Serial.println(analogRead(0));
  return lowlight;
}

int ControlLight()
{
  if (light == 1)
  {
    digitalWrite(BluePin,LOW);
  }
  else
  {
    digitalWrite(BluePin,HIGH);
  }
  Serial.println("Checking Light Status···");
  return 0;
}


void setup() 
{
  Serial.begin(9600);
  Serial.print("Link Start");
  Serial.println();
  delay(500);
  pinMode(BluePin,OUTPUT);
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  pinMode(BacklightPin,OUTPUT);
  pinMode(pinInterrupt, INPUT);
  digitalWrite(BacklightPin,HIGH);
  lcd.begin(16,2);
  lcd.print("Link Start!");
  lcd.setCursor(16,1); 
  lcd.blink();    
  MsTimer2::set(1000, onTimer); 
  MsTimer2::start(); 
  attachInterrupt(0,onChange,RISING); 
  GetDist();
  GetLex();
    
  Serial.print("Now let's rolling!");
  Serial.println();
  Serial.println();
}

void loop() 
{
  if ((check == 1) and (sjmp == 0))
  {
    if ((tick == 0) and (tock == 0))
    {
      Serial.println("Here is the magic!");
      waiting = 15;
      tick = 1;
    }
    if (tick == 1)
    {
      if(tock == 1)
      {
        if (lowdistance == 0)
        {
          tick = 2;
          tock = 0;
          Serial.println("Soon leave.");
          waiting = 60;
        }
      }
    }
    if (tick == 2)  
    {
      if(tock == 1)
      {
        if (lowdistance == 0)
        {
          tick = 0;
          tock = 0;
          Serial.println("All gone.");
          sjmp = 1;
        }
      }
    }
  }
}
