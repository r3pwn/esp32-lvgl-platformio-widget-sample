#define LGFX_USE_V1
#include <Arduino.h>
#include <lvgl.h>
#include <fragments/root_fragment.h>
#include <boards/esp32-2424s012.h>

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char *file, uint32_t line, const char *fn_name, const char *dsc)
{
  Serial.printf("%s(%s)@%d->%s\r\n", file, fn_name, line, dsc);
  Serial.flush();
}
#endif

void setup()
{
  Serial.begin(115200); /* prepare for possible serial debug */

  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

#ifdef BOARD_ESP32_2424S012
  ESP32_2424S012::init();
#endif

  create_root_view();
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}