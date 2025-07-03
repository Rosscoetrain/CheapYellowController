#ifndef ESP32_DIS02170A_H
#define ESP32_DIS02170A_H

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
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <driver/i2c.h>


class LGFX : public lgfx::LGFX_Device {
public:

  lgfx::Bus_RGB _bus_instance;
  lgfx::Panel_RGB _panel_instance;
  lgfx::Touch_GT911 _touch_instance;

  LGFX(void) {
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

    {
      auto cfg = _panel_instance.config_detail();

      cfg.use_psram = 1;

      _panel_instance.config_detail(cfg);
    }

    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;
      cfg.pin_d0 = GPIO_NUM_21;    // B0
      cfg.pin_d1 = GPIO_NUM_47;    // B1
      cfg.pin_d2 = GPIO_NUM_48;   // B2
      cfg.pin_d3 = GPIO_NUM_45;    // B3
      cfg.pin_d4 = GPIO_NUM_38;    // B4
      cfg.pin_d5 = GPIO_NUM_9;    // G0
      cfg.pin_d6 = GPIO_NUM_10;    // G1
      cfg.pin_d7 = GPIO_NUM_11;    // G2
      cfg.pin_d8 = GPIO_NUM_12;   // G3
      cfg.pin_d9 = GPIO_NUM_13;   // G4
      cfg.pin_d10 = GPIO_NUM_14;   // G5
      cfg.pin_d11 = GPIO_NUM_7;  // R0
      cfg.pin_d12 = GPIO_NUM_17;  // R1
      cfg.pin_d13 = GPIO_NUM_18;  // R2
      cfg.pin_d14 = GPIO_NUM_3;  // R3
      cfg.pin_d15 = GPIO_NUM_46;  // R4

      cfg.pin_henable = GPIO_NUM_42;
      cfg.pin_vsync = GPIO_NUM_41;
      cfg.pin_hsync = GPIO_NUM_40;
      cfg.pin_pclk = GPIO_NUM_39;
      cfg.freq_write = 21000000;
      //cfg.freq_write = 13990000;
      //cfg.freq_write = 14000000;

      cfg.hsync_polarity = 0;
      cfg.hsync_front_porch = 8;
      cfg.hsync_pulse_width = 4;
      cfg.hsync_back_porch = 8;
      cfg.vsync_polarity = 0;
      cfg.vsync_front_porch = 8;
      cfg.vsync_pulse_width = 4;
      cfg.vsync_back_porch = 8;
      cfg.pclk_idle_high = 1;

      _bus_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);



    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = 800;
      cfg.y_min = 0;
      cfg.y_max = 480;
      cfg.pin_int = -1;
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;
      cfg.i2c_port = I2C_NUM_0;
      cfg.pin_sda = GPIO_NUM_15;
      cfg.pin_scl = GPIO_NUM_16;
      cfg.pin_rst = 3; // -1;
      cfg.freq = 400000;
      cfg.i2c_addr = 0x5D;  // 0x5D , 0x14
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);
  }
};


LGFX *gfx = new LGFX();


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

//TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

//Initialize the Touch Controller
void initTouch()
{
//  ts.begin();
//  ts.setRotation(ROTATION);
}

void my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
/*
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
*/
}



#endif // ESP32_DIS02170A_H
