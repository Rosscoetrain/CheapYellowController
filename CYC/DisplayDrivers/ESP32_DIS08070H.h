#ifndef ESP32_JC8048W550C_H
#define ESP32_JC8048W550C_H

/*******************************************************************************
 * Start of LovyanGFX setting
 ******************************************************************************/

#define GFX_BL 2 // default backlight pin, you may replace DF_GFX_BL to actual backlight pin
#define ROTATION 1
#define SCREEN_WIDTH 480          //Using EEZ Orientation
#define SCREEN_HEIGHT 800
#define DISPLAY_WIDTH 800         //Physical Display Properties ex rotation
#define DISPLAY_HEIGHT 480
#define AUTO_FLUSH true

#define NAME_COL_WIDTH 360

#define TFT_BACKLIGHT 230

//#define GFX_DEV_DEVICE ESP32_8048W550
#define RGB_PANEL

#define TFT_BL 2




#define LGFX_AUTODETECT
#include <LGFX_AUTODETECT.hpp>

//#include <lv_demo.h>
#include <lvgl.h>

/*Change to your screen resolution*/
//static const uint16_t screenWidth  = 800;
//static const uint16_t screenHeight = 480;

//static lv_disp_draw_buf_t draw_buf;
//static lv_color_t buf[2][ screenWidth * 10 ];

LGFX gfx;




/*
LGFX::LGFX(void) {
  {
    auto cfg = _bus_instance.config();
    cfg.panel = &_panel_instance;

    cfg.pin_d0 = GPIO_NUM_15; // B0
    cfg.pin_d1 = GPIO_NUM_7;  // B1
    cfg.pin_d2 = GPIO_NUM_6;  // B2
    cfg.pin_d3 = GPIO_NUM_5;  // B3
    cfg.pin_d4 = GPIO_NUM_4;  // B4

    cfg.pin_d5 = GPIO_NUM_9;  // G0
    cfg.pin_d6 = GPIO_NUM_46; // G1
    cfg.pin_d7 = GPIO_NUM_3;  // G2
    cfg.pin_d8 = GPIO_NUM_8;  // G3
    cfg.pin_d9 = GPIO_NUM_16; // G4
    cfg.pin_d10 = GPIO_NUM_1; // G5

    cfg.pin_d11 = GPIO_NUM_14; // R0
    cfg.pin_d12 = GPIO_NUM_21; // R1
    cfg.pin_d13 = GPIO_NUM_47; // R2
    cfg.pin_d14 = GPIO_NUM_48; // R3
    cfg.pin_d15 = GPIO_NUM_45; // R4

    cfg.pin_henable = GPIO_NUM_41;
    cfg.pin_vsync = GPIO_NUM_40;
    cfg.pin_hsync = GPIO_NUM_39;
    cfg.pin_pclk = GPIO_NUM_0;
    cfg.freq_write = 15000000;

    cfg.hsync_polarity = 0;
    cfg.hsync_front_porch = 40;
    cfg.hsync_pulse_width = 48;
    cfg.hsync_back_porch = 40;

    cfg.vsync_polarity = 0;
    cfg.vsync_front_porch = 1;
    cfg.vsync_pulse_width = 31;
    cfg.vsync_back_porch = 13;

    cfg.pclk_active_neg = 1;
    cfg.de_idle_high = 0;
    cfg.pclk_idle_high = 0;

    _bus_instance.config(cfg);
  }
  {
    auto cfg = _panel_instance.config();
    cfg.memory_width = 800;
    cfg.memory_height = 480;
    cfg.panel_width = 800;
    cfg.panel_height = 480;
    cfg.offset_x = 0;
    cfg.offset_y = 0;
    _panel_instance.config(cfg);
  }
  _panel_instance.setBus(&_bus_instance);
  setPanel(&_panel_instance);
}
*/





/*******************************************************************************
 * Capacitive Touch
 ******************************************************************************/

#include <TAMC_GT911.h>

#define TOUCH_GT911_SCL 20
#define TOUCH_GT911_SDA 19
#define TOUCH_GT911_INT -1
#define TOUCH_GT911_RST 38

#define TOUCH_GT911_ROTATION ROTATION_NORMAL
#define TOUCH_MAP_X1 0
#define TOUCH_MAP_X2 480
#define TOUCH_MAP_Y1 800
#define TOUCH_MAP_Y2 0

int touch_last_x = 0, touch_last_y = 0;

TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

//Initialize the Touch Controller
void initTouch()
{
  ts.begin();
  ts.setRotation(ROTATION);
}

//Create the Touch object
void my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
  ts.read();
  if (ts.isTouched) 
  {
  //  TP_Point p = ts.getPoint();
    data->state = LV_INDEV_STATE_PR;
//    #if defined(TOUCH_SWAP_XY)
      touch_last_x = map(ts.points[0].y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, DISPLAY_HEIGHT - 1);
      touch_last_y = map(ts.points[0].x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, DISPLAY_WIDTH - 1);
//    #else
//      touch_last_x = map(ts.points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, DISPLAY_HEIGHT - 1, 0);
//      touch_last_y = map(ts.points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, DISPLAY_WIDTH - 1, 0);
//    #endif
    data->point.x = touch_last_x;
    data->point.y = touch_last_y;
    Serial.println(data->point.x);
    Serial.println(data->point.y);
    Serial.println();

    delay(100);
  }  
}

#endif
