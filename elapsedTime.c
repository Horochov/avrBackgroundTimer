/*
 * elapsedTime.c
 *
 *  Created on: 21.10.2018
 *      Author: HorochovPL
 */
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "elapsedTime.h"



static volatile uint32_t elapsedTimeMs;

//interrupt every 1ms. Feel free to add your code here
ISR(TIMER0_COMPA_vect)
{
	//H3H3, it's shorter than an arduino interrupt.
	elapsedTimeMs++;

}

void timer_enable()
{
	TCCR0B|=(1<<CS00)|(1<<CS01);
}
void timer_disable()
{
	TCCR0B&=~((1<<CS00)|(1<<CS01));
}
void timer_reset(void)
{
	elapsedTimeMs=0;
#if defined(TCNT0)
	TCNT0=0;
#else
	TCNT0L=0;
#endif
}
uint32_t timer_getMs(void)
{
	return elapsedTimeMs;
}

uint32_t timer_getUs(void)
{
/*
 * arduino source based. Pretty clever
 * Uses milisecound buffer and current timer0 value combined to achieve 8us accuracy.
 */
	uint32_t m;
    uint8_t oldSREG = SREG,
    		t;

    cli();
    m = elapsedTimeMs;
#if defined(TCNT0)
    t = TCNT0;
#elif defined(TCNT0L)
    t = TCNT0L;
#else
    #error TIMER 0 not defined
#endif


    //if we just overflowed without interrupt
#ifdef TIFR0
    if ((TIFR0 & (1<<OCF0A)) && t )
        m++;
#else
    if ((TIFR & (1<<OCF0A)) && t )
        m++;
#endif

    SREG = oldSREG;
    //got data, now huuumphh... Combined!
    return ((m*1000)+(t<<3));
    //hw multiplier is lovely <3
}

uint32_t timer_getSec(void)
{
	//confirmed, it's faster than division!
	return elapsedTimeMs*0.001;
}

void timer_init(void)
{
	TCCR0A=(1<<WGM01);
	#define timerPrescaler ((F_CPU/1000/64)-1)
	#if ((timerPrescaler>255)||(timerPrescaler<0))
		#error backgroundTimer bad prescaler!
	#endif
	OCR0A=timerPrescaler;
	#undef timerPrescaler
	TIMSK0|=(1<<OCIE0A);
	timer_enable();
}
