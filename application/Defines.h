/*
 * Defines.h
 *
 *  Created on: Jul 24, 2024
 *      Author: hzaib
 */

#ifndef APPLICATION_DEFINES_H_
#define APPLICATION_DEFINES_H_


#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/drivers/Timer.h>
#include "api_mac.h"
#include <semaphore.h>
#define TYPEDEF_STRUCT_PACKED        typedef struct __attribute__((__packed__))
#define CLOCK_US(us) ((us * 1)      / Clock_tickPeriod)
#define CLOCK_MS(ms) ((ms * 1000)   / Clock_tickPeriod)
#define CLOCK_S(s)   ((s * 1000000) / Clock_tickPeriod)


#define total_noti 100
 extern uint16_t noti_count;

extern int gmt;


extern  uint32_t devInfoConfirmationTimer;
extern  uint8_t devInfoConfirmationFlag;
extern  uint8_t devInfoConfirmationMail;

typedef enum{

    OK = 0,
    ERROR = 1,
}status;

/*Collector Task Parameters*/

extern Task_Struct sensorTask;        /* not static so you can see in ROV */
extern Task_Params sensorTaskParam;
#define sensorTaskStackSize  (2*1024)
extern uint8_t sensorTaskStack[sensorTaskStackSize];
#define sensorTaskPriority  1

/*Control Task*/
extern Task_Struct controlTask;        /* not static so you can see in ROV */
extern Task_Params controlTaskParam;
#define controlTaskStackSize  (5*1024)
extern uint8_t controlTaskStack[controlTaskStackSize];
#define controlTaskPriority  3

extern Mailbox_Params control_task_InfoToHub_params;
extern Mailbox_Handle control_task_InfoToHub_handle;

extern Mailbox_Params control_task_NotiInfo_params;
extern Mailbox_Handle control_task_NotiInfo_handle;

/*Display Task*/
extern Task_Struct displayTask;        /* not static so you can see in ROV */
extern Task_Params displayTaskParam;
#define displayTaskStackSize  (2*1024)
extern uint8_t displayTaskStack[controlTaskStackSize];
#define displayTaskPriority  4


extern ApiMac_sAddr_t collectorAddr_app ;


enum
{
    main_menu_ = 1,
    selection_ = 2,
    notif_center_ = 3,
    settings_= 4,

}menu_number;

typedef enum
{
    //c denotes as an identifier for that button code
    cCALL = 0,
    cWATER = 1,
    cORDER = 2,
    cBILL = 3,
    cNONE = 4,
}noti_codes;



extern sem_t display_handle;

extern char network_info[20];
extern void display_taskInit();


extern void timer_callback(Timer_Handle handle, int_fast16_t status);
extern void timer_init();


typedef enum
{
    //c denotes as an identifier for that button code
    cUP = 0,
    cDWN = 1,
    cENTR = 2,
    cEXIT = 3,
    cNONE_ = 4,
}btn_codes;


typedef struct {
    uint32_t buttonTimer; //to debounce the button
    uint8_t buttonFlag;//to know if button is pressed

    uint32_t buttonTimeoutCount[4];
    uint32_t buttonTimeout;
    uint8_t buttonTimeoutEnable[4];

    btn_codes Sel_BT; // selected button
    btn_codes BT_code;//code that transfers to main program

} Button_t;

extern Button_t Button_;

extern void btn_process();
extern void btn_init();


#endif /* APPLICATION_DEFINES_H_ */
