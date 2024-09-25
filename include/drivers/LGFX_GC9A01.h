#ifndef _LGFX_GC9A01_H
#define _LGFX_GC9A01_H

#include <LovyanGFX.hpp>

class LGFX_GC9A01 : public lgfx::LGFX_Device
{
  lgfx::Panel_GC9A01 _panel_instance;
  lgfx::Bus_SPI _bus_instance;

public:
  LGFX_GC9A01(void);
  void setBrightness(uint8_t brightness);
};

#endif