/*
 * masterTimer.h
 *
 *  Created on: 21 paü 2018
 *      Author: HorochovPL
 */

#ifndef AVRBACKGROUNDTIMER_H_
#define AVRBACKGROUNDTIMER_H_


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




#endif /* AVRBACKGROUNDTIMER_H_ */
