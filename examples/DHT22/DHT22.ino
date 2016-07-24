/*
   DHT22.ino
   Reading humidity and temperature from DHT22  then display it
    
   This example code is in the public domain.
*/

#include <SSD1306.h>
#include <Wire.h>
#include <DHT.h>
#include "floatToString.h"

SSD1306  display(0x3c, 13, 12);

DHT dht(2, DHT22, 11);

float humidity, temperature;  // Values read from dht sensor

typedef void (*FrameCallback)(void);

void drawFrame0() {

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Initlize....");
}

void drawFrame1() {
  char buffer[25]; // just give it plenty to write out any values you want to test
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Humidity:");
  display.drawString(0, 10, floatToString(buffer, humidity, 2));
  display.drawString(0, 20, "Temperature:");
  display.drawString(0, 30, floatToString(buffer, temperature, 2));
}


FrameCallback frames[] = {drawFrame0, drawFrame1};
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // Initialising the UI will init the display too.
  display.init();
  
  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  dht.begin();
  // Display Main Screen
  display.clear();
  frames[0]();
  display.display();
  delay(1000);

}

void loop() {
    humidity = dht.readHumidity();          // Read humidity (percent)
    temperature = dht.readTemperature();     // Read temperature
    display.clear();
    frames[1]();
    display.display();
    delay(1000);
}
