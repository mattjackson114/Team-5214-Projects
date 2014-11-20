//Created by: Matthew Jackson
// 11/19/14
//For use with 16x32 RGB Matrix Display 
#include <Adafruit_GFX.h>  
#include <RGBmatrixPanel.h> 

#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

#define CLK 8  
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
// Last parameter = 'true' enables double-buffering, for flicker-free,
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);

const char str[] PROGMEM = "Team 5214, The Mighty CavBots!";
int    textX   = matrix.width(),
textMin = sizeof(str) * -12,
hue     = 0;
int8_t ball[3][4] = {
  {  
    3,  0,  1,  1     }
  { 
    17, 15,  1, -1     }
  ,
  { 
    27,  4, -1,  1     }
};
static const uint16_t PROGMEM ballcolor[3] = {
  0x0080, 
  0x0002, 
  0x1000  
};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false); 
  matrix.setTextSize(2);
}

void loop() {
  byte i;
  matrix.fillScreen(0);

  for(i=0; i<3; i++) {
    matrix.fillCircle(ball[i][0], ball[i][1], 5, pgm_read_word(&ballcolor[i]));
    ball[i][0] += ball[i][2];
    ball[i][1] += ball[i][3];
    if((ball[i][0] == 0) || (ball[i][0] == (matrix.width() - 1)))
      ball[i][2] *= -1;
    if((ball[i][1] == 0) || (ball[i][1] == (matrix.height() - 1)))
      ball[i][3] *= -1;
  }

  matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
  matrix.setCursor(textX, 1);
  matrix.print(F2(str));
  if((--textX) < textMin) textX = matrix.width();
  hue += 7;
  if(hue >= 1536) hue -= 1536;
  matrix.swapBuffers(false);
}


