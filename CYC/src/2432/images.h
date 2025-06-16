#include "../../defines.h"

#ifdef RES2432

#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_dcc_ex;
extern const lv_img_dsc_t img_6;
extern const lv_img_dsc_t img_x;
extern const lv_img_dsc_t img_lh0;
extern const lv_img_dsc_t img_lh1;
extern const lv_img_dsc_t img_rh0;
extern const lv_img_dsc_t img_rh1;
extern const lv_img_dsc_t img_ds0;
extern const lv_img_dsc_t img_ds1;
extern const lv_img_dsc_t img_ds2;
extern const lv_img_dsc_t img_ds3;
extern const lv_img_dsc_t img_dsl0;
extern const lv_img_dsc_t img_dsl1;
extern const lv_img_dsc_t img_dsu0;
extern const lv_img_dsc_t img_dsu1;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[15];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/

#endif // RES2432
