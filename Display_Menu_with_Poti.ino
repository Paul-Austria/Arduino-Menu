// A simple Menu Program made by KspPaul
/*This project is a Arduino Menu which can be controlled with two buttons and one Potentiometer (The other Code uses three Buttons)
*  
* The first Menu is for a temperature Sensor. In this case the ds18b20. 
* The Seconds is for a phtocell.
* And the third is for a led.
* You can see a small demonstration on Reddit: https://www.reddit.com/r/arduino/comments/7ito0w/i_made_a_simple_menu_to_read_and_display/?ref=share&ref_source=link
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
const int light = A0; // this is for the photocell
const int led = 8; // the Pin for the led
const int poti = A2; // this is the potentiometer


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {                

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  

  pinMode(down, INPUT);
  pinMode(ok, INPUT);
  pinMode(led, OUTPUT);
  
  display.setTextSize(0.5);
  display.setTextColor(WHITE);

  sensors.begin(); 
}


void loop() {
  int okState = digitalRead(ok);
  int potiValue = analogRead(poti);
  int downState = digitalRead(down);


Serial.println(down);
  if(okState == HIGH) // when you press the ok Button it moves into this part of the code.
  {
 
    if(counter==1)        // when the counter is zero it moves into this part.
    {
      Serial.println("ok");
     
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
  
  if(potiValue<=341)     
  {
    display.setCursor(0,0);
    display.print("tempS: You are here");
    display.setCursor(0,10);
    display.print("lights:");
    display.setCursor(0,20);
    display.print("led:");
    display.display();

    counter=1;
    
    delay(400);
  }
  if(potiValue<=682 && potiValue>341)
  {
    display.setCursor(0,0);
    display.print("tempS:");
    display.setCursor(0,10);
    display.print("lights: You are here");
    display.setCursor(0,20);
    display.print("led:");
    display.display();

    counter=2;
    
    delay(400);
  }
  if(potiValue>682)   
  {
    display.setCursor(0,0);
    display.print("tempS:");
    display.setCursor(0,10);
    display.print("lights:");
    display.setCursor(0,20);
    display.print("led: You are here");
    display.display();

    counter=3;
    
    delay(400);
  }
  display.clearDisplay();
}
