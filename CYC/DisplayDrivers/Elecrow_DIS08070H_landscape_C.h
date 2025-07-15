/*
 *
 * @file Elecrow_DIS08070H_C.h
 * 
 * 
 *
 */


#ifndef ESP32_DIS08070H_C_H
#define ESP32_DIS08070H_C_H


//#include <PCA9557.h>
#include <lvgl.h>
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <driver/i2c.h>

#include <Wire.h>



#define LCD_H_RES 800
#define LCD_V_RES 480



#define GFX_BL 2 // default backlight pin, you may replace DF_GFX_BL to actual backlight pin
/*
#define ROTATION 1
#define SCREEN_WIDTH 480          //Using EEZ Orientation
#define SCREEN_HEIGHT 800
#define DISPLAY_WIDTH 800         //Physical Display Properties ex rotation
#define DISPLAY_HEIGHT 480
*/
#define AUTO_FLUSH true
/*
#define TFT_BACKLIGHT 250
*/
#define NAME_COL_WIDTH 360
/*
#define RGB_PANEL
*/



class LGFX : public lgfx::LGFX_Device
{
public:

  lgfx::Bus_RGB     _bus_instance;
  lgfx::Panel_RGB   _panel_instance;
  lgfx::Touch_GT911 _touch_instance;

  LGFX(void)
  {


    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;
      
      cfg.pin_d0  = GPIO_NUM_15; // B0
      cfg.pin_d1  = GPIO_NUM_7;  // B1
      cfg.pin_d2  = GPIO_NUM_6;  // B2
      cfg.pin_d3  = GPIO_NUM_5;  // B3
      cfg.pin_d4  = GPIO_NUM_4;  // B4
      
      cfg.pin_d5  = GPIO_NUM_9;  // G0
      cfg.pin_d6  = GPIO_NUM_46; // G1
      cfg.pin_d7  = GPIO_NUM_3;  // G2
      cfg.pin_d8  = GPIO_NUM_8;  // G3
      cfg.pin_d9  = GPIO_NUM_16; // G4
      cfg.pin_d10 = GPIO_NUM_1;  // G5
      
      cfg.pin_d11 = GPIO_NUM_14; // R0
      cfg.pin_d12 = GPIO_NUM_21; // R1
      cfg.pin_d13 = GPIO_NUM_47; // R2
      cfg.pin_d14 = GPIO_NUM_48; // R3
      cfg.pin_d15 = GPIO_NUM_45; // R4

      cfg.pin_henable = GPIO_NUM_41;
      cfg.pin_vsync   = GPIO_NUM_40;
      cfg.pin_hsync   = GPIO_NUM_39;
      cfg.pin_pclk    = GPIO_NUM_0;
      cfg.freq_write  = 15000000;

      cfg.hsync_polarity    = 0;
      cfg.hsync_front_porch = 40;
      cfg.hsync_pulse_width = 48;
      cfg.hsync_back_porch  = 40;
      
      cfg.vsync_polarity    = 0;
      cfg.vsync_front_porch = 1;
      cfg.vsync_pulse_width = 31;
      cfg.vsync_back_porch  = 13;

      cfg.pclk_active_neg   = 1;
      cfg.de_idle_high      = 0;
      cfg.pclk_idle_high    = 0;

      _bus_instance.config(cfg);
    }
            {
      auto cfg = _panel_instance.config();
      cfg.memory_width  = 800;
      cfg.memory_height = 480;
      cfg.panel_width  = 800;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      _panel_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);
    setPanel(&_panel_instance);

    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = 800;
      cfg.y_min = 0;
      cfg.y_max = 480;

      cfg.pin_int = -1;
      cfg.bus_shared = false;
//      cfg.offset_rotation = 0;
//      cfg.offset_rotation = 1;
//      cfg.offset_rotation = 2;
//      cfg.offset_rotation = 3;
      cfg.i2c_port = I2C_NUM_0;
      cfg.pin_sda = GPIO_NUM_19;
      cfg.pin_scl = GPIO_NUM_20;
      cfg.pin_rst = -1;
      cfg.freq = 400000;
      cfg.i2c_addr = 0x5D;  // 0x5D , 0x14
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }
  }
};


LGFX gfx;





void setBacklight(uint8_t brightness)
 {
  ledcSetup(0, 5000, 8);                          //If using ESP Boards 2.0.x LEDChannel, frequency, resolution
  ledcAttachPin(GFX_BL, 0);                       //If using ESP Boards 2.0.x Pin, LEDChannel
  ledcWrite(0, brightness);                       //If using ESP Boards 2.0.x LEDChannel, Brightness* 0-255

//  ledcAttachChannel(GFX_BL, 5000, 8, 0);          //If using ESP Boards 3.x Pin, Frequency, Resolution, Channel
//  ledcWrite(GFX_BL, brightness);                  //If using ESP Boards 3.x Pin, Brightness
 }


void init_Hardware()
 {

 }

#endif // ESP32_DIS08070H_C_H
