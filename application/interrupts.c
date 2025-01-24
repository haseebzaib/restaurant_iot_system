/*
 * interrupts.c
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





  void timer_callback(Timer_Handle handle, int_fast16_t status)
  {

      if(devInfoConfirmationFlag == 1)
       {
          devInfoConfirmationTimer++;

          if(devInfoConfirmationTimer > 6000)
          {
              devInfoConfirmationTimer = 0;
              devInfoConfirmationMail = 1;

          }

       }

      btn_process();

  }



  void timer_init()
  {
      Timer_Handle timer0;
       Timer_Params params;

       Timer_Params_init(&params);
       params.period        = 1*1000;
       params.periodUnits   = Timer_PERIOD_US;
       params.timerMode     = Timer_CONTINUOUS_CALLBACK;
       params.timerCallback = timer_callback;

       timer0 = Timer_open(CONFIG_TIMER_0, &params);

       if (timer0 == NULL)
       {
           /* Failed to initialized timer */
           while (1) {}
       }

       if (Timer_start(timer0) == Timer_STATUS_ERROR)
       {
           /* Failed to start timer */
           while (1) {}
       }
  }
