# Arduino IDE Timer broker for uTimerLib - uTimerBrokerLib


## What is this repository for?

Broker library to manage multiple interrupts with uTimerLib.

It allows to attach multiple interrupts to uTimerLib, but at the cost of reducing resolution to miliseconds instead nanoseconds.

## Important: Dependencies

This library requires uTimerLib libary; it's available on IDE Library Manager and also here:

https://github.com/Naguissa/uTimerLib

https://github.com/Naguissa/uTimerLib/releases


## Usage ##

1st we get a class instance:

**uTimerBrokerLib TimerBrokerLib = uTimerBrokerLib::instance();**


You have these methods:
 - **uTimerBrokerLib.add(callback_function, miliseconds);** : callback_function will be called each miliseconds. Adds it on 1st free slot.
 - **uTimerBrokerLib.set(callback_function, slot, miliseconds);** : callback_function will be called each miliseconds. Adds it on indicated slot. If any exists will be overwritten.
 - **uTimerBrokerLib.clear(slot);** : Clears given slot.
 - **uTimerBrokerLib.clear(callback_function);** : Search for callback function and clears that slot if found.


## How do I get set up?

You can get it from Arduino libraries directly, searching by uTimerBrokerLib.

For manual installation:

 * Get the ZIP from releases link: https://github.com/Naguissa/uTimerBrokerLib/releases
 * Rename to uTimerBrokerLib.zip
 * Install library on Arduino


## Documentation and extras

You can find all documentation and extras in this repository: https://github.com/Naguissa/uTimerBrokerLib_doc_and_extras

You can read documentation online here: https://naguissa.github.io/uTimerBrokerLib_doc_and_extras/



## Examples

Included on example folder, available on Arduino IDE.


## Who do I talk to?

 * [Naguissa](https://github.com/Naguissa)
 * https://www.foroelectro.net
 * https://www.naguissa.com


## Contribute

Any code contribution, report or comment are always welcome. Don't hesitate to use GitHub for that.


 * You can sponsor this project using GitHub's Sponsor button: https://github.com/Naguissa/uTimerBrokerLib
 * You can make a donation via PayPal: https://paypal.me/foroelectro


Thanks for your support.


Contributors hall of fame: https://www.foroelectro.net/hall-of-fame-f32/contributors-contribuyentes-t271.html
