/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  The macros defines herein are intended for use by applications which
 *  directly include this header. These macros should NOT be hard coded or
 *  copied into library source code.
 *
 *  Symbols declared as const are intended for use with libraries.
 *  Library source code must extern the correct symbol--which is resolved
 *  when the application is linked.
 *
 *  DO NOT EDIT - This file is generated for the LP_CC1314R10_RGZ
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_LP_CC1314R10_RGZ
#ifndef DeviceFamily_CC13X4
#define DeviceFamily_CC13X4
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== CCFG ========
 */


/*
 *  ======== AESCCM ========
 */

extern const uint_least8_t                  CONFIG_AESCCM_0_CONST;
#define CONFIG_AESCCM_0                     0
#define CONFIG_TI_DRIVERS_AESCCM_COUNT      1


/*
 *  ======== GPIO ========
 */
extern const uint_least8_t CONFIG_GPIO_RST_CONST;
#define CONFIG_GPIO_RST 24

extern const uint_least8_t CONFIG_GPIO_DC_CONST;
#define CONFIG_GPIO_DC 25

extern const uint_least8_t CONFIG_GPIO_CS_CONST;
#define CONFIG_GPIO_CS 26

extern const uint_least8_t CONFIG_GPIO_1_CONST;
#define CONFIG_GPIO_1 1

/* Owned by CONFIG_SPI_LCD as  */
extern const uint_least8_t CONFIG_GPIO_SPI_LCD_SCLK_CONST;
#define CONFIG_GPIO_SPI_LCD_SCLK 27

/* Owned by CONFIG_SPI_LCD as  */
extern const uint_least8_t CONFIG_GPIO_SPI_LCD_POCI_CONST;
#define CONFIG_GPIO_SPI_LCD_POCI 28

/* Owned by CONFIG_SPI_LCD as  */
extern const uint_least8_t CONFIG_GPIO_SPI_LCD_PICO_CONST;
#define CONFIG_GPIO_SPI_LCD_PICO 29

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_SCLK_CONST;
#define CONFIG_GPIO_SPI_0_SCLK 10

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_POCI_CONST;
#define CONFIG_GPIO_SPI_0_POCI 8

/* Owned by CONFIG_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_SPI_0_PICO_CONST;
#define CONFIG_GPIO_SPI_0_PICO 9

/* Owned by CONFIG_DISPLAY_UART as  */
extern const uint_least8_t CONFIG_GPIO_DISPLAY_UART_TX_CONST;
#define CONFIG_GPIO_DISPLAY_UART_TX 3

/* Owned by CONFIG_DISPLAY_UART as  */
extern const uint_least8_t CONFIG_GPIO_DISPLAY_UART_RX_CONST;
#define CONFIG_GPIO_DISPLAY_UART_RX 2

/* Owned by BTN_DWN as  */
extern const uint_least8_t CONFIG_GPIO_BTN_DWN_INPUT_CONST;
#define CONFIG_GPIO_BTN_DWN_INPUT 13

/* Owned by BTN_UP as  */
extern const uint_least8_t CONFIG_GPIO_BTN_UP_INPUT_CONST;
#define CONFIG_GPIO_BTN_UP_INPUT 14

/* Owned by BTN_ENTR as  */
extern const uint_least8_t CONFIG_GPIO_BTN_ENTR_INPUT_CONST;
#define CONFIG_GPIO_BTN_ENTR_INPUT 16

/* Owned by BTN_EXIT as  */
extern const uint_least8_t CONFIG_GPIO_BTN_EXIT_INPUT_CONST;
#define CONFIG_GPIO_BTN_EXIT_INPUT 17

/* Owned by CONFIG_LED_RED as  */
extern const uint_least8_t CONFIG_GPIO_RLED_CONST;
#define CONFIG_GPIO_RLED 6

/* Owned by CONFIG_LED_GREEN as  */
extern const uint_least8_t CONFIG_GPIO_GLED_CONST;
#define CONFIG_GPIO_GLED 7

/* Owned by CONFIG_NVS_SPI_0 as  */
extern const uint_least8_t CONFIG_GPIO_0_CONST;
#define CONFIG_GPIO_0 20

/* The range of pins available on this device */
extern const uint_least8_t GPIO_pinLowerBound;
extern const uint_least8_t GPIO_pinUpperBound;

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== NVS ========
 */

extern const uint_least8_t              CONFIG_NVSINTERNAL_CONST;
#define CONFIG_NVSINTERNAL              0
/*
 *  PICO: DIO9
 *  POCI: DIO8
 *  SCLK: DIO10
 *  LaunchPad SPI Bus
 *  CSN: undefined
 */
extern const uint_least8_t              CONFIG_NVS_0_CONST;
#define CONFIG_NVS_0                    1
#define CONFIG_TI_DRIVERS_NVS_COUNT     2




/*
 *  ======== SPI ========
 */

/*
 *  PICO: DIO29
 *  POCI: DIO28
 *  SCLK: DIO27
 */
extern const uint_least8_t              CONFIG_SPI_LCD_CONST;
#define CONFIG_SPI_LCD                  0
/*
 *  PICO: DIO9
 *  POCI: DIO8
 *  SCLK: DIO10
 *  LaunchPad SPI Bus
 */
extern const uint_least8_t              CONFIG_SPI_0_CONST;
#define CONFIG_SPI_0                    1
#define CONFIG_TI_DRIVERS_SPI_COUNT     2


/*
 *  ======== Timer ========
 */

extern const uint_least8_t                  CONFIG_TIMER_0_CONST;
#define CONFIG_TIMER_0                      0
#define CONFIG_TI_DRIVERS_TIMER_COUNT       1


/*
 *  ======== UART2 ========
 */

/*
 *  TX: DIO3
 *  RX: DIO2
 *  XDS110 UART
 */
extern const uint_least8_t                  CONFIG_DISPLAY_UART_CONST;
#define CONFIG_DISPLAY_UART                 0
#define CONFIG_TI_DRIVERS_UART2_COUNT       1


/*
 *  ======== Button ========
 */

extern const uint_least8_t                  BTN_DWN_CONST;
#define BTN_DWN                             0
extern const uint_least8_t                  BTN_UP_CONST;
#define BTN_UP                              1
extern const uint_least8_t                  BTN_ENTR_CONST;
#define BTN_ENTR                            2
extern const uint_least8_t                  BTN_EXIT_CONST;
#define BTN_EXIT                            3
#define CONFIG_TI_DRIVERS_BUTTON_COUNT      4


/*
 *  ======== LED ========
 */

extern const uint_least8_t              CONFIG_LED_RED_CONST;
#define CONFIG_LED_RED                  0
extern const uint_least8_t              CONFIG_LED_GREEN_CONST;
#define CONFIG_LED_GREEN                1
#define CONFIG_TI_DRIVERS_LED_COUNT     2


/*
 *  ======== GPTimer ========
 */

extern const uint_least8_t                  CONFIG_TIMER_0_GP_CONST;
#define CONFIG_TIMER_0_GP                   0
#define CONFIG_TI_DRIVERS_GPTIMER_COUNT     1


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
