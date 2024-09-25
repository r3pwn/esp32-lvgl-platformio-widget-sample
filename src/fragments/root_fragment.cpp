#include <fragments/fragment_base.h>
#include <fragments/root_fragment.h>
#include <fragments/time_fragment.h>
#include <fragments/button_counter_fragment.h>

static disp_size_t disp_size;

static lv_obj_t *tv;
static lv_style_t style_title;

static const lv_font_t *font_large;
static const lv_font_t *font_normal;

void Root_Fragment::create_fragment()
{
  if (LV_HOR_RES <= 320)
    disp_size = DISP_SMALL;
  else if (LV_HOR_RES < 720)
    disp_size = DISP_MEDIUM;
  else
    disp_size = DISP_LARGE;

  font_large = LV_FONT_DEFAULT;
  font_normal = LV_FONT_DEFAULT;

#if LV_USE_THEME_DEFAULT
  lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
                        font_normal);
#endif

  lv_style_init(&style_title);
  lv_style_set_text_font(&style_title, font_large);

  // set tab size to 0
  tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, (lv_coord_t)0);

  lv_obj_set_style_text_font(lv_scr_act(), font_normal, 0);

  lv_obj_t *t1 = lv_tabview_add_tab(tv, "Time");
  lv_obj_t *t2 = lv_tabview_add_tab(tv, "Button");

  Time_Fragment::create_fragment(t1);
  Button_Counter_Fragment::create_fragment(t2);
}
