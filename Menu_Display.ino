// A simple Menu Program made by KspPaul
/*This project is a Arduino Menu which can be controlled with three Buttons. 
The first Menu is for a temperature Sensor. In this case the ds18b20. 
The Seconds is for a phtocell.
And the third is for a led.
You can see a small demonstration on Reddit: https://www.reddit.com/r/arduino/comments/7ito0w/i_made_a_simple_menu_to_read_and_display/?ref=share&ref_source=link
*/
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
const int down = 4;  // this is the down Button
const int ok =2 ;    // this is the ok Button
const int up = 7;   // this is the up Button
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

  if(downState == HIGH)//because of this Counter the program knews on which Menu you are at the moment
  {
    
    counter--;
  }
  else if(upState == HIGH)
  {
    counter++;
  }

  if(counter==0) // when the counter is 0 it automatically changes it to 3
  {
    counter = 3;
  }
  if(counter==4)// when the counter is 4 it automatically changes it to 1
  {
    counter =1;
  }

  if(okState == HIGH) // when you press the ok Button it moves into this part of the code.
  {
 
    if(counter==1)        // when the counter is zero it moves into this part.
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
        downState = digitalRead(down); // when the user presses the down Button the program goes ot of this part of the code.
      }
      display.clearDisplay();
    }
    if(counter==2)
    {
      while(downState==LOW)
      {
        int brightness = analogRead(light); 

        
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("Brightness: ");
        display.println(brightness);
        display.display();

        downState = digitalRead(down);
        delay(200);
      }
      display.clearDisplay();
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
      display.clearDisplay();
      digitalWrite(led, LOW);
    }
  }

  //that are the Menus
  
  if(counter==1)     
  {
    display.setCursor(0,0);
    display.print("tempS: You are here");
    display.setCursor(0,10);
    display.print("lights:");
    display.setCursor(0,20);
    display.print("led:");
    display.display();
    delay(400);
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
    delay(400);
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
    delay(400);
  }
  display.clearDisplay();
}
