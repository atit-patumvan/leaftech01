/*
   OLED.ino
   Read button press signal on pin 0 then flip and display frame
    
   This example code is in the public domain.
*/

#include <SSD1306.h>
#include <Wire.h>


SSD1306  display(0x3c, 13, 12);

typedef void (*FrameCallback)(void);

int f1 = 0; //Frame flip Flag 1
int f2 = 0; //Frame flip Flag 2
int frameloop = 1; // Frame display flag

void drawFrame0() {

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Frame 0");
  display.drawString(0, 40, "Press button to change");
  display.drawString(0, 50, "frame.");
}

void drawFrame1() {
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 10, "Frame 1");
  display.drawString(0, 40, "Press button to change");
  display.drawString(0, 50, "frame.");
}

void drawFrame2() {
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 20, "Frame 2");
  display.drawString(0, 40, "Press button to change");
  display.drawString(0, 50, "frame.");
}


FrameCallback frames[] = {drawFrame0, drawFrame1, drawFrame2};
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  pinMode(0, INPUT); // GPIO0, Page Flip Button

  // Initialising the UI will init the display too.
  display.init();

  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  // Display Main Screen
  display.clear();
  frames[0]();
  display.display();

}

void loop() {
  if (digitalRead(0) == LOW) {
    f1 = f1 ^ 1;
  }
  if (f1 != f2) {
    f2 = f1;
    display.clear();
    switch (frameloop) {
      case 1:
        frames[1]();
        frameloop = 2;
        break;
      case 2:
        frames[2]();
        frameloop = 1;
        break;
    }
    display.display();
    delay(500);
  }
}
