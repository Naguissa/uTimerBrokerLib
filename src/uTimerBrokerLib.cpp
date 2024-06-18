/**
 * \class uTimerBrokerLib
 * \brief Broker library for uTimerLib
 *
 * Adds multiple timed functions support to uTimerLib
 *
 * Decreases resolution to miliseconds
 *
 * Library depends on uTimerLib library, https://github.com/Naguissa/uTimerLib
 *
 * @see <a href="https://github.com/Naguissa/uTimerBrokerLib">https://github.com/Naguissa/uTimerBrokerLib</a>
 * @see <a href="https://github.com/Naguissa/uTimerLib">https://github.com/Naguissa/uTimerLib</a> - Needed dependecy
 * @see <a href="mailto:naguissa@foroelectro.net">naguissa@foroelectro.net</a>
 * @version 1.0.1
 */
#include <Arduino.h>
#include "uTimerBrokerLib.h"

#ifndef _uTimerBrokerLib_cpp_
    #define _uTimerBrokerLib_cpp_
    #include "uTimerBrokerLib.h"

    uTimerBrokerLib *uTimerBrokerLib::_instance;
    void (*uTimerBrokerLib::_functions[UTIMERBROKERLIB_MAXHOOKS])();
    int32_t uTimerBrokerLib::_intervals[UTIMERBROKERLIB_MAXHOOKS];
    volatile int32_t uTimerBrokerLib::_left[UTIMERBROKERLIB_MAXHOOKS];

    /**
     * \brief Private constructor
     *
     * Prepares internal data
     */
    uTimerBrokerLib::uTimerBrokerLib() {
            _instance = this;
        // zerofill control array
        for (uint8_t i = 0; i < UTIMERBROKERLIB_MAXHOOKS; i++) {
            _intervals[i] = 0;
        }
        TimerLib.setInterval_us(uTimerBrokerLib::interrupt, 1000);
    }

    /**
     * \brief Used to instatiate main object
     *
     * @return Instance of object
     */
    uTimerBrokerLib uTimerBrokerLib::instance(void) {
        if (_instance == NULL) {
            uTimerBrokerLib();
        }
        return *_instance;
    }


    /**
     * \brief Sets a function in a given slot
     *
     * @param userfunction function pointer to be called
     * @param slot position where to store
     * @param ms period of function call, in miliseconds
     * @return slot where function is placed. Useful to clear or overwrite it. UTIMERBROKERLIB_ERROR if slot > space
     */
    uint8_t uTimerBrokerLib::set(void (* userfunction)(), const uint8_t slot, const int32_t ms) {
        if (ms > 0 && slot < UTIMERBROKERLIB_MAXHOOKS) {
            _intervals[slot] = _left[slot] = ms;
            _functions[slot] = userfunction;
            return slot;
        }
        return UTIMERBROKERLIB_ERROR;
    }

    /**
     * \brief Adds a function in 1st available slot
     *
     * @param userfunction function pointer to be called
     * @param ms period of function call, in miliseconds
     * @return slot where function is placed. Useful to clear or overwrite it. UTIMERBROKERLIB_ERROR if no space available
     */
    uint8_t uTimerBrokerLib::add(void (* userfunction)(), const int32_t ms) {
        if (ms > 0) {
            for (uint8_t i = 0; i < UTIMERBROKERLIB_MAXHOOKS; i++) {
                if (_intervals[i] == 0) {
                    _intervals[i] =  _left[i] = ms;
                    _functions[i] = userfunction;
                    return i;
                }
            }
        }
        return UTIMERBROKERLIB_ERROR;
    }

    /**
     * \brief Clears a given slot
     *
     * @return Slot cleared. UTIMERBROKERLIB_ERROR if not found
     */
    uint8_t uTimerBrokerLib::clear(const uint8_t slot) {
        if (slot < UTIMERBROKERLIB_MAXHOOKS) {
            _intervals[slot] = 0;
            return slot;
        }
        return UTIMERBROKERLIB_ERROR;
    }


    /**
     * \brief Removes 1s appearance of give function from slots
     *
     * @param userfunction function pointer to be called
     * @return Slot cleared. UTIMERBROKERLIB_ERROR if not found
     */
    uint8_t uTimerBrokerLib::clear(void (* userfunction)()) {
        for (uint8_t i = 0; i < UTIMERBROKERLIB_MAXHOOKS; i++) {
            if (_intervals[i] > 0 && _functions[i] == userfunction) {
                _intervals[i] = 0;
                return i;
            }
        }
        return UTIMERBROKERLIB_ERROR;
    }


    /**
     * \brief Main private interrupt loop
     *
     * Checks and decrements all active functions
     */
    void uTimerBrokerLib::interrupt(void) {
        for (uint8_t i = 0; i < UTIMERBROKERLIB_MAXHOOKS; i++) {
            if (_intervals[i] > 0) {
                _left[i]--;
                if (_left[i] < 1) {
                    _left[i] += _intervals[i];
                    _functions[i]();
                }
            }
        }
    }
#endif

