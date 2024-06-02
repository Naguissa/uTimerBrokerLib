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
 * @version 1.0.0
 */
#include <Arduino.h>
#include "uTimerBrokerLib.h"

/**
 * \brief Static variable assignment to NULL
 */
uTimerBrokerLib * uTimerBrokerLib::_instance = NULL;



uTimerBrokerLib::uTimerBrokerLib() {
    // zerofill control array
    for (uint8_t i = 0; i < UTIMERBROKERLIB_MAXHOOKS; i++) {
        _intervals[i] = 0;
    }
	TimerLib.setInterval_us(uTimerBrokerLib::interrupt, 1000);
}

/**
 * \brief Class initialization
 * @return true if correct, false if already init.
 */
uTimerBrokerLib* uTimerBrokerLib::init() {
	extern uTimerLib TimerLib;
	if (_instance == NULL) {
		_instance = uTimerBrokerLib();
		return _instance;
	}
	return null;
}


/**
 * \brief Sets a function in a given slot
 *
 * @param userfunction function pointer to be called
 * @param slot position where to store 
 * @param ms period of function call, in miliseconds
 * @return slot where function is placed. Useful to clear or overwrite it. UTIMERBROKERLIB_ERROR if slot > space
 */
uint8_t uTimerBrokerLib::set(const void *userfunction, const uint8_t slot, const uint32_t ms) {
    if (slot < UTIMERBROKERLIB_MAXHOOKS) {
        _intervals[slot] = ms;
        _left[slot] = ms;
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
uint8_t uTimerBrokerLib::add(const void *userfunction, const uint32_t ms) {
    for (uint8_t i = 0; i < UTIMERBROKERLIB_MAXHOOKS; i++) {
        if (_intervals[i] == 0) {
            _intervals[slot] = ms;
            _left[slot] = ms;
            _functions[slot] = userfunction;
            return i;
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
uint8_t uTimerBrokerLib::clear(const void *userfunction) {
    for (uint8_t i = 0; i < UTIMERBROKERLIB_MAXHOOKS; i++) {
        if (_intervals[i] > 0 && _functions[i] == userfunction) {
            _intervals[i] = 0;
            return i;
        }
    }
    return UTIMERBROKERLIB_ERROR;
}

/**
 * \brief Main public interrupt loop
 *
 * Calls private loop
 */

void uTimerBrokerLib::interrupt() {
	_instance->_interrupt();
}



/**
 * \brief Main private interrupt loop
 *
 * Checks and decrements all active functions
 */
void uTimerBrokerLib::_interrupt(void) {
    for (uint8_t i = 0; i < UTIMERBROKERLIB_MAXHOOKS; i++) {
        if (_intervals[i] > 0) {
            if (--_left[i] == 0) {
                _left[i] = _intervals[i];
                _functions[i]();
            }
        }
    }
}


/**
 * \brief Preinstantiate Object
 *
 * Now you can use al functionality calling TimerBrokerLib.function
 */
uTimerBrokerLib TimerBrokerLib = uTimerBrokerLib();



