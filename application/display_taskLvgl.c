/*
 * display_taskLvgl.c
 *
 *  Created on: Oct 18, 2024
 *      Author: hzaib
 */

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


sem_t display_handle;
Task_Struct displayTask;        /* not static so you can see in ROV */
Task_Params displayTaskParam;
uint8_t displayTaskStack[controlTaskStackSize];
char network_info[20];
int gmt = 5;


void display_task_(uintptr_t arg1, uintptr_t arg2)
{



    lv_init();
    Display_init_lvgl(0,CONFIG_SPI_LCD);

    lv_obj_t *screen = lv_scr_act();
    // Create ID label
    lv_obj_t * id_label = lv_label_create(screen);
    lv_label_set_text(id_label, "ID: 12345");
    lv_obj_align(id_label, LV_ALIGN_TOP_LEFT, 10, 10);

    // Create battery bar
    lv_obj_t * battery_bar = lv_bar_create(screen);
    lv_bar_set_range(battery_bar, 0, 100);
    lv_bar_set_value(battery_bar, 80, LV_ANIM_OFF);
    lv_obj_set_size(battery_bar, 100, 10);
    lv_obj_align(battery_bar, LV_ALIGN_TOP_RIGHT, -10, 10);

    // Create time label
    lv_obj_t * time_label = lv_label_create(screen);
    lv_label_set_text(time_label, "12:00 PM - 01/01/2024");
    lv_obj_align(time_label, LV_ALIGN_BOTTOM_MID, 0, 0);


    while(1)
    {


       lv_timer_handler();
       Task_sleep(CLOCK_MS(10));
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



