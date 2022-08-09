#include <M5Stack.h>


#define TFT_GREY 0x5AEB


uint32_t targetTime = 0;                    // for next 1 second timeout

int hh = 0, mm = 0; 
int ss = 0, cs = 0; // Get H, M, S from compile time


byte omm = 99, oss = 99, ocs = 99;
byte xcolon = 0, xsecs = 0, xcs = 0;
unsigned int colour = 0;


void setup() {
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  targetTime = millis() + 10;
  draw(hh, mm, ss, cs);
}

int timestoper = 0;
void loop() {
  if (M5.BtnA.wasPressed()){
    timestoper = 1;
  }
  if (M5.BtnB.wasPressed()){
    timestoper = 0;
  }
  if (M5.BtnC.wasPressed()){
    hh = 0;
    mm = 0;
    ss = 0;
    cs = 0;
    timestoper = 0;
    draw(hh, mm, ss, cs);
  }
  if (targetTime < millis() && timestoper) {
    // Set next update for 1 second later
      cs ++;
      targetTime = millis() + 10;
      if (cs == 100) {
        cs = 0;
        ss++;
        if (ss == 60) {    // Check for roll-over
        ss = 0;          // Reset seconds to zero
        omm = mm;        // Save last minute time for display update
        mm++;            // Advance minute
        if (mm > 59) {   // Check for roll-over
          mm = 0;
          hh++;          // Advance hour
          if (hh > 23) { // Check for 24hr roll-over (could roll-over on13)
            hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
          }
         }
        }
      }
      draw(hh, mm, ss, cs);
    }
  M5.update();
}

void draw(int hh,int mm,int ss,int cs) {
  //Update digital time
      int xpos = 0;
      int ypos = 85; // Top left corner to clock text, about half way down
      int ysecs = ypos;
  
  
      if (omm != mm) { // Redraw hours and minutes time every minute
        omm = mm;
        // Draw hours and minutes
        // Add hours leading zero for 24 hr clock
        if (hh < 10) xpos += M5.Lcd.drawChar('0', xpos, ypos, 6); 
        xpos += M5.Lcd.drawNumber(hh, xpos, ypos, 6);             // Draw hours
        xcolon = xpos; // Save colon coord for later to flash on/off later
        xpos += M5.Lcd.drawChar(':', xpos, ypos - 6, 6);
        // Add minutes leading zero
        if (mm < 10) xpos += M5.Lcd.drawChar('0', xpos, ypos, 6); 
        xpos += M5.Lcd.drawNumber(mm, xpos, ypos, 6);         // Draw minutes
        xsecs = xpos; // Save seconds 'x' position for later display updates
      }
      if (oss != ss) { // Redraw seconds time every second
        oss = ss;
        xpos = xsecs;
  
  
        if (ss % 2) { // Flash the colons on/off
          // Set colour to grey to dim colon
          M5.Lcd.setTextColor(0x39C6, TFT_BLACK); 
          M5.Lcd.drawChar(':', xcolon, ypos - 6, 6);     // Hour:minute colon
          xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
          // Set colour back to yellow
          M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);    
        }
        else {
          M5.Lcd.drawChar(':', xcolon, ypos - 6, 6);     // Hour:minute colon
          xpos += M5.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
        }
        //Draw seconds
        // Add leading zero
        if (ss < 10) xpos += M5.Lcd.drawChar('0', xpos, ysecs, 6); 
        xpos += M5.Lcd.drawNumber(ss, xpos, ysecs, 6);       // Draw seconds
        xcs = xpos;
      }
     if (ocs != cs) {
      ocs = cs;
      xpos = xcs;
      xpos += M5.Lcd.drawChar('.', xpos, ysecs, 6);
      if (cs < 10) xpos += M5.Lcd.drawChar('0', xpos, ysecs, 6); 
      xpos += M5.Lcd.drawNumber(cs, xpos, ypos, 6);
     }
}
