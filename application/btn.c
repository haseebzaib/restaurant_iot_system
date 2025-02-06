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
#include "NeoPixel.h"
#include "NeoPixelEffect.h"

#define btn_timeout 5000


 Button_t Button_;
static Button_Handle gBTN_CALL;
static Button_Handle gBTN_WATER;
static Button_Handle gBTN_ORDER;
static Button_Handle gBTN_BILL;


static uint32_t button_timeoutCount = 0;
static uint32_t button_timeout = 5000;

static uint32_t button_timeout_enable = 0;



#define read_BtnCall  (!GPIO_read(((Button_HWAttrs*)gBTN_CALL->hwAttrs)->gpioIndex))
#define read_BtnWater (!GPIO_read(((Button_HWAttrs*)gBTN_WATER->hwAttrs)->gpioIndex))
#define read_BtnOrder (!GPIO_read(((Button_HWAttrs*)gBTN_ORDER->hwAttrs)->gpioIndex))
#define read_BtnBill  (!GPIO_read(((Button_HWAttrs*)gBTN_BILL->hwAttrs)->gpioIndex))

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


static void Store_buttonCode(button_codes iCode)
{

if(!Button_.buttonTimeoutEnable[iCode] && iCode != cNONE)
{

    Button_.BT_code = iCode;
    //control_Task_led_confirmation_mail(led_noti_confirmation,Button_.BT_code);
    control_Task_Noti_Info_mail(Button_.BT_code);
    Button_.buttonTimeoutCount[iCode] = 0;
    Button_.buttonTimeoutEnable[iCode] = 1;
}



}

void btn_process()
{

    Button_Timeout();

    if(Button_.buttonFlag)
    {

        if(read_BtnCall)
        {
            setTimer(&Button_.buttonTimer); //to set debounce
            Button_.buttonFlag =0;
            Button_.Sel_BT =cCALL;
        }
        else if(read_BtnWater)
        {
            setTimer(&Button_.buttonTimer); //to set debounce
            Button_.buttonFlag =0;
            Button_.Sel_BT =cWATER;
        }
        else if(read_BtnOrder)
        {
            setTimer(&Button_.buttonTimer); //to set debounce
            Button_.buttonFlag =0;
            Button_.Sel_BT =cORDER;
        }
        else if(read_BtnBill)
        {
            setTimer(&Button_.buttonTimer); //to set debounce
            Button_.buttonFlag =0;
            Button_.Sel_BT =cBILL;
        }

    }
    else if((!Button_.buttonFlag) && (checkTimer(&Button_.buttonTimer, CLOCK_MS(150))))
    {
        switch (Button_.Sel_BT) {

        case cCALL:
        {
            if (!read_BtnCall) {
                Store_buttonCode(Button_.Sel_BT);
              }
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE;

            break;
        }
        case cWATER:
        {
            if (!read_BtnWater) {
                Store_buttonCode(Button_.Sel_BT);
              }
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE;
            break;
        }
        case cORDER:
        {
            if (!read_BtnOrder) {
                Store_buttonCode(Button_.Sel_BT);
              }
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE;
            break;
        }
        case cBILL:
        {
            if (!read_BtnBill) {
                Store_buttonCode(Button_.Sel_BT);
              }
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE;
            break;
        }
        default:
            Button_.buttonFlag =1;
            Button_.Sel_BT = cNONE;
            break;


        }

    }

}
void btn_init()
{
    Button_init();
    Button_Params bparams;
    Button_Params_init(&bparams);
    gBTN_CALL = Button_open(BTN_CALL, &bparams);
    gBTN_WATER = Button_open(BTN_WATER, &bparams);
    gBTN_ORDER = Button_open(BTN_ORDER, &bparams);
    gBTN_BILL = Button_open(BTN_BILL, &bparams);

    Button_.BT_code = cNONE;
    Button_.buttonFlag = 1;
    Button_.buttonTimer = 0;
    Button_.buttonTimeout = btn_timeout;

    for(int i =0; i< 4;i++)
    {
        Button_.buttonTimeoutCount[i] = 0;
        Button_.buttonTimeoutEnable[i] = 0;

    }

}
