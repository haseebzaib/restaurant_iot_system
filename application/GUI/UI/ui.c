/*
 * ui.c
 *
 *  Created on: Jan 25, 2025
 *      Author: hzaib
 */


#include "ti_drivers_config.h"
#include <ti/sysbios/knl/Task.h>
#include "ui.h"
#include "Defines.h"
#include "st7789.h"
#include <ti/drivers/UART2.h>

uint8_t count = 0;


void ui_lvglTickHandler()
{
    lv_tick_inc(1);
}

 void ui_loop()
 {
     lv_timer_handler();
     Task_sleep(CLOCK_MS(1000));
     //ui_Main_new_message(count++,"2.12min");
     //ui_Main_scroll_list();

 }



void ui_init()
{
    lv_init();
    Display_init_lvgl(0,CONFIG_SPI_LCD);
    ui_Main_screen_init();
    lv_disp_load_scr(ui_Main);

}
