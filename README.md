# elapsedTime
This code implements arduino-like millis() functions, written in clear C and tested on atmega328.



# Functions
## void timer_init(void)
Sets up 8bit timer0 to CTC mode, 1ms interval and turns it on.



## void timer_disable() and void timer_enable()
Turn on/off timer via setting prescaler.

## void timer_reset(void)
Set elapsed time to 0

## uint32_t timer_getMs(void) and uint32_t timer_getUs(void)
Returns time in millisecounds since init or reset call. Also callable by alias `millis()`.

## uint32_t timer_getUs(void);
Returns time in microsecounds since init or reset call. Also callable by alias `micros()`.

This function uses timer register TIFRx to get relatively high accouracy without spamming with interrupts.

Lowest accouracy is something like 8us, will depend on F_CPU like this: `1/((F_CPU/1000/64)-1)`

Copied from arduino source.


## uint32_t timer_getSec(void);
Returns time in secounds since init or reset call. 
