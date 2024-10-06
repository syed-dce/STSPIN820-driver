
#ifndef SRC_DRIVERS_TM4C_STSPIN820_STSPIN820_DRIVER_H_
#define SRC_DRIVERS_TM4C_STSPIN820_STSPIN820_DRIVER_H_
/// \cond
#include <stdbool.h>
#include <stdint.h>
/// \endcond
#include <tm4c_utils/pins.h>
#include "tm4c_utils/timers.h"

/* Step mode pre-scaler selection*/
typedef enum {
    STEP_1_1 = 0b0000,
    STEP_1_2 = 0b0001,
    STEP_1_4 = 0b0010,
    STEP_1_8 = 0b0011,
    STEP_1_16 = 0b0100,
    STEP_1_32 = 0b0101,
    STEP_1_128 = 0b0110,
    STEP_1_256 = 0b0111,
} step_mode_t;

typedef enum { BACKWARD = 0U, FORWARD = 1U } dir_mode_t;

/* Legacy functions to handle normal driver operations*/
typedef struct stspin820_driver stspin820_driver_t;

/* 
 * Library - driver base structure
 */
struct stspin820_driver {
    pin_t* pin_en;
    pin_t* pin_dir;
    pin_t* pin_step;
    pin_t* pin_stby;
    pin_t* m1;
    pin_t* m2;
    pin_t* m3;
    uint16_t step_mode;
    uint32_t frequency_hz;
    timer_module_t* timer;
    void (*runForward)(stspin820_driver_t*, uint32_t);
    void (*runBackward)(stspin820_driver_t*, uint32_t);
    void (*enable)(stspin820_driver_t*);
    void (*disable)(stspin820_driver_t*);
    void (*standBy)(stspin820_driver_t*);
    void (*configStepMode)(stspin820_driver_t*, step_mode_t);
};

/* Assign local functions and another initial local configuration*/
void setupStepMotor(stspin820_driver_t* driver, step_mode_t step_mode);

#endif /* SRC_DRIVERS_TM4C_STSPIN820_STSPIN820_DRIVER_H_ */
