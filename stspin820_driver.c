
#include "drivers/tm4c_stspin820/stspin820_driver.h"
/// \cond
#include <stdbool.h>
#include <stdint.h>
/// \endcond
#include <tm4c_utils/pins.h>
#include "tm4c_utils/timers.h"

static void runForward(stspin820_driver_t* driver, uint32_t frequency_hz) {
    driver->frequency_hz = frequency_hz;
    // NOTE: When timer prescaler is 0, set a frequency < 500 hz will cause faults
    if (frequency_hz < 500) {
        return;
    }
    driver->timer->configureFrequency(driver->timer, driver->frequency_hz);
    driver->timer->enable(driver->timer);
    pinWrite(driver->pin_dir, FORWARD);
    driver->enable(driver);
}

static void runBackward(stspin820_driver_t* driver, uint32_t frequency_hz) {
    driver->frequency_hz = frequency_hz;
    if (frequency_hz < 500) {
        return;
    }
    driver->timer->configureFrequency(driver->timer, driver->frequency_hz);
    driver->timer->enable(driver->timer);
    pinWrite(driver->pin_dir, BACKWARD);
    driver->enable(driver);
}

static void enable(stspin820_driver_t* driver) {
    pinWrite(driver->pin_en, 0);
    pinWrite(driver->pin_stby, 1);
}

static void disable(stspin820_driver_t* driver) {
    pinWrite(driver->pin_en, 1);
    pinWrite(driver->pin_stby, 0);
    driver->timer->disable(driver->timer);
    pinWrite(driver->pin_step, 0);
}

static void standBy(stspin820_driver_t* driver) {
    pinWrite(driver->pin_en, 0);
    pinWrite(driver->pin_stby, 1);
    driver->timer->disable(driver->timer);
    pinWrite(driver->pin_step, 0);
}

static void configStepMode(stspin820_driver_t* driver, step_mode_t step_mode) {
    pinWrite(driver->m1, step_mode & 0b0001);
    pinWrite(driver->m2, (step_mode & 0b0010) >> 1);
    pinWrite(driver->m3, (step_mode & 0b0100) >> 2);
}

void setupStepMotor(stspin820_driver_t* driver, step_mode_t step_mode) {
    driver->runForward = &runForward;
    driver->runBackward = &runBackward;
    driver->enable = &enable;
    driver->disable = &disable;
    driver->standBy = &standBy;
    driver->configStepMode = &configStepMode;

    driver->configStepMode(driver, step_mode);
}
