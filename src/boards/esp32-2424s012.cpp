#include <lvgl.h>
#include <boards/esp32-2424s012.h>
#include <drivers/LGFX_GC9A01.h>
#include <drivers/CST816D.h>

#define LCD_HEIGHT 240
#define LCD_WIDTH 240

#define I2C_SDA 4
#define I2C_SCL 5
#define TP_INT 0
#define TP_RST 1

#define off_pin 35
#define buf_size 100

// initialize device drivers (lcd and touchscreen)
LGFX_GC9A01 tft;
CST816D touch(I2C_SDA, I2C_SCL, TP_RST, TP_INT);

static const uint32_t screenWidth = LCD_WIDTH;
static const uint32_t screenHeight = LCD_HEIGHT;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[2][screenWidth * buf_size];

/* Display flushing */
void lv_disp_dma_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  if (tft.getStartCount() == 0)
  {
    tft.endWrite();
  }

  tft.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);

  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

/*Read the touchscreen input*/
void lv_input_read_cb(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  bool touched;
  uint8_t gesture;
  uint16_t touchX, touchY;

  touched = touch.getTouch(&touchX, &touchY, &gesture);

  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

#ifdef INVERT_DISPLAY
    data->point.x = screenWidth - touchX;
    data->point.y = screenHeight - touchY;
#else
    data->point.x = touchX;
    data->point.y = touchY;
#endif
  }
}

void ESP32_2424S012::init()
{
  Serial.println("Initializing ESP32_2424S012 board");

  tft.init();
  tft.initDMA();
  tft.setBrightness(50);

#ifdef INVERT_DISPLAY
  tft.setRotation(2);
#endif
  tft.startWrite();

  touch.begin();

  lv_disp_draw_buf_init(&draw_buf, buf[0], buf[1], screenWidth * buf_size);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = lv_disp_dma_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = lv_input_read_cb;
  lv_indev_drv_register(&indev_drv);
}