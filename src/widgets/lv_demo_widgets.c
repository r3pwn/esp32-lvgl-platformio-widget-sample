#include "screens/screen_base.h"
#include "screens/time_fragment.h"
#include "screens/button_counter_fragment.h"

#if LV_MEM_CUSTOM == 0 && LV_MEM_SIZE < (38ul * 1024ul)
#error Insufficient memory for lv_demo_widgets. Please set LV_MEM_SIZE to at least 38KB (38ul * 1024ul).  48KB is recommended.
#endif

/**********************
 *  STATIC VARIABLES
 **********************/
static disp_size_t disp_size;

static lv_obj_t *tv;
static lv_obj_t *calendar;
static lv_style_t style_text_muted;
static lv_style_t style_title;

static lv_obj_t *meter1;
static lv_obj_t *meter2;
static lv_obj_t *meter3;

static lv_obj_t *chart1;
static lv_obj_t *chart2;
static lv_obj_t *chart3;

static lv_chart_series_t *ser1;
static lv_chart_series_t *ser2;
static lv_chart_series_t *ser3;
static lv_chart_series_t *ser4;

static const lv_font_t *font_large;
static const lv_font_t *font_normal;

static uint32_t session_desktop = 1000;
static uint32_t session_tablet = 1000;
static uint32_t session_mobile = 1000;

void lv_demo_widgets(void)
{
  if (LV_HOR_RES <= 320)
    disp_size = DISP_SMALL;
  else if (LV_HOR_RES < 720)
    disp_size = DISP_MEDIUM;
  else
    disp_size = DISP_LARGE;

  font_large = LV_FONT_DEFAULT;
  font_normal = LV_FONT_DEFAULT;

  // set tab size to 0
  lv_coord_t tab_size = 0;
  if (disp_size == DISP_LARGE)
  {
#if LV_FONT_MONTSERRAT_24
    font_large = &lv_font_montserrat_24;
#else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_24 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_16
    font_normal = &lv_font_montserrat_16;
#else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_16 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
  }
  else if (disp_size == DISP_MEDIUM)
  {
#if LV_FONT_MONTSERRAT_20
    font_large = &lv_font_montserrat_20;
#else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_20 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_14
    font_normal = &lv_font_montserrat_14;
#else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_14 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
  }
  else
  { /* disp_size == DISP_SMALL */
#if LV_FONT_MONTSERRAT_18
    font_large = &lv_font_montserrat_18;
#else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_18 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
#if LV_FONT_MONTSERRAT_12
    font_normal = &lv_font_montserrat_12;
#else
    LV_LOG_WARN("LV_FONT_MONTSERRAT_12 is not enabled for the widgets demo. Using LV_FONT_DEFAULT instead.");
#endif
  }

#if LV_USE_THEME_DEFAULT
  lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
                        font_normal);
#endif

  lv_style_init(&style_text_muted);
  lv_style_set_text_opa(&style_text_muted, LV_OPA_50);

  lv_style_init(&style_title);
  lv_style_set_text_font(&style_title, font_large);

  tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, tab_size);

  lv_obj_set_style_text_font(lv_scr_act(), font_normal, 0);

  if (disp_size == DISP_LARGE)
  {
    lv_obj_t *tab_btns = lv_tabview_get_tab_btns(tv);
    lv_obj_set_style_pad_left(tab_btns, LV_HOR_RES / 2, 0);
    lv_obj_t *logo = lv_img_create(tab_btns);
    LV_IMG_DECLARE(img_lvgl_logo);
    lv_img_set_src(logo, &img_lvgl_logo);
    lv_obj_align(logo, LV_ALIGN_LEFT_MID, -LV_HOR_RES / 2 + 25, 0);

    lv_obj_t *label = lv_label_create(tab_btns);
    lv_obj_add_style(label, &style_title, 0);
    lv_label_set_text(label, "LVGL v8");
    lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

    label = lv_label_create(tab_btns);
    lv_label_set_text(label, "Widgets demo");
    lv_obj_add_style(label, &style_text_muted, 0);
    lv_obj_align_to(label, logo, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
  }

  lv_obj_t *t1 = lv_tabview_add_tab(tv, "Time");
  lv_obj_t *t2 = lv_tabview_add_tab(tv, "Button");

  create_time_fragment(t1);
  create_button_counter_fragment(t2);
}
