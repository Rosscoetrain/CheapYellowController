/*
 *
 * @file elecrow_setup.h
 * 
 */

#ifndef ELECROW_SETUP_H
#define ELECROW_SETUP_H

#include "callbacks.h"

/* Change to your screen resolution */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf;
static lv_color_t *buf1;

uint16_t touch_x, touch_y;


//  Display refresh
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  if (gfx.getStartCount() > 0) {
    gfx.endWrite();
  }
  gfx.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::rgb565_t *)&color_p->full);

  lv_disp_flush_ready(disp);  //	Tell lvgl that the refresh is complete
}


//  Read touch
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
  data->state = LV_INDEV_STATE_REL;// The state of data existence when releasing the finger
  bool touched = gfx.getTouch( &touch_x, &touch_y );
  if (touched)
  {
    data->state = LV_INDEV_STATE_PR;

    //  Set coordinates
    data->point.x = touch_x;
    data->point.y = touch_y;
//    Serial.print("x = ");
//    Serial.println(touch_x);
//    Serial.print("y = ");
//    Serial.println(touch_y);
#if defined ESP32DIS02170A || defined ESP32DIS02170A_LS
    beep(250);
#endif
  }
}


/*
//
//****************************************************************************************************
// Read all LittleFS data files and populate working arrays
//
// This needs to go at the end of setup() in main.cpp
//*****************************************************************************************************
//
*/

void init_LittleFS()
 {
  LittleFS.begin();
  delay(100);

  Serial.println("Now loading Selected Loco IDs");
  populateSelected("/throttleids.txt");

  delay(100);

  Serial.println("Now populating Locos...");
  populateLocoArray("/locos.txt");

  // Set all function numbers to 255
  for(int i = 0; i < NUM_LOCOS; i++)
   {
    for(int j = 0; j < NUM_FUNC_SLOTS; j++) strcpy(funcNumber[i][j], "255");
   }
  
  Serial.println("Now populating Functions");
  populateLocoFunctions("/functions.txt");

  Serial.println("Now loading List of Credentials");
  populateCredentials("/credentials.txt");
    
  Serial.println("Now Populating the Roster...");
  for(int i = 0; i < locoCount; i++)
   {
    lv_table_set_cell_value(objects.tbl_roster, i, 0, locoName[i]);
    lv_table_set_cell_value(objects.tbl_roster, i, 1, locoAddress[i]);
   }
  Serial.println("Roster Populated");

  rosterMode = GUEST_INACTIVE;

  lv_table_set_col_width(objects.tbl_roster, 0, NAME_COL_WIDTH);
 }




 void setup()
{
  Serial.begin(115200); 

  pinMode(19, OUTPUT);//uart1

  Wire.begin(I2C_SDA, I2C_SCL);
  delay(100);

// Init additional display hardware.
  init_Hardware();


// Init Display
  if (!gfx.init())
   {
    Serial.println("gfx failed");
    while (1)
     {
      
     }
   }

  gfx.initDMA();

#if !defined ESP32DIS02170A_LS && !defined ESP32DIS08070H_LS
  gfx.setRotation(1);
#endif

  gfx.startWrite();
  gfx.fillScreen(TFT_BLACK);

  lv_init();
  // size_t buffer_size = sizeof(lv_color_t) * LCD_H_RES * LCD_V_RES;
  size_t buffer_size = sizeof(lv_color_t) * LCD_H_RES * LCD_V_RES * 4;
  buf = (lv_color_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_SPIRAM);
  buf1 = (lv_color_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_SPIRAM);

  lv_disp_draw_buf_init(&draw_buf, buf, buf1, LCD_H_RES * LCD_V_RES);

  // Initialize display
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  // Change the following lines to your display resolution
  disp_drv.hor_res = LCD_H_RES;
  disp_drv.ver_res = LCD_V_RES;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Initialize input device driver program
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  delay(100);
  gfx.fillScreen(TFT_BLACK);

// Init UI
  ui_init();

// callbacks init these are in the file callbacks.h
  init_callbacks();

  LittleFS.begin();
  delay(100);

  init_LittleFS();

  setBacklight(255);

#if defined ESP32DIS02170A || defined ESP32DIS02170A_LS
  beep(1000);
#endif

  Serial.println( "Setup done" );
}

#endif  // ELECROW_SETUP_H

