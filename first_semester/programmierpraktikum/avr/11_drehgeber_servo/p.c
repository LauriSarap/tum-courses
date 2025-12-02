#include <avr/io.h>
#include <avr/interrupt.h>


// Taktrate Prozessor: 20 MHz => 1 Takt (1 cycle) dauert 50 ns


#define DREHGEBER_DELTA	100


// Drehgeber

ISR(INT0_vect)
{
	// Linksdrehung









	// Rechtsdrehung








}


int main(void)
{

	DDRD = 32;	// PD5 als Ausgang (OC1A)

	// Interrupts global freischalten
	SREG = 128;

	// Drehgeber
	EIMSK = 1;		// INT0 Interrupt freischalten
	EICRA = 3;		// Für INT0 steigende Flanke als Auslöser auswählen



	// Servo-Signale auf Wikipedia: https://en.wikipedia.org/wiki/Servo_control#/media/File:Servomotor_Timing_Diagram.svg
	// PWM Zyklus dauert 20 ms
	// Neutralstellung: 1,5 ms High-Pegel und 18,5 ms Low-Pegel
	// 90 Grad links: 1 ms High-Pegel und 19 ms Low-Pegel
	// 90 Grad rechts: 2 ms High-Pegel und 18 ms Low-Pegel


	// Überschlagung 8 Bit PWM
	// 20 ms müssen auf 0 ... 255 abgebildet werden
	// 20 MHz => 50 ns Zykluszeit
	// Prescaler 1024 => 50 ns x 1024 = 51,2 µs pro TCNT-increase
	// 51,2 µs * 255 = 13 ms
	// => zu wenig für 20 ms Zykluszeit, es sei denn, man verwendet Software-PWM

	// Überschlagung 16 Bit PWM
	// 20 ms müssen auf 0 ... 65.535 abgebildet werden
	// 20 MHz => 50 ns Zykluszeit
	// Prescaler 8 => 50 ns x 8 = 400 ns pro TCNT-increase
	// 400 ns * 65535 = 26 ms; passt perfekt für 20 ms Zykluszeit
	// Anzahl TCNT-increases für 20 ms: 20 ms / (50 ns * 8) =
	// = 20.000.000 / 400 = 50.000
	// "Fast-PWM-Mode" verwenden, dann geht der Timer immer von 0 bis oberen
	// Grenzwert und startet danach wieder bei 0 für den nächsten Zyklus
	// WGM1 (zusammengesetzt aus Bits in TCCR1A und TCCR1B) auf 14 dezimal
	// = 1110 binär setzen => Timer Untergrenze = 0, Timer Obergrenze = ICR1
	// => ICR1 auf 50.000 setzen, dann läuft Timer von 0 bis 50.000 und
	// man hat genau 20 ms Zykluszeit




	// TIMSK1 = 6;		// Enable Interrupt for Output Compare A and B Match
	// TIMSK1 |= 1;	// Enable T1 overflow 


	// Fast-PWM-Mode einstellen
	// TCCR1A = 0xA0;	// S. 175/176: Clear OC1A/B on compare match
	TCCR1A = 0x80;		
	TCCR1A |= 2;	// S. 136: set lower 2 bits of 4 bit WGM1 (WGM1 muss 14 = 1110 sein)
	TCCR1B = 2;		// prescaler 8 => 26 ms für 16 Bit Range
	TCCR1B |= 24;	// set upper 2 bits of 4 bit WGM1 (WGM1 muss 14 = 1110 sein)


	// In OCR1A/B die Mittenposition (= 1,5 ms) setzen
	// 50.000 Zählerschritte = 20 ms
	// 1,5 ms = (50.000 * 1,5) / 20 => 3750;
	OCR1A = 3750;		// Mittenposition: 1,5 ms
	// OCR1B = 3750;		// Mittenposition: 1,5 ms

	// Miuzei-Servos von Amazon:
	//
	// 500 µs => (50.000 * 0,5) / 20 => 1.250
	// 2500 µs => (50.000 * 2,5) / 20 => 6.250

	// Ausschlag +90 Grad: 2 ms = 5.000 Zählerschritte
	// Ausschlag -90 Grad: 1 ms = 2.500 Zählerschritte

	// Anzahl Zähler-Schritte für 90 Grad: 20
	// 1250 / 20 = 62,5 => pro Drehgeber-Interrupt Änderung um 50
 
	// wir brauchen non inverting compare output mode

	// In ICR1 und OCR1A die Auflösung auf 16 Bit setzen (max)

	// S. 129: Zähler erhöht sich bis Wert in ICR1 erreicht, wenn WGM1_3:0 = 14


	// ICR1 so setzen, dass nach 20 ms der Timer wieder bei 0 anfängt
	// 1 Takt = 50 ns
	// 20 Takte = 1 µs
	// 20.000 Takte = 1 ms
	// 20.000 x 20 = 400.000 Takte = 1 ms
	// Prescaler 8 => 400.000 / 8 = 50.000
	ICR1 = 50000;


	// printf("Hallo Michi %.02f", 123.45);


	while(1);

}