/*
  OrangutanMotors.cpp - Library for using the motor drivers on the
      Orangutan LV, SV, SVP, Baby Orangutan B, or 3pi robot.
	  The timer2 overflow ISR is designed to work with Arduino 12
	  and will not work properly with earlier versions of the Arduino
	  environment.
*/

/*
 * Written by Ben Schmidel, May 15, 2008.
 * Last modified: September 29, 2008
 * Copyright (c) 2008-2011 Pololu Corporation. For more information, see
 *
 *   http://www.pololu.com
 *   http://forum.pololu.com
 *   http://www.pololu.com/docs/0J18
 *
 * You may freely modify and share this code, as long as you keep this
 * notice intact (including the two links above).  Licensed under the
 * Creative Commons BY-SA 3.0 license:
 *
 *   http://creativecommons.org/licenses/by-sa/3.0/
 *
 * Disclaimer: To the extent permitted by law, Pololu provides this work
 * without any warranty.  It might be defective, in which case you agree
 * to be responsible for all resulting costs and damages.
 */

#ifndef F_CPU
#define F_CPU 16000000UL	// Orangutans run at 20 MHz
#endif //!F_CPU

#include <avr/interrupt.h>
#include <avr/io.h>
#include "OrangutanMotors.h"
#include "../OrangutanDigital/OrangutanDigital.h"
#include "../OrangutanResources/include/OrangutanModel.h"
#ifdef _ORANGUTAN_X2
#include "../OrangutanX2/OrangutanX2.h"
#endif

#ifdef _ORANGUTAN_SVP

#define PWM2A	IO_D7
#define PWM2B	IO_D6
#define DIRA	IO_C7
#define	DIRB	IO_C6

#else

//#define PWM0A	IO_D6
//#define PWM0B	IO_D5
//#define PWM2A	IO_B3
//#define PWM2B	IO_D3

#define PWM0A	IO_D6
#define	PWM0B	IO_D5
#define PWM1A	IO_B1
#define PWM1B	IO_B2

#endif


extern "C" void set_m1_speed(int speed)
{
	OrangutanMotors::setM1Speed(speed);
}

extern "C" void set_m2_speed(int speed)
{
	OrangutanMotors::setM2Speed(speed);
}

extern "C" void set_motors(int m1, int m2)
{
	OrangutanMotors::setSpeeds(m1, m2);
}


// constructor

OrangutanMotors::OrangutanMotors()
{
}


// initialize timers 0 and 2 to generate the proper PWM ouputs
// to the motor drivers
void OrangutanMotors::init2()
{

#if !defined(_ORANGUTAN_X2)
	/*  40 kHz operation (3pi, Orangutan SV and SVP, and Baby Orangutan B can handle this, Orangutan LV cannot)
	*** Note that using these settings will break OrangutanTime and QTRsensors ***
	// configure for inverted phase-correct PWM output on motor control pins:   
    //  set OCxx on compare match, clear on timer overflow   
    //  Timer0 and Timer2 count up from 0 to 255 and then counts back down to 0  
    TCCR0A = TCCR2A = 0xF1;
  
    // use the system clock (=20 MHz) as the timer clock,
	// which will produce a PWM frequency of 39 kHz (because of phase-correct mode)
    TCCR0B = TCCR2B = 0x01;
	*/

	// configure for inverted fast PWM output on motor control pins:   
    //  set OCxx on compare match, clear on timer overflow   
    //  Timer0 and Timer2 counts up from 0 to 255 and then overflows directly to 0   
    TCCR0A =  0xF3;                                /////////////////////////////////////////////Change it
	TCCR1A = 0xF1;
 
#ifndef ARDUINO	
    // use the system clock/8 (=2.5 MHz) as the timer clock,
	// which will produce a PWM frequency of 10 kHz
	// Arduino uses Timer0 for timing functions like micros() and delay() so we can't change it
    TCCR0B = 0x02;                               /////////////////////////////////////////////Change it
	TCCR1B = 0x09;
#endif

	// use the system clock (=20 MHz) as the timer clock,
	// which will produce a PWM frequency of 78 kHz.  The Baby Orangutan B
	// and 3Pi can support PWM frequencies this high.  The
	// Orangutan LV-168 cannot support frequencies above 10 kHz.
    //TCCR0B = TCCR2B = 0x01;

    // initialize all PWMs to 0% duty cycle (braking)   
    OCR0A = OCR0B = OCR1A = OCR1B = 0;    /////////////////////////////////////////////Change it                 
	
	OrangutanDigital::setOutput(PWM0A, 0);
	OrangutanDigital::setOutput(PWM0B, 0);
	OrangutanDigital::setOutput(PWM1A, 0);
	OrangutanDigital::setOutput(PWM1B, 0);

#endif
}


// sets the motor speed.  The sign of 'speed' determines the direction
// and the magnitude determines the speed.  limits: -255 <= speed < 255
// |speed| = 255 produces the maximum speed while speed = 0 is full brake.
void OrangutanMotors::setM1Speed(int speed)
{
	init();
	unsigned char reverse = 0;

	if (speed < 0)
	{
		speed = -speed;	// make speed a positive quantity
		reverse = 1;	// preserve the direction
	}
	if (speed > 0xFF)	// 0xFF = 255
		speed = 0xFF;
		
	if (reverse)
	{
		OCR0B = 0;		// hold one driver input high
		OCR0A = speed;	// pwm the other input
	}
	else	// forward
	{
		OCR0B = speed;	// pwm one driver input
		OCR0A = 0;		// hold the other driver input high
	}
}

void OrangutanMotors::setM2Speed(int speed)
{
	init();
	unsigned char reverse = 0;

	if (speed < 0)
	{
		speed = -speed;	// make speed a positive quantity
		reverse = 1;	// preserve the direction
	}
	if (speed > 0xFF)	// 0xFF = 255
		speed = 0xFF;
		
	if (reverse)
	{
		OCR1B = 0;		// hold one driver input high
		OCR1A = speed;	// pwm the other input
	}
	else	// forward
	{
		OCR1B = speed;	// pwm one driver input
		OCR1A = 0;		// hold the other driver input high
	}
}


void OrangutanMotors::setSpeeds(int m1Speed, int m2Speed)
{
	setM1Speed(m1Speed);
	setM2Speed(m2Speed);
}

// Local Variables: **
// mode: C++ **
// c-basic-offset: 4 **
// tab-width: 4 **
// indent-tabs-mode: t **
// end: **
