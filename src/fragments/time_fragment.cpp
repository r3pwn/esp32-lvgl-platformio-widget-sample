#include <fragments/time_fragment.h>

static lv_style_t style_root;

void Time_Fragment::create_fragment(lv_obj_t *parent)
{
  lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW);

  lv_style_init(&style_root);
  lv_style_set_radius(&style_root, LV_RADIUS_CIRCLE);
  lv_style_set_bg_opa(&style_root, (lv_opa_t)0);
  lv_style_set_outline_color(&style_root, lv_color_lighten(lv_color_black(), (lv_opa_t)60));
  lv_style_set_outline_pad(&style_root, (lv_coord_t)10);
  lv_style_set_outline_width(&style_root, (lv_coord_t)4);
  lv_style_set_border_width(&style_root, (lv_coord_t)0);

  lv_obj_t *fragment_root = lv_obj_create(parent);
  lv_obj_set_width(fragment_root, lv_pct(100));
  lv_obj_set_height(fragment_root, lv_pct(100));
  lv_obj_add_style(fragment_root, &style_root, 0);

  lv_obj_t *label = lv_label_create(fragment_root);

  lv_label_set_text(label, "12:34:56");
  lv_obj_center(label);
}