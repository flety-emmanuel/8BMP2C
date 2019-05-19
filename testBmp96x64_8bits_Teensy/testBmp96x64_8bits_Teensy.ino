//Test code to read bmp file over a 16 bit coded array
//By Enzo Niro - protongamer

#include <SPI.h>
#include <SSD_13XX.h>
#include "bmp_data.h" // bitmap arrays

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10
#define TFT_RS 8

uint8_t errorCode = 0;

SSD_13XX tft = SSD_13XX(TFT_CS, TFT_DC, TFT_RS);

//Prototype function
void drawBmp(uint8_t _x, uint8_t _y, const uint16_t bmp[64][96]);

void setup() {
Serial.begin(115200);

  tft.begin(false);

  //the following it's mainly for Teensy
  //it will help you to understand if you have choosed the
  //wrong combination of pins!
  errorCode = tft.getErrorCode();
  if (errorCode != 0) {
    Serial.print("Init error! ");
    if (bitRead(errorCode, 0)) Serial.print("MOSI or SCLK pin mismach!\n");
    if (bitRead(errorCode, 1)) Serial.print("CS or DC pin mismach!\n");
  }


  drawBmp(0,0,logo,96,64); //Read and display logo array at coordinate XY(0,0)

}


void drawBmp(uint8_t _x, uint8_t _y, const uint8_t bmp[], uint8_t width, uint8_t height){//function to read bitmap array


uint8_t _w = _x, _h = height+_y;

uint32_t color,R,G,B;
  
for(int i = 0; i < (width*height); i++){

color = colorPalette[pgm_read_byte(&bmp[i])];
//convert to RGB565
R = color & 0xFF;
G = (color & 0xFF00) >> 8;
B = (color & 0xFF0000) >> 16;
R = map(R,0,255,0,31);
G = map(G,0,255,0,63);
B = map(B,0,255,0,31);

color = (R << 11) | (G << 5) | B;

tft.drawPixel(_w,_h,color);

_w++;
if(_w >= width+_x){
  _w = _x;
  _h--;
if(_h < _y){
  _h = height+_y;
}

}
 
}

}



void loop(void) {
//Do your personal code here :)
}

