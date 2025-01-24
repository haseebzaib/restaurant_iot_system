/*
 * btn.c
 *
 *  Created on: Jul 30, 2024
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
#include <ti/drivers/dpl/ClockP.h>
#include <ti/drivers/Timer.h>
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
#include <ti/sysbios/knl/Semaphore.h>

#define btn_timeout 5000


 Button_t Button_;
static Button_Handle gBTN_UP;
static Button_Handle gBTN_DWN;
static Button_Handle gBTN_ENTR;
static Button_Handle gBTN_EXIT;


static uint32_t button_timeoutCount = 0;
static uint32_t button_timeout = 5000;

static uint32_t button_timeout_enable = 0;



#define read_BtnUP  (!GPIO_read(((Button_HWAttrs*)gBTN_UP->hwAttrs)->gpioIndex))
#define read_BtnDWN (!GPIO_read(((Button_HWAttrs*)gBTN_DWN->hwAttrs)->gpioIndex))
#define read_BtnENTR (!GPIO_read(((Button_HWAttrs*)gBTN_ENTR->hwAttrs)->gpioIndex))
#define read_BtnEXIT  (!GPIO_read(((Button_HWAttrs*)gBTN_EXIT->hwAttrs)->gpioIndex))

static void setTimer(uint32_t* timer)
{
    *timer = ClockP_getSystemTicks();
}
static uint8_t checkTimer(uint32_t* timer, uint32_t msTime)
{
    uint8_t retrn = 0;
    uint32_t compare_timer = ClockP_getSystemTicks();
    retrn = ((compare_timer - *timer) > msTime)  ? 1 : 0;
    return retrn;
}

static void Button_Timeout()
{

    for(int i =0; i< 4;i++)
    {
        if(Button_.buttonTimeoutEnable[i])
        {
            Button_.buttonTimeoutCount[i]++;

            if( Button_.buttonTimeoutCount[i] > Button_.buttonTimeout)
            {
                Button_.buttonTimeoutEnable[i] = 0;
            }

        }

    }

}


static void Store_buttonCode(btn_codes iCode)
{



    Button_.BT_code = iCode;
    Button_.buttonTimeoutCount[iCode] = 0;
    Button_.buttonTimeoutEnable[iCode] = 1;
    sem_post(&display_handle);



}

void btn_process()
{

//    Button_Timeout();

    if(Button_.buttonFlag)
    {

        if(read_BtnUP)
        {
            setTimer(&Button_.buttonTimer); //to set debounce
            Button_.buttonFlag =0;
            Button_.Sel_BT =cUP;
        }
        else if(read_BtnDWN)
        {
            setTimer(&Button_.buttonTimer); //to set debounce
            Button_.buttonFlag =0;
            Button_.Sel_BT =cDWN;
        }
        else if(read_BtnENTR)
        {
            setTimer(&Button_.buttonTimer); //to set debounce
            Button_.buttonFlag =0;
            Button_.Sel_BT =cENTR;
        }
        else if(read_BtnEXIT)
        {
            setTimer(&Button_.buttonTimer); //to set debounce
            Button_.buttonFlag =0;
            Button_.Sel_BT =cEXIT;
        }

    }
    else if((!Button_.buttonFlag) && (checkTimer(&Button_.buttonTimer, CLOCK_MS(150))))
    {
        switch (Button_.Sel_BT) {

        case cUP:
        {
            if (!read_BtnUP) {
                Store_buttonCode(Button_.Sel_BT);
              }
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE_;

            break;
        }
        case cDWN:
        {
            if (!read_BtnDWN) {
                Store_buttonCode(Button_.Sel_BT);
              }
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE_;
            break;
        }
        case cENTR:
        {
            if (!read_BtnENTR) {
                Store_buttonCode(Button_.Sel_BT);
              }
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE_;
            break;
        }
        case cEXIT:
        {
            if (!read_BtnEXIT) {
                Store_buttonCode(Button_.Sel_BT);
              }
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE_;
            break;
        }
        default:
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE_;
            break;


        }

    }

}
void btn_init()
{
    Button_init();
    Button_Params bparams;
    Button_Params_init(&bparams);
    gBTN_UP = Button_open(BTN_UP, &bparams);
    gBTN_DWN = Button_open(BTN_DWN, &bparams);
    gBTN_ENTR = Button_open(BTN_ENTR, &bparams);
    gBTN_EXIT = Button_open(BTN_EXIT, &bparams);

    Button_.BT_code = cNONE_;
    Button_.buttonFlag = 1;
    Button_.buttonTimer = 0;
    Button_.buttonTimeout = btn_timeout;

    for(int i =0; i< 4;i++)
    {
        Button_.buttonTimeoutCount[i] = 0;
        Button_.buttonTimeoutEnable[i] = 0;

    }

}
