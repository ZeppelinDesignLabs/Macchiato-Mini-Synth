/*
This is a variant file for Arduino to add the ATMEGA 644PA TQFP package.
Author:	Stephen Cass
Notes:	Lets hope it works....

*/


#ifndef ATMEGA_644_PA_H
#define ATMEGA_644_PA_H

#include <avr/pgmspace.h>

static const uint8_t SS	= 44;
static const uint8_t MOSI	= 1;
static const uint8_t MISO	= 2;
static const uint8_t SCK	= 3;

static const uint8_t SDA	= 20;
static const uint8_t SCL	= 19;

//#define LED_BUILTIN	

static const uint8_t A0	= 31;
static const uint8_t A1	= 30;
static const uint8_t A2	= 29;
static const uint8_t A3	= 28;
static const uint8_t A4	= 27;
static const uint8_t A5	= 26;
static const uint8_t A6	= 25;
static const uint8_t A7 = 24;

//	ATMEL ATMEGA644PA TQFP Package
//						  P  P  P  P  P  G  V  P  P  P  P
//						  B  B  B  B  B  N  C  A  A  A  A
//						  4  3  2  1  0  D  C  0  1  2  3
//						  44 43 42 41 40 39 38 37 36 35 34
//						  _________________________________
//				PB5		 1|								  |33	PA4 
//				PB6		 2|								  |32	PA5 
//				PB7		 3|								  |31	PA6 
//				RST		 4|								  |30	PA7 
//				VCC		 5|								  |29	AREF 
//				GND		 6|								  |28	GND
//				XTAL2	 7|								  |27	AVCC
//				XTAL1	 8|								  |26	PC7 
//				PD0		 9|								  |25	PC6 
//				PD1		10|								  |24	PC5 
//				PD2		11|_______________________________|23	PC4 
//						  12 13 14 15 16 17 18 19 20 21 22 
//						  P  P  P  P  P  V  G  P  P  P  P
//						  D  D  D  D  D  C  N  C  C  C  C
//						  3  4  5  6  7  C  D  0  1  2  3
/*
The following information is for the pin mapping to arduino.  It has the following format;
Package_Pin#	Digital_Pin#/Extra_features

	1	D13/MOSI |	12	D3		|	23	D20		 |	34	D28/ADC3
	2	D14/MISO |	13	D4/PWM	|	24	D21		 |	35	D29/ADC2
	3	D15/SCK	 |	14	D5/PWM	|	25	D22		 |	36	D30/ADC1
	4	RST		 |	15	D6/PWM	|	26	D23		 |	37	D31/ADC0
	5	VCC		 |	16	D7/PWM	|	27	AVCC	 |	38	VCC
	6	GND		 |	17	VCC		|	28	GND		 |	39	GND
	7	XTAL1	 |	18	GND		|	29	AREF	 |	40	D8
	8	XTAL2	 |	19	D16/SCL	|	30	D24/ADC7 |	41	D9
	9	D0/RX0	 |	20	D17/SDA	|	31	D25/ADC6 |	42	D10
	10	D1/TX0	 |	21	D18		|	32	D26/ADC5 |	43	D11/PWM
	11	D2		 |	22	D19		|	33	D27/ADC4 |	44	D12/SS/PWM
*/

#define NUM_DIGITAL_PINS	24
#define NUM_ANALOG_INPUTS	8

#define analogInputToDigitalPin(p)	((p < 8) ? 31 - (p): -1)
#define analogPinToChannel(p)		((p < 8) ? (p) : 31 - (p))

#define digitalPinHasPWM(p)			((p) == 13 || (p) == 14 || (p) == 15 || (p) == 16 || (p) == 43 || (p) == 44)

#define digitalPinToPCICR(p)        ( (((p) >= 0) && ((p) <= 31)) ? (&PCICR) : ((uint8_t *)0) )

#define digitalPinToPCICRbit(p)     ( (((p) >= 24) && ((p) <= 31)) ? 0 : \
                                    ( (((p) >=  0) && ((p) <=  7)) ? 1 : \
                                    ( (((p) >= 16) && ((p) <= 23)) ? 2 : \
                                    ( (((p) >=  8) && ((p) <= 15)) ? 3 : \
                                    0 ) ) ) )

#define digitalPinToPCMSK(p)        ( (((p) >= 24) && ((p) <= 31)) ? (&PCMSK0) : \
                                    ( (((p) >=  0) && ((p) <=  7)) ? (&PCMSK1) : \
                                    ( (((p) >= 16) && ((p) <= 23)) ? (&PCMSK2) : \
                                    ( (((p) >=  8) && ((p) <= 15)) ? (&PCMSK3) : \
                                    ((uint8_t *)0) ) ) ) )


#define digitalPinToPCMSKbit(p)     ( (((p) >= 24) && ((p) <= 31)) ? (31 - (p)) : \
                                    ( (((p) >=  0) && ((p) <=  7)) ? (p) : \
                                    ( (((p) >= 16) && ((p) <= 23)) ? ((p) - 16) : \
                                    ( (((p) >=  8) && ((p) <= 15)) ? ((p) - 8) : \
                                    0 ) ) ) )

#define digitalPinToInterrupt(p)    ((p) == 10 ? 0 : ((p) == 11 ? 1 : ((p) == 2 ? 2 : NOT_AN_INTERRUPT)))

#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,

};

const uint16_t PROGMEM port_to_output_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,

};

const uint16_t PROGMEM port_to_input_PGM[] = 
{
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,

};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = 
{
	PD,	//0	PORTD
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PB,	//8 PORTB
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PC,	//16 PORTC
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
	PA,	//24 PORTA
	PA,
	PA,
	PA,
	PA,
	PA,
	PA,
	PA	//31

};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = 
{
	_BV(0),	//0 PORTD
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),	
	_BV(0),	//8 PORTB
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0),	//16 PORTC
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(7),	//24 PORTA
	_BV(6),
	_BV(5),
	_BV(4),
	_BV(3),
	_BV(2),
	_BV(1),
	_BV(0)

};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = 
{


};

#endif

#define SERIAL_PORT_MONITOR		Serial
#define SERIAL_PORT_HARDWARE	Serial

#ifndef UBRR1H
	#define SERIAL_PORT_HARDWARE1		Serial1
	#define SERIAL_PORT_HARDWARE_OPEN	Serial1
#endif

#endif