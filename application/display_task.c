/*
 * display_task.c
 *
 *  Created on: Jul 27, 2024
 *      Author: hzaib
 */
/* RTOS header files */

#include <ti/sysbios/BIOS.h>

#include <pthread.h>

#include <ioc.h>

#include "sys_ctrl.h"

#include "ti_drivers_config.h"

#include <inc/hw_ccfg.h>
#include <inc/hw_ccfg_simple_struct.h>

/* Header files required for the temporary idle task function */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/drivers/GPIO.h>
#include <aon_rtc.h>
#include <prcm.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>
#include "Defines.h"

/* Header files required to enable instruction fetch cache */
#include <ti/drivers/dpl/HwiP.h>
#include "cpu.h"
#include "sensor.h"
#include <string.h>
#include "control_task.h"
#include "cui.h"
#include "api_mac.h"
#include "smsgs.h"
#include "st7789.h"
#include "ugui.h"
#include "string.h"
#include "stdio.h"
#include "time_clock.h"
#include "utc_clock.h"
#include <semaphore.h>
#include "jdllc.h"
#include "mac_util.h"


//#include "lv_port_disp.h"
//#include "lv_port_indev.h"


#include "LVGL_Library/lvgl/lvgl.h"
#include "LVGL_Library/ui/ui.h"
#include "LVGL_Library/ui/ui_helpers.h"

sem_t display_handle;

static const char noti_code[4][20] =
{
 "CALL",
 "WATER",
 "ORDER",
 "BILL",
};

static const char selection_menu_str[2][20] =
{
 "1)Notification",
 "2)Settings",

};

static const char setting_menu_str[2][25] =
{
 "1)Associate",
 "2)Dissociate",


};

uint8_t menu_marker = 0;
uint8_t entr_marker = 0;

char network_info[20];
uint16_t SollMenue = 0;
uint16_t Menu_index = 0;
 Task_Struct displayTask;        /* not static so you can see in ROV */
 Task_Params displayTaskParam;

 int gmt = 5;

 uint8_t displayTaskStack[controlTaskStackSize];

const uint16_t battery_full_[30000] = {
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0xffff,
                                   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
                                   0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
                                   0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
 };


 UG_BMP battery_full = {
   .p=battery_full_,
   .width=32,
   .height=32,
   .bpp=BMP_BPP_16,
 };


 char display_buffer[250];


 typedef struct MenueStruct {
     uint16_t MenueNr;           // this menu no
     void (*Function)(void); // pointer to function
     uint16_t Enter[255];            // Menu number with enter button
     uint16_t ESC;           // Menu number with ESC buton
     uint16_t DN;            // Menu number for DN button
     uint16_t UP;            // Menu number for UP button
     uint16_t LFT;           // Menu number for LFT button
     uint16_t RGHT;          // Menu number for RGHT button
 } MENUETYP;


 /*Static function declaration*/

 static void top_display();
 static void settings_display();
 static void noti_display();
 static void selection_menu();
 static void main_menu();


 static void top_display()
 {
     char buf[40];
     if(control_Task_dev_info.dev_shortAddr == 0xFFFF)
     {
         sprintf(buf,"ID: NULL");
     }
     else
     {
         sprintf(buf,"ID: %d",control_Task_dev_info.dev_shortAddr);
     }
     LCD_PutStr(0, 10, buf, FONT_16X26, C_BLACK, C_WHITE);
     UG_DrawBMP(200, 10, &battery_full);


    // UG_DrawBMP(100, 50, &fry);
 }

 static void settings_display()
 {

     uint8_t total_selection = 2;
     int8_t selection = 0;
     do
      {
          Button_.BT_code = cNONE_;
          do {

              ST7789_clearbuffer();
               UG_FillScreen(C_WHITE);
               top_display();

               for (int i = 0; i < 2; i++)
               {
                 LCD_PutStr(0, 50 + ((i)*30),(char *) setting_menu_str[i], FONT_16X26,selection == i ? C_RED : C_BLACK, C_WHITE);
               }
               UG_Update();

               Mysem_waitTimed(&display_handle,CLOCK_MS(1000));

          }while(Button_.BT_code == cNONE_);

          switch(Button_.BT_code)
          {

          case cUP:
          {

                  selection = selection  - 1;
                  if(selection < 0)
                  {
                      selection = total_selection-1;
                  }

                  break;
          }

          case cDWN:
          {
              selection = selection  + 1;
              selection = selection%total_selection;

              break;
          }
          case cENTR:
          {

              if(selection)
              {
                  Jdllc_sendDisassociationRequest();
              }
              else
              {
                  // Tell the sensor to start
                    Util_setEvent(&Sensor_events, SENSOR_START_EVT);
              }


              break;
          }
          default:
                  break;

          }


      } while(!(Button_.BT_code == cEXIT));



 }


 static void noti_display()
 {
     uint8_t total_selection = 9;
     int8_t prev_selection = 0;
     int8_t selection = 0;
     int16_t index_adder = 0;
//     /int16_t selected_index = 0;

     do
     {
         Button_.BT_code = cNONE_;
         do {
             uint16_t idx = 0;
             ST7789_clearbuffer();
             UG_FillScreen(C_WHITE);
             top_display();



             for (int i = 0 + index_adder; i < total_selection + index_adder; i++)
              {
                if(i < total_noti)
                {

                  if(recved_notifications[i].structValid == 0xBEEF)
                 {
                     sprintf(display_buffer,"%d)Table:%d Noti:%s      ",idx + 1 + index_adder,recved_notifications[i].Ding_ReferenceNumber,noti_code[recved_notifications[i].Noti_Code]);
                     LCD_PutStr(0, 50 + ((idx)*18), display_buffer, FONT_10X16,selection == idx ? C_RED :  C_BLACK,  C_WHITE);
                     idx++;
                 }

                }
              }


             UG_Update();
             //Task_sleep(CLOCK_MS(2000));

             sem_wait(&display_handle);

         }while(Button_.BT_code == cNONE_);

         switch(Button_.BT_code)
         {

         case cENTR:
         {
             uint8_t break_or_not = 1;


             if(recved_notifications[selection + index_adder].structValid == 0xBEEF)
             {

                 recved_notifications[selection + index_adder].structValid = 0xFFFF; //we invalid the current val as it is read
                 //Check if next is even available or not then we set the noti_count according to that
                 //if next is not available and we go in this struct that can cause the issue
                if(recved_notifications[(selection+1) + index_adder].structValid == 0xBEEF)
                {
                 for(int i = (selection+1) + index_adder ; i < total_noti ; i++ )
                 {
                     if(recved_notifications[i].structValid == 0xBEEF)
                     {
                         memcpy(&recved_notifications[i - 1],&recved_notifications[i],sizeof(control_task_Recvnotification_info));
                         recved_notifications[i].structValid = 0xFFFF;
                     }
                     else
                     {
                         noti_count = i;
                         break;
                     }

                 }
                }
                else
                {
                    noti_count = selection + index_adder;
                }

                 break_or_not = 0;


             }
             if(break_or_not)
             {
                 break;
             }

         }

         case cUP:
         {

                 selection = selection  - 1;
                 if(selection < 0 )
                 {


                     if(index_adder <= 0)
                     {
                         selection = 0;
                         index_adder = 0;
                     }
                     else
                     {
                         if(recved_notifications[selection + index_adder].structValid != 0xBEEF)
                           {
                               selection = selection  + 1;
                           }
                          else
                          {

                              if(selection <= 0)
                             {

                                    index_adder = index_adder - 9;
                                    selection = 8;

                                    if(index_adder <= 0) //incase for safety reasons
                                    {
                                        index_adder = 0;
                                    }
                             }

                          }
                     }
                 }



                 break;
         }

         case cDWN:
         {

             selection = selection  + 1;
            // selection = selection%total_selection;
             if(recved_notifications[selection + index_adder].structValid != 0xBEEF)
             {
                 selection = selection  - 1;
             }
             else
             {

               if(selection >= total_selection)
               {
                 selection = 0;
                 index_adder = index_adder + 9;
               }

             }


             break;
         }
         default:
                 break;

         }


   } while(!(Button_.BT_code == cEXIT));

 }

 static void selection_menu()
 {
     uint8_t total_selection = 2;
     int8_t selection = 0;
     entr_marker = 0;
     menu_marker = 1;
     do
     {
         Button_.BT_code = cNONE_;
         do {
             ST7789_clearbuffer();
              UG_FillScreen(C_WHITE);
              top_display();

              for (int i = 0; i < 2; i++)
              {
                LCD_PutStr(0, 50 + ((i)*30),(char *) selection_menu_str[i], FONT_16X26,selection == i ? C_RED : C_BLACK, C_WHITE);

              }
              UG_Update();

              sem_wait(&display_handle);

     }while(Button_.BT_code == cNONE_);

         switch(Button_.BT_code)
         {

         case cUP:
         {

                 selection = selection  - 1;
                 if(selection < 0)
                 {
                     selection = total_selection-1;
                 }

                 break;
         }

         case cDWN:
         {
             selection = selection  + 1;
             selection = selection%total_selection;

             break;
         }
         default:
                 break;

         }


         entr_marker = selection;



  }while(!(Button_.BT_code == cENTR || Button_.BT_code == cEXIT));


 }

static void main_menu()
{


    do
    {
        Button_.BT_code = cNONE_;
        do {

          // UG_FontSetTransparency(1);
            uint32_t time =UTC_getClock();
            UTCTimeStruct tm;
            EPOCH_convertTime(&tm,time,gmt);
            ST7789_clearbuffer();
            UG_FillScreen(C_WHITE);
            top_display();



            sprintf(display_buffer,"%02d:%02d:%02d    ",tm.hour, tm.minutes, tm.seconds );
            LCD_PutStr(62, 50, display_buffer, FONT_16X26, C_BLACK, C_WHITE);
            sprintf(display_buffer,"%02d/%02d/%02d    ", tm.day, tm.month, tm.year);
            LCD_PutStr(50, 80, display_buffer, FONT_16X26, C_BLACK, C_WHITE);

            //network_info
            LCD_PutStr(55, 130, "*Network*", FONT_16X26, C_BLACK, C_WHITE);
            LCD_PutStr(55, 165, network_info, FONT_16X26, C_BLACK, C_WHITE);
            UG_Update();



            Mysem_waitTimed(&display_handle,CLOCK_MS(800));

        }while(Button_.BT_code == cNONE_);



    }while(!(Button_.BT_code == cENTR));


}



 // Menu tables
 const MENUETYP mkaMenue[] =
         {
          {main_menu_,main_menu,{selection_},main_menu_,0,0,0,0},
          {selection_,selection_menu,{notif_center_,settings_},main_menu_,0,0,0,0},
          {notif_center_,noti_display,{main_menu_},main_menu_,0,0,0,0},
          {settings_,settings_display,{main_menu_},main_menu_,0,0,0,0},

         };

 static void process_menu(void) {
     uint16_t iIdx;
     uint16_t iNeuMenue;

         if (SollMenue == 0)     // Restart or change of day
                 {
             SollMenue = 1;      // first menu
         }
         for (iIdx = 0; iIdx < sizeof(mkaMenue) / sizeof(mkaMenue[0]); iIdx++) {
             if (SollMenue == mkaMenue[iIdx].MenueNr)// check if this menu is found ?
                     {
                 break;
             }
         }
         if (iIdx < sizeof(mkaMenue) / 16)       // found ?
                 {
             Menu_index = iIdx;
             mkaMenue[Menu_index].Function();    // Execute menu item

             switch (Button_.BT_code)                    // which branch?
             {
             case cENTR: {
                 if(!menu_marker)
                   {
                     iNeuMenue = mkaMenue[Menu_index].Enter[0];
                   }
                 else
                 {
                     iNeuMenue = mkaMenue[Menu_index].Enter[entr_marker];
                     menu_marker = 0;
                 }
                 break;
             }

             case cEXIT: {
                     iNeuMenue = mkaMenue[Menu_index].ESC;
                 break;
             }
             case cDWN: {
                 iNeuMenue = mkaMenue[Menu_index].DN;
                 break;
             }
             case cUP: {
                 iNeuMenue = mkaMenue[Menu_index].UP;
                 break;
             }

//             case cLFT_BT: {
//                 iNeuMenue = mkaMenue[Menu_index].LFT;
//                 break;
//             }
//
//             case cRGHT_BT: {
//                 iNeuMenue = mkaMenue[Menu_index].RGHT;
//                 break;
//             }
//
//             case cSub_menu: {
//                 iNeuMenue = SollMenue;
//
//                 break;
//             }

             default:
                 iNeuMenue = 0;
                 break;
             }
             if (iNeuMenue != 0)         // Menu change wanted?
                     {
                 SollMenue = iNeuMenue;  // is to be carried out
             }

         } else {
             SollMenue = 1; //select first menu and retry
         }

 }


void display_task_(uintptr_t arg1, uintptr_t arg2)
{
    ST7789_Init(CONFIG_SPI_LCD);


   // lv_init();
   // Display_init_lvgl(0,CONFIG_SPI_LCD);
   // ui_init();
    while(1)
    {
        process_menu();

       // lv_timer_handler();
       // Task_sleep(CLOCK_MS(10));
    }
}


void display_taskInit()
{

    sem_init(&display_handle, 0, 0);

    Task_Params_init(&displayTaskParam);
    displayTaskParam.stack = displayTaskStack;
    displayTaskParam.stackSize = displayTaskStackSize;
    displayTaskParam.priority = displayTaskPriority;
    Task_construct(&displayTask, display_task_, &displayTaskParam, NULL);

}
