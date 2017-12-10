// A simple Menu Program made by KspPaul

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#define ONE_WIRE_BUS 13
OneWire oneWire(ONE_WIRE_BUS);
#include <DallasTemperature.h>
DallasTemperature sensors(&oneWire);

int counter = 1; 
const int down = 4; 
const int ok =2 ;
const int up = 7;
const int light = A0; // this is for the photocell
const int led = 8; // the Pin for the led


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void setup()   {                
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(1000);

  pinMode(down, INPUT);
  pinMode(up , INPUT);
  pinMode(ok, INPUT);
  pinMode(led, OUTPUT);
  
  display.setTextSize(0.5);
  display.setTextColor(WHITE);

  sensors.begin(); 
}


void loop() {
  int downState = digitalRead(down);
  int upState = digitalRead(up);
  int okState = digitalRead(ok);

  Serial.println(counter);
  if(downState == HIGH)
  {
    
    counter--;
  }
  else if(upState == HIGH)
  {
    counter++;
  }

  if(counter==0)
  {
    counter = 3;
  }
  if(counter==4)
  {
    counter =1;
  }

  if(okState == HIGH)
  {
 
    if(counter==1)
    {
      
     
      while(downState==LOW)
      {
        display.clearDisplay();
        sensors.requestTemperatures();
        display.setCursor(0,0);
        display.print("Temperature: ");
        display.println(sensors.getTempCByIndex(0));
        display.display();
        
        delay(100);
        downState = digitalRead(down);
      }
    }
    if(counter==2)
    {
      while(downState==LOW)
      {
        int bright = analogRead(light); 

        
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("Brightness: ");
        display.println(bright);
        display.display();

        downState = digitalRead(down);
        delay(200);
      }
    }
    if(counter==3)
    {
      digitalWrite(led, HIGH);
      
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("LED is on");
      display.display();
      
      
      while(downState==LOW)
      {
        delay(100);
        downState = digitalRead(down);
      }
    }
  }

  if(counter==1)
  {
    display.setCursor(0,0);
    display.print("tempS: You are here");
    display.setCursor(0,10);
    display.print("lights:");
    display.setCursor(0,20);
    display.print("led:");
    display.display();
    delay(500);
  }
  if(counter==2)
  {
    display.setCursor(0,0);
    display.print("tempS:");
    display.setCursor(0,10);
    display.print("lights: You are here");
    display.setCursor(0,20);
    display.print("led:");
    display.display();
    delay(500);
  }
  if(counter==3)   
  {
    display.setCursor(0,0);
    display.print("tempS:");
    display.setCursor(0,10);
    display.print("lights:");
    display.setCursor(0,20);
    display.print("led: You are here");
    display.display();
    delay(500);
  }

  digitalWrite(led, LOW);
  display.clearDisplay();
}
