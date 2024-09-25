#ifndef SCREEN_BASE_H
#define SCREEN_BASE_H

#include <lvgl.h>

typedef enum
{
  DISP_SMALL,
  DISP_MEDIUM,
  DISP_LARGE,
} disp_size_t;

class Fragment_Base
{
public:
  static void create_fragment(lv_obj_t *parent);
};

#endif /*SCREEN_BASE_H*/
