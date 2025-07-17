/*
 *
 * @file Elecrow_DIS02170A_portrait_C.h
 * 
 * 
 *
 */

#ifndef ELECROW_DIS02170A_PORTRAIT_C_H
#define ELECROW_DIS02170A_PORTRAIT_C_H

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <driver/i2c.h>

#include <Wire.h>

/* Expand IO */
#include <TCA9534.h>
TCA9534 ioex;


//#include <Adafruit_SSD1306.h>
//#include <Adafruit_GFX.h>

#define LCD_H_RES 480
#define LCD_V_RES 800

/*
#define GFX_BL 2 // default backlight pin, you may replace DF_GFX_BL to actual backlight pin
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

//#define I2C_SDA 15
//#define I2C_SCL 16

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
//      cfg.freq_write = 21000000;
        cfg.freq_write = 16000000;
//      cfg.freq_write = 13990000;
//      cfg.freq_write = 14000000;

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
      cfg.x_min = 800;
      cfg.x_max = 0;
      cfg.y_min = 480;
      cfg.y_max = 0;
      cfg.offset_rotation = 2;

      cfg.pin_int = -1;
      cfg.bus_shared = false;
//      cfg.offset_rotation = 0;
//      cfg.offset_rotation = 1;
//      cfg.offset_rotation = 3;
      cfg.i2c_port = I2C_NUM_0;
      cfg.pin_sda = GPIO_NUM_15;
      cfg.pin_scl = GPIO_NUM_16;
      cfg.pin_rst = -1;
      cfg.freq = 400000;
      cfg.i2c_addr = 0x5D;  // 0x5D , 0x14
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);
  }
};


LGFX gfx;


// Version 1.2 updated the control of backlight on the basis of the original, the backlight of version 1.2 is controlled by STC8H1K28 microcontroller,
// and the backlight is lit in the program by sending the value to this microcontroller address (0x30).
// The values are 0x05, 0x06, 0x07, 0x08, 0x09 and 0x10, where 0x05 switches off the backlight and 0x10 is the maximum brightness.

void setBacklight(uint8_t brightness)
 {
  uint8_t b = 0x06 + (brightness / 55);
//  Serial.print("brightness : "); Serial.println(b, HEX);
  Wire.beginTransmission(0x30);
  Wire.write(b);          // maximum brightness
  Wire.endTransmission();
 }

bool i2cScanForAddress(uint8_t address)
{
  Wire.beginTransmission(address);
//  byte error = Wire.endTransmission();
//  Serial.print("Wire end = ");Serial.println(error);
  return (Wire.endTransmission() == 0);
}


void init_Hardware()
 {
// Version 1.2 updated the control of backlight on the basis of the original, the backlight of version 1.2 is controlled by STC8H1K28 microcontroller,
// and the backlight is lit in the program by sending the value to this microcontroller address (0x30).
// The values are 0x05, 0x06, 0x07, 0x08, 0x09 and 0x10, where 0x05 switches off the backlight and 0x10 is the maximum brightness.

  if (i2cScanForAddress(0x30)) // new V1.2
  {
    Wire.beginTransmission(0x30);
    Wire.write(0x10);          // maximum brightness
    Wire.endTransmission();
    Serial.println("Beep???");
    Wire.beginTransmission(0x30);
    Wire.write(0x18);          // beep???
    Wire.endTransmission();
  }
  else
  {
    ioex.attach(Wire);
    ioex.setDeviceAddress(0x18);
    ioex.config(1, TCA9534::Config::OUT);
    ioex.config(2, TCA9534::Config::OUT);

    // Turn on backlight
    ioex.output(1, TCA9534::Level::H);

    delay(20);
    ioex.output(2, TCA9534::Level::H);
    delay(100);
    pinMode(1, INPUT);
    // end
  }

 }


void beep(uint16_t duration)
 {
  Wire.beginTransmission(0x30);
  Wire.write(0x15);
  Wire.endTransmission();
  delay(duration);
  Wire.beginTransmission(0x30);
  Wire.write(0x16);
  Wire.endTransmission();
 }


/*
 //create a touch object
void my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{

  if (ts.pressed()) 
  {
    data->state = LV_INDEV_STATE_PR;
//    data->point.x = ts.X(); //map(p.x, touch_map_x1, touch_map_x2, 1, SCREEN_WIDTH);
//    data->point.y = ts.Y(); //map(p.y, touch_map_y1, touch_map_y2, 1, SCREEN_HEIGHT);

    data->point.x = map(ts.RawY(), touch_map_x1, touch_map_x2, 1, SCREEN_WIDTH);
    data->point.y = map(ts.RawX(), touch_map_y1, touch_map_y2, 1, SCREEN_HEIGHT);
 //   Serial.printf("RawX: %d X: %d - RawY: %d Y: %d\n", ts.RawX(), data->point.x, ts.RawY(), data->point.y );
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }

}
*/

 #endif // ELECROW_DIS02170A_PORTRAIT_C_H
 