#ifndef CALLBACKS_H
#define CALLBACKS_H

/*
 ********************************************************************************************************
 * Call-Back routine for Textarea fields
 ********************************************************************************************************
*/
static void ta_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * ta = lv_event_get_target(e);
  lv_obj_t * kb = (lv_obj_t *)lv_event_get_user_data(e);
  if(code == LV_EVENT_FOCUSED) 
  { 
    if(rosterMode != GUEST_ACTIVE)
    {
      lv_keyboard_set_textarea(kb, ta);
      lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
  }
  if(code == LV_EVENT_READY)
  {
    lv_keyboard_set_textarea(kb, NULL);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
  }
}

/*
 *
 * These set up the functions used by the EEZ Studio graphics.
 * 
 */

void init_callbacks()
 {
  lv_obj_set_parent(objects.btn_stop, lv_layer_top());
  lv_obj_set_parent(objects.btn_power, lv_layer_top());
  lv_obj_set_parent(objects.btn_home, lv_layer_top());
  lv_obj_set_parent(objects.img_wifi, lv_layer_top());
  lv_obj_set_parent(objects.h_line, lv_layer_top());

  lv_textarea_add_text(objects.ta_password, netwks[0].password.c_str());
  lv_textarea_add_text(objects.ta_ip_address, netwks[0].ipAddress.c_str());
  lv_textarea_add_text(objects.ta_port, netwks[0].nwPort.c_str());

    // Callback definitions - WiFi
  lv_obj_add_event_cb(objects.ta_ssid, ta_event_cb, LV_EVENT_ALL, objects.kb_alpha );
  lv_obj_add_event_cb(objects.ta_password, ta_event_cb, LV_EVENT_ALL, objects.kb_alpha );
  lv_obj_add_event_cb(objects.ta_ip_address, ta_event_cb, LV_EVENT_ALL, objects.kb_numeric );
  lv_obj_add_event_cb(objects.ta_port, ta_event_cb, LV_EVENT_ALL, objects.kb_numeric );
  lv_obj_add_event_cb(objects.dd_ssids, dd_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.dd_locos, dd_locos_cb, LV_EVENT_ALL, NULL);

    // Callback definitions - Menu, Throttle, Roster
  lv_obj_add_event_cb(objects.menu_mtx, menu_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.throttle_mtx, throttle_selection_handler_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.function_mtx, functions_cb, LV_EVENT_PRESSED, NULL);
  lv_obj_add_event_cb(objects.function_mtx, functions_cb, LV_EVENT_RELEASED, NULL);
  lv_obj_add_event_cb(objects.track_mtx, track_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.cv_mtx, cv_cb, LV_EVENT_ALL, NULL);

    // Callback definitions for Edit Loco  
  lv_obj_add_event_cb(objects.btn_s0,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s1,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s2,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s3,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s4,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s5,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s6,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s7,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s8,function_name_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(objects.btn_s9,function_name_cb, LV_EVENT_ALL, NULL);

  lv_obj_add_event_cb(objects.tbl_roster, tbl_roster_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(objects.ta_name, ta_event_cb, LV_EVENT_ALL, objects.a_kbd_edit_loco );
  lv_obj_add_event_cb(objects.ta_address, ta_event_cb, LV_EVENT_ALL, objects.n_kbd_edit_loco );
  lv_obj_add_event_cb(objects.ta_fnum, ta_event_cb, LV_EVENT_ALL, objects.n_kbd_edit_loco );
  lv_obj_add_event_cb(objects.ta_fname, ta_event_cb, LV_EVENT_ALL, objects.a_kbd_edit_loco );
  lv_obj_add_event_cb(objects.ta_guest_address, ta_event_cb, LV_EVENT_ALL, objects.kbd_guest );

  lv_obj_add_event_cb(objects.ta_adr, ta_event_cb, LV_EVENT_ALL, objects.kbd_program );
  lv_obj_add_event_cb(objects.ta_cvn, ta_event_cb, LV_EVENT_ALL, objects.kbd_program );
  lv_obj_add_event_cb(objects.ta_cvv, ta_event_cb, LV_EVENT_ALL, objects.kbd_program );

  lv_obj_add_event_cb(objects.ta_tft_backlight, ta_event_cb, LV_EVENT_ALL, objects.kbd_config );
  lv_obj_add_event_cb(objects.ta_wifi_timeout, ta_event_cb, LV_EVENT_ALL, objects.kbd_config );
 }


#endif // CALLBACKS_H

