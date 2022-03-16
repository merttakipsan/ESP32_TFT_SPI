#include <Arduino.h>


#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>

#include "takipsan_mini.c"

#include "bluetooth_logo.c"
#include "bluetooth_no_icon.c"

#include "no_wifi.c"
#include "wifi_logo.c"

#define TFT_DC     21       // register select (stands for Data Control perhaps!)
#define TFT_RST   22         // Display reset pin, you can also connect this to the ESP32 reset
                            // in which case, set this #define pin to -1!
#define TFT_CS   2       // Display enable (Chip select), if not enabled will not talk on SPI bus





Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);  
#define ST7735_TFTWIDTH  128
#define ST7735_TFTHEIGHT   128
float p = 3.1415926;
int kontrol=0;
int rotate=2;
void setup(void) {
  tft.init();   // initialize a ST7735S chip,
   tft.setRotation(rotate);
    
}

void loop() {  
  //for(uint16_t rotation=0; rotation<4;rotation++)
    //Demo(rotation);
    while(kontrol==0){
    tft.setRotation(rotate);
    tft.fillScreen(ST7735_WHITE);
    tft.drawRGBBitmap(5, 0, takipsan_mini, 120, 120);
     delay(2000);
     
      tft.fillScreen(ST7735_WHITE);
      tft.drawRGBBitmap(92, 3, bluetooth_logo, 16, 16);
      tft.drawRGBBitmap(110, 2, wifi_logo, 16, 16);
      tft.setCursor(5,5);
      tft.setTextSize(0);
      tft.setTextColor(ST7735_BLACK);
      tft.setTextWrap(false);
      tft.print("Takipsan");
      kontrol=1;
    }
while(kontrol==1){
  
  for(int o=0;o<99;o++){
 tft.fillRect(40, 50, 60, 60, 0xFFFF);
  tft.setCursor(40,50);
  
  tft.setTextColor(ST7735_BLACK);
  tft.setTextSize(5);
   
    tft.print(o);
    delay(200);
  }
  kontrol=2;
}
while(kontrol==2){
  if(rotate==2){
   rotate=3;
   kontrol=0;
  }
  else if(rotate==3){
     rotate=2;
     kontrol=0;
  }
}
  
   
}

/*
void Demo(uint16_t rotation)

{

  tft.setRotation(rotation);
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  delay(500);

  // large block of text
  tft.fillScreen(ST7735_BLACK);
 
  testdrawtext("This is a test of some very log text that I written for the sole purpose of checking if the display displays very long text correctly.", ST7735_WHITE);
  delay(1000);

  // tft print function!
  tftPrintTest();
  delay(4000);

  // a single pixel
  tft.drawPixel(tft.width()/2, tft.height()/2, ST7735_GREEN);
  delay(500);

  testdrawrects(ST7735_GREEN);
  delay(500);

  testfillrects(ST7735_YELLOW, ST7735_MAGENTA);
  delay(500);

  tft.fillScreen(ST7735_BLACK);
  testfillcircles(10, ST7735_BLUE);
  testdrawcircles(10, ST7735_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(1000);
  for(int i=2;i>0;i--)
  {
    tft.invertDisplay(true);
    delay(500);
    tft.invertDisplay(false);
    delay(500);
  }
}



void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(5,5);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("I'm running");
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(3);
  tft.println("on a");
  tft.setTextColor(ST7735_BLUE);
  tft.println("ESP32");
  tft.setTextSize(4);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Ha ha!");
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST7735_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST7735_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST7735_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST7735_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}
void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}
void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST7735_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(ST7735_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}
*/
