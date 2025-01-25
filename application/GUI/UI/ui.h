/*
 * ui.h
 *
 *  Created on: Jan 25, 2025
 *      Author: hzaib
 */

#ifndef APPLICATION_GUI_UI_UI_H_
#define APPLICATION_GUI_UI_UI_H_

#include "lvgl/lvgl.h"


//ui_Main functions
// LVGL objects
extern lv_obj_t* ui_Main;
extern lv_obj_t* time_label;
extern lv_obj_t* date_label;
extern lv_obj_t* waiter_icon;
extern lv_obj_t* waiter_name_label;
extern lv_obj_t* tables_connected_label;
extern lv_obj_t* message_container;

extern void ui_Main_descroll_list();
extern void ui_Main_scroll_list();
extern void ui_Main_new_message(uint8_t tableNum, const char* timeStr);
extern void ui_Main_screen_init();





extern void ui_lvglTickHandler();
extern void ui_loop();
extern void ui_init();


#endif /* APPLICATION_GUI_UI_UI_H_ */
