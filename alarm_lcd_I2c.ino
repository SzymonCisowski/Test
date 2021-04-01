#include <Keypad.h> 
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(14,15,16,17,18,19);
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
bool alarm=true;
int haslo=1111;
int has=0;
const byte ROWS = 5; 
const byte COLS = 5; 
int wartosc=0;
char klawisz;
char h;
bool t=true;
bool c=true;
char a;
char b;
char d;
char e;
int err=0;
bool ruch=false;
 
byte rowPins[ROWS] = {0, 12, 2, 3}; 
byte colPins[COLS] = {4, 5, 6, 7}; 
 
char keys[ROWS][COLS] = { 
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 
 
void setup(){
  lcd.init();
  lcd.backlight();
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ustaw 4 cyfrowy");
  lcd.setCursor(0,1);
  lcd.print("pin:");
   
    
  
} 
void loop(){
  if(digitalRead(11) == HIGH && c==false && t==false)
  {
    ruch=true;
  }
  if(alarm == true && ruch==true)
  {
    digitalWrite(8,HIGH);
    tone(10,1000);
    
   
  }
  if(c==true){
    klawisz = klawiatura.getKey();
    if(klawisz && has==0)
    {
      a=klawisz;
      lcd.print(a);
      has=1;
    }
    else if(klawisz && has==1)
    {
      b=klawisz;
      lcd.print(b);
      has=2;
    }
    else if(klawisz && has==2)
    {
      d=klawisz;
      lcd.print(d);
      has=3;
    }
    else if(klawisz && has==3)
    {
      e=klawisz;
      lcd.print(e);
      c=false;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Ustawiony pin:");
      lcd.setCursor(0,1);
      lcd.print(a);
      lcd.print(b);
      lcd.print(d);
      lcd.print(e);
      delay(2000);
    }
    
  }
  if(wartosc==0 && c==false){
  klawisz = klawiatura.getKey();
  }
  if(alarm == true && wartosc==0 && t==true && c==false && ruch==false)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stan alarmu : ON");
  lcd.setCursor(0,1);
  lcd.print("A. Odblokuj");
  t=false;
  has=0;
  }
  else if(alarm == false && wartosc==0 && t==true && c==false && ruch==false)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Stan alarmu: OFF");
    lcd.setCursor(0,1);
    lcd.print("B. Zablokuj");
    t=false;
    has=0;
    
  }
  if(alarm == true && klawisz=='A' && c==false||ruch==true &&  alarm==true)
  {
   if(wartosc==0)
   {wartosc=1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Podaj pin:");
  lcd.setCursor(0,1); 
  
   }
   h = klawiatura.getKey();
   if(h)
   {
    
    lcd.print(h);
    err++;
  if(h==a&& has==0)
  {
    has=1;
  }
    
    else if(h==b&& has==1)
    {
      has=2;
      }
    else if(h==d&& has==2)
      {
       has=3;
      }
      else if(h==e && has==3)
      {
         
          delay(500);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Poprawny pin");
          alarm=false;
          wartosc=0;
          t=true;
          has=4;
          err=0;
          ruch=false;
          delay(1000);
        }
      
    if(err == 4 && has!=4)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Niepoprawny pin");
      alarm=true;
      wartosc=0;
      t=true;
      err=0;
      delay(1000);
    }
    
  

 }
}  
  
  
if(alarm == true && c==false)
  {
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    delay(200);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
  }
  else
  {
    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
    noTone(10);
    
    delay(200);
  }
  if(alarm == false && klawisz=='B' && c==false)
  {
   if(wartosc==0)
   {wartosc=1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Podaj pin:");
  lcd.setCursor(0,1); 
  
   }
   h = klawiatura.getKey();
   if(h)
   {
    lcd.print(h);
    err++;
  if(h==a && has==0)
  {
    has=1;
  }
    else if(h==b && has==1)
    {
      has=2;
    }
    else if(h==d && has==2)
      {
       has=3; 
      }
      else if(h==e && has==3)
      {
          
          delay(500);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Poprawny pin");
          alarm=true;
          wartosc=0;
          t=true;
          has=4;
          err=0;
          ruch=false;
          delay(1000);
          
        }
        if(err==4 && has!=4)
        {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Niepoprawny pin");
      alarm=false;
      wartosc=0;
      t=true;
      err=0;
      ruch=false;
      delay(1000);
        }
      
    
  

 }
}  
  

}
