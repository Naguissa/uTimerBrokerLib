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
/** \file uTimerBrokerLib.h
 *   \brief uTimerBrokerLib header file
 */
#ifndef _uTimerBrokerLib_
	/**
	 * \brief Prevent multiple inclussion
	 */
	#define _uTimerBrokerLib_

	#include "Arduino.h"
	#include "uTimerBrokerLib.h"


    #define UTIMERBROKERLIB_ERROR 255

    #ifndef UTIMERBROKERLIB_MAXHOOKS
        /**
         * \brief UTIMERBROKERLIB_MAXHOOKS maximum number of attached functions
         *
         * This is limited to uint8_t max - 1, [1-254]
         */
        #define UTIMERBROKERLIB_MAXHOOKS 12
    #endif

	class uTimerBrokerLib {
		public:
			uint8_t add(void *);
			uint8_t set(const void *, const uint8_t, const uint32_t);
			uint8_t clear(uint8_t);
			uint8_t clear(void *);
			static void interrupt(void);
			uTimerBrokerLib* init();

		private:
			// Constructor
			uTimerBrokerLib();
			static uTimerBrokerLib *_instance;
						
			void _interrupt(void);

            void* _functions[UTIMERBROKERLIB_MAXHOOKS];
            uint32_t _intervals[UTIMERBROKERLIB_MAXHOOKS];
            uint32_t _left[UTIMERBROKERLIB_MAXHOOKS];
	};
	
	extern uTimerBrokerLib TimerBrokerLib;	
#endif

