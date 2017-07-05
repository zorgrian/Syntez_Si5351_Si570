#ifndef DISP_ILI9341_H
#define DISP_ILI9341_H

#include <Arduino.h>
#include "TRX.h"

class Display_ILI9341_SPI: public TRXDisplay {
  private:
    uint8_t tx;
  public:
	  void setup();
    void reset();
	  void Draw(TRX& trx);
	  void clear();
	  void DrawMenu(const char* title, const char** items, uint8_t selected, const char* help, uint8_t fontsize);
};

#endif
