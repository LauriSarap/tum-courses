#include <avr/io.h>
#include <avr/interrupt.h>


#define TOGGLE_LED (PORTD ^= 1)


// Variable tcnt0_reset_value wird bei jedem Timer0-Überlauf als neuer
// Timer-Start-Wert in das TCNT-Register geladen. Hier tcnt0_reset_value
// deklarieren und so initialisieren, dass T0 jede 1/100 s überläuft.




// Variable t0_overflows legt die Anzahl der Überläufe fest, welche die LED
// an bzw. aus ist; Wertebereich: 1, 2, ... 100; hier t0_overflows dekla-
// rieren und so initialisieren, dass die LED initial mit 5 Hz blinkt.





// Variable t0_overflow_count wird zum Zählen der Timer0-Überläufe seit
// der letzten LED-Zustandsänderung verwendet; Wertebereich: 1, 2, ... 100;
// Deklarieren Sie die Variable und initalisieren Sie sie mit demselben
// Wert wie t0_overflows 



ISR(INT0_vect)
{
	// Linksdrehung










	// Rechtsdrehung









}


ISR(TIMER0_OVF_vect)
{
	// Timer-Wert wiederherstellen



	// t0_overflow_count um 1 verringern



	// wenn Zähler t0_overflow_count bei 0 angekommen ist,
	// t0_overflow_count zurücksetzen und Zustand LED ändern





}



int main(void)
{

	// Bit 0 von PORTD als Ausgang festlegen


	// Interrupts global freischalten


	// INT0 Interrupt freischalten


	// Für INT0 steigende Flanke als Auslöser auswählen


	// Interrupt für Timer0 freischalten


	// Prescaler 1024 für Timer0 auswählen


	// TCNT0 mit tcnt0_reset_value initialisieren


	//Endlos-Schleife

}
