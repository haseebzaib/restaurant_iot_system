/*
 * control_task.h
 *
 *  Created on: Jul 27, 2024
 *      Author: hzaib
 */

#ifndef APPLICATION_CONTROL_TASK_H_
#define APPLICATION_CONTROL_TASK_H_

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include "ti_154stack_config.h"
#include "Defines.h"
#include "api_mac.h"
extern uint16_t personal_addr ;


typedef struct _control_task_InfoToHub_mail
{
    uint8_t sendInfo;  //send information related to sensor to hub
}control_task_InfoToHub_mail;


typedef struct _control_task_led_confirmation
{
    led_confirmation ledInfo;
    button_codes btn_code;
}control_task_led_confirmation;




TYPEDEF_STRUCT_PACKED {
   uint16_t dev_shortAddr;  /*device short address to send messages on*/
   uint64_t dev_signature; /*unique signature of CC1314*/
   uint8_t isWatch;   /*true false*/
   uint8_t isDing;    /*true false*/
   uint8_t isManager; /*true false*/
   uint16_t structValid;
}control_task_devices_info;
extern control_task_devices_info control_Task_dev_info;


TYPEDEF_STRUCT_PACKED {
    /*These two parameters are important as they are for identification of device*/
    uint16_t dev_shortAddr;  /*device short address to send messages on*/
    uint64_t dev_signature;  /*unique signature of CC1314*/

    button_codes Noti_Code; /*This will tell hub what the noti is for*/



}control_task_CallButtonNotification_Info;




extern status control_Task_Noti_Info_mail(button_codes btn_code);
extern status control_Task_led_confirmation_mail(led_confirmation ledinfo,button_codes btn_code);
extern status control_task_mail_post_InfoToHub(uint8_t sendInfo);
extern void control_taskInit();

#endif /* APPLICATION_CONTROL_TASK_H_ */
