/*
 * elapsedTime.h
 *
 *  Created on: 21.10.2018
 *      Author: HorochovPL
 */

#ifndef ELAPSEDTIME_H_
#define ELAPSEDTIME_H_

/*
 * Allows you to call "timer_registerCallback(void(*fun)(void), unsigned int waitTimeMs);"
 * where fun is pointer to your function, and waitTimeMs time between function calls in ms.
 */
#define TIMER_ENABLE_CALLBACK 1

#ifdef TIMER0_IN_USE
	//This is just my convention. If any of my libs use this timer, will warn me.
	#warning Timer0 code collision
#endif
#define TIMER0_IN_USE 1

void timer_init(void);
void timer_enable();
void timer_disable();
void timer_reset(void);

uint32_t timer_getMs(void);
#define millis() timer_GetMs()
uint32_t timer_getUs(void);
#define micros() timer_GetUs()
uint32_t timer_getSec(void);

#if TIMER_ENABLE_CALLBACK>0
void timer_registerCallback(void(*fun)(void), unsigned int waitTimeMs);
#endif



#endif /* ELAPSEDTIME_H_ */
