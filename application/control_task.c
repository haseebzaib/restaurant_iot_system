/*
 * control_task.c
 *
 *  Created on: Jul 27, 2024
 *      Author: hzaib
 */

/* RTOS header files */

#include <ti/sysbios/BIOS.h>

#include <pthread.h>

#include <ioc.h>

#include "sys_ctrl.h"
#include "jdllc.h"
#include "ti_drivers_config.h"
#include "mac_util.h"
#include "ssf.h"
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

Task_Struct controlTask;
Task_Params controlTaskParam;
uint8_t controlTaskStack[controlTaskStackSize];
control_task_devices_info control_Task_dev_info;

Mailbox_Params control_task_InfoToHub_params;
Mailbox_Handle control_task_InfoToHub_handle = NULL;

Mailbox_Params control_task_ledConfirm_params;
Mailbox_Handle control_task_ledConfirm_handle = NULL;

Mailbox_Params control_task_NotiInfo_params;
Mailbox_Handle control_task_NotiInfo_handle= NULL;

uint16_t personal_addr = 0xFFFF;

control_task_CallButtonNotification_Info sendNoti_To_Hub;

typedef union
{
    uint8_t B[4];
    uint32_t L;
} bit32_4_8bits;

bit32_4_8bits macAddrLsb;
bit32_4_8bits macAddrMsb;

typedef union
{

    uint8_t B[2];
    uint16_t L;
} bit16_2_8bits;

bit16_2_8bits conv;

uint8_t devInfoConfirmationFlag = 0;
uint32_t devInfoConfirmationTimer = 0;
uint8_t devInfoConfirmationMail = 0;
uint8_t disconnected_ledShow =1;
uint8_t retry_count_devInfo = 0;


/*static variables*/
static control_task_InfoToHub_mail InfoToHub_mail;
static control_task_led_confirmation LedConfirm_mail;
static control_task_CallButtonNotification_Info NotiInfo_mail;
static uint16_t Num_MsgInfoToHubMail = 0;
static uint16_t Num_MsgLedConfirmMail = 0;
static uint16_t Num_MsgNotiInfoMail = 0;

/*Function prototypes*/
static void show_disconnectionColor();
static void check_NotiInfoMail();
static void check_devInfoMail();
static void check_ledConfirmMail();
static void set_normalColor();
static void controlTask_(uintptr_t arg1, uintptr_t arg2);


static void show_disconnectionColor()
{
    NeoPixelEffect_strobe(255, 0, 0, 3, 300, 0, NUMBER_OF_LEDS);
}

static void check_NotiInfoMail()
{
    Num_MsgNotiInfoMail = Mailbox_getNumPendingMsgs(
            control_task_NotiInfo_handle);

    if (Num_MsgNotiInfoMail > 0)
    {

        bool success = Mailbox_pend(control_task_NotiInfo_handle,
                                    &NotiInfo_mail, BIOS_WAIT_FOREVER);
        if (success)
        {

                uint8_t cmdbyte[12];

                /*cmdId*/
                cmdbyte[0] = Smsgs_cmdIds_SensorNotiInfo;
                /*dev_short Addr*/
                conv.L = NotiInfo_mail.dev_shortAddr;
                cmdbyte[1] = conv.B[0]; //lsb
                cmdbyte[2] = conv.B[1]; //msb
                /*dev_signature*/
                cmdbyte[3] = macAddrLsb.B[0];
                cmdbyte[4] = macAddrLsb.B[1];
                cmdbyte[5] = macAddrLsb.B[2];
                cmdbyte[6] = macAddrLsb.B[3];
                cmdbyte[7] = macAddrMsb.B[0];
                cmdbyte[8] = macAddrMsb.B[1];
                cmdbyte[9] = macAddrMsb.B[2];
                cmdbyte[10] = macAddrMsb.B[3];
                /*Notification Code*/
                cmdbyte[11] = NotiInfo_mail.Noti_Code;
                //Task_sleep(CLOCK_MS(300));
                Sensor_sendMsg(Smsgs_cmdIds_SensorNotiInfo,
                               &collectorAddr_app, true, 12, cmdbyte);

        }

    }



}


static void check_devInfoMail()
{
    Num_MsgInfoToHubMail = Mailbox_getNumPendingMsgs(
            control_task_InfoToHub_handle);

    if (Num_MsgInfoToHubMail > 0)
    {

        bool success = Mailbox_pend(control_task_InfoToHub_handle,
                                    &InfoToHub_mail, BIOS_WAIT_FOREVER);
        if (success)
        {
            // printf("Short Address: %d",joinedDev_mail.shortAddr);

            if (InfoToHub_mail.sendInfo)
            {
                uint8_t cmdbyte[16];

                /*cmdId*/
                cmdbyte[0] = Smsgs_cmdIds_SensorDeviceInfo;
                /*dev_short Addr*/
                conv.L = control_Task_dev_info.dev_shortAddr;
                cmdbyte[1] = conv.B[0]; //lsb
                cmdbyte[2] = conv.B[1]; //msb
                /*dev_signature*/
                cmdbyte[3] = macAddrLsb.B[0];
                cmdbyte[4] = macAddrLsb.B[1];
                cmdbyte[5] = macAddrLsb.B[2];
                cmdbyte[6] = macAddrLsb.B[3];
                cmdbyte[7] = macAddrMsb.B[0];
                cmdbyte[8] = macAddrMsb.B[1];
                cmdbyte[9] = macAddrMsb.B[2];
                cmdbyte[10] = macAddrMsb.B[3];
                /*type of sensor*/
                cmdbyte[11] = control_Task_dev_info.isWatch; //is watch
                cmdbyte[12] = control_Task_dev_info.isDing;
                cmdbyte[13] = control_Task_dev_info.isManager;
                /*Verification*/
                cmdbyte[14] = 0xEF;
                cmdbyte[15] = 0xBE;
                Task_sleep(CLOCK_MS(500));
                Sensor_sendMsg(Smsgs_cmdIds_SensorDeviceInfo,
                               &collectorAddr_app, true, 16, cmdbyte);

                devInfoConfirmationTimer = 0;
                devInfoConfirmationFlag = 1; //we start timing now

            }

        }

    }

    if (devInfoConfirmationMail == 1)
    {
        retry_count_devInfo++;
        devInfoConfirmationMail = 0;
        control_task_mail_post_InfoToHub(1);
    }

    /*Do 10 retries only*/
    if(retry_count_devInfo > 10)
    {
        devInfoConfirmationFlag = 0;
        devInfoConfirmationTimer = 0;
        devInfoConfirmationMail = 0;
        retry_count_devInfo = 0;


        Jdllc_sendDisassociationRequest();

        /* Clear the event */
        Util_clearEvent(&Sensor_events, SENSOR_DISASSOC_EVT);

        /* Tell the sensor to start */
       Util_setEvent(&Sensor_events, SENSOR_START_EVT);
       /* Wake up the application thread when it waits for clock event */
       Ssf_PostAppSem();
       Util_setEvent(&Jdllc_events, JDLLC_ASSOCIATE_REQ_EVT);


    }

}
static void check_ledConfirmMail()
{
    Num_MsgLedConfirmMail = Mailbox_getNumPendingMsgs(
            control_task_ledConfirm_handle);

    if (Num_MsgLedConfirmMail > 0)
    {

        bool success = Mailbox_pend(control_task_ledConfirm_handle,
                                    &LedConfirm_mail, BIOS_WAIT_FOREVER);
        if (success)
        {

            switch (LedConfirm_mail.ledInfo)
            {
            case led_devInfo_confirmation:
            {
                 NeoPixelEffect_strobe(0, 0, 255, 3, 300, 0, NUMBER_OF_LEDS);
                break;
            }
            case led_noti_confirmation:
            {
                NeoPixelEffect_strobe(0, 255, 0, 2, 300, LedConfirm_mail.btn_code*4 , 4);
                break;
            }

            default:
                break;

            }

        }

    }

}

static void set_normalColor()
{
    NeoPixel_clear();

   for(int i =0; i< NUMBER_OF_LEDS ; i++)
    {
       NeoPixel_setPixelColor(i, 255, 165, 0);

    }
    NeoPixel_show();

}
/*
 * Task to control features
 */
static void controlTask_(uintptr_t arg1, uintptr_t arg2)
{

    btn_init();
    timer_init();

    disconnected_ledShow = 1;

    /*compute unique ID here for MCU*/
    macAddrLsb.L = HWREG(FCFG1_BASE + FCFG1_O_MAC_15_4_0);
    macAddrMsb.L = HWREG(FCFG1_BASE + FCFG1_O_MAC_15_4_1);

    control_Task_dev_info.isWatch = 0; //is watch
    control_Task_dev_info.isDing = 1;
    control_Task_dev_info.isManager = 0;
    control_Task_dev_info.structValid = 0xBEEF;
//control_Task_dev_info.dev_signature = macAddress;

    NeoPixel_init();

    NeoPixel_setBrightness(5);
    set_normalColor();

    while (1)
    {

        if(disconnected_ledShow)
        {
            show_disconnectionColor();
        }

        check_devInfoMail();
        check_NotiInfoMail();
        check_ledConfirmMail();
        set_normalColor();


        Task_sleep(CLOCK_MS(100));

    }

}

/*Global Functions*/

status control_Task_Noti_Info_mail(button_codes btn_code)
{


    control_task_CallButtonNotification_Info mail;

    status status_ = OK;

    mail.Noti_Code = btn_code;
    mail.dev_shortAddr = control_Task_dev_info.dev_shortAddr;
    mail.dev_signature =  ((uint64_t)(macAddrMsb.L) << 32) | (uint64_t)(macAddrLsb.L);


    if (control_task_NotiInfo_handle)
    {
        if (!Mailbox_post(control_task_NotiInfo_handle, &mail, CLOCK_MS(100)))
        {
            status_ = ERROR;
        }
    }
    else
    {
        status_ = ERROR;
    }

    return status_;
}

status control_Task_led_confirmation_mail(led_confirmation ledinfo,button_codes btn_code)
{
    control_task_led_confirmation mail;

    status status_ = OK;

    mail.ledInfo = ledinfo;

    if(ledinfo != led_devInfo_confirmation)
    {
      mail.btn_code = btn_code;
    }

    if (control_task_ledConfirm_handle)
    {
        if (!Mailbox_post(control_task_ledConfirm_handle, &mail, CLOCK_MS(100)))
        {
            status_ = ERROR;
        }
    }
    else
    {
        status_ = ERROR;
    }

    return status_;
}

/*
 *Post mail to the control task from outside the scope
 */
status control_task_mail_post_InfoToHub(uint8_t sendInfo)
{
    control_task_InfoToHub_mail mail;

    status status_ = OK;

    mail.sendInfo = sendInfo;

    if (control_task_InfoToHub_handle)
    {
        if (!Mailbox_post(control_task_InfoToHub_handle, &mail, CLOCK_MS(100)))
        {
            status_ = ERROR;
        }
    }
    else
    {
        status_ = ERROR;
    }

    return status_;
}

/*
 * Initialization function
 */
void control_taskInit()
{

    Mailbox_Params_init(&control_task_InfoToHub_params);
    control_task_InfoToHub_handle = Mailbox_create(
            sizeof(control_task_InfoToHub_mail), 2,
            &control_task_InfoToHub_params, NULL);

    Mailbox_Params_init(&control_task_ledConfirm_params);
    control_task_ledConfirm_handle = Mailbox_create(
            sizeof(control_task_led_confirmation), 2,
            &control_task_ledConfirm_params, NULL);


    Mailbox_Params_init(&control_task_NotiInfo_params);
    control_task_NotiInfo_handle = Mailbox_create(
            sizeof(control_task_CallButtonNotification_Info), 10,
            &control_task_NotiInfo_params, NULL);

    Task_Params_init(&controlTaskParam);
    controlTaskParam.stack = controlTaskStack;
    controlTaskParam.stackSize = controlTaskStackSize;
    controlTaskParam.priority = controlTaskPriority;
    Task_construct(&controlTask, controlTask_, &controlTaskParam, NULL);

}

