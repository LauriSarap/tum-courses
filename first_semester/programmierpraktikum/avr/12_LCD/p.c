#include <avr/io.h>
// #include <printf.h>

// Taktrate Prozessor: 20 MHz => 1 Takt (1 cycle) dauert 50 ns

#define TOGGLE_LED (PORTD ^= 1)











void wait_ms(unsigned long ms)
{





}


void lcd_reset(void)
{















}



// rs: 1 if data, 0 if instruction 
// rw: 1 if read operation, 0 if write operation
// send_data: the data to be sent
// return value: the value read from the display
unsigned char lcd(unsigned char rs, unsigned char rw, unsigned char send_data, unsigned char eight_bit_mode)
{
	unsigned char read_data = 0;

	// Bis auf PB3 (VDC) alle Bits von PORTB auf 0 setzen
	// danach können entsprechende Bits mit ODER-Operationen gesetzt werden


	// High-Pegel an RS ausgeben, falls rs == 1


	// High-Pegel an RW ausgeben, falls rw == 1


	// mind. 140 ns abwarten; 3 Zyklen zu je 50 ns => 150 ns


	// Falls es sich um eine Lese-Operation handelt
	if(rw)	
	{
		// ***** Die oberen 4 Bits einlesen (bzw. 8-Bit-Operation) *****

		// PB7, PB6, PB5 und PB4 als Eingang konfigurieren
		// RS, RW, E und VDC bleiben als Ausgang konfiguriert


		// Steigende Flanke an E erzeugen


		// mind. 320 ns abwarten, bis Daten verfügbar sind


		// Datenbits einlesen und in oberen 4 Bits von read_data ablegen


		// Wartezyklen hinzufügen, High-Pegel von E mind. 450 ns


		// E auf Low-Pegel legen


		// 500 ns warten, um mind. 1000 ns Zykluszeit von E zu erreichen


		// Im 8-Bit-Modus sind jetzt bereits alle Daten gelesen
		// Falls eight_bit_mode wahr ist, dann read_data zurückgeben



		// ****** Die unteren 4-Bits einlesen ******

		// E auf High-Pegel legen


		// mind. 320 ns abwarten, bis Daten verfügbar sind


		// Datenbits einlesen und an Position 3, 2, 1, 0 von 
		// read_data einfügen


		// Wartezyklen hinzufügen; mind. 450 ns High-Pegel von E


		// E auf Low-Pegel Legen


		// 500 ns warten, um mind. 1000 ns Zykluszeit von E zu erreichen


		// read_data zurückgeben

	}

	// Falls es sich um einen Schreibzugriff auf das Display handelt
	else
	{
		// Alle Pins von Port B als Ausgang konfigurieren

		// E auf High-Pegel legen


		// Die oberen vier Bits von send_data über die oberen vier Bits
		// von PORTB an das Display ausgeben



		// 500 ns warten

		
		// E auf Low-Pegel legen


		// nochmal 500 ns warten (Zykluszeit E mind. 1000 ns)


		// Im 8-Bit-Modus sind bereits alle Daten gesendet
		// Wenn eight_bit_mode == wahr, dann 0 zurückgeben


		// ****** Die unteren 4 Bit senden *****

		// E auf High-Pegel legen


		// Die unteren 4 Bit von send_data über die oberen
		// 4 Bit von PORTB ans Display ausgeben



		// 500 ns warten


		// An E Low-Pegel ausgeben


		// 500 ns warten um Zykluszeit von E (1000 ns) sicherzustellen


		// Funktion lcd durch Rückgabe des Wertes 0 beenden

	}
}



void lcd_init(void)
{
	// *** Hier noch im 8-Bit-Modus ***

	// Solange warten (= busy-Flag auslesen), wie Display 
	// beschäftigt ist (8-Bit-Modus)


	// Display einstellen auf 4-Bit-Modus, 2 Zeilen, 5x7 und
	// solange warten, wie Display beschäftigt ist (8-Bit-Modus)


	
	// *** Ab hier ist Display im 4-Bit-Modus ***

	// Display einstellen auf 4-Bit-Modus, 2 Zeilen, 5x7, dann
	// Warten, solange Display beschäftigt ist (im 4 Bit Modus)



	// Display anschalten, Cursor nicht anzeigen, Blinken aus
	// und warten, solange Display beschäftigt ist



	// Display löschen, Cursor an Position (0, 0) und
	// warten, solange Display beschäftigt ist



	// Cursor auf "auto increment" einstellen und
	// warten, solange Display beschäftigt ist



	// DD-RAM Adresse auf 0x00 setzen und
	// warten, solange Display beschäftigt ist


}

void lcd_clear_display(void)
{
	// Solange warten, bis Busy-Flag 0 ist


	// Befehl zum Löschen des Displays abschicken

}

// void lcd_cursor_at_home(void)
// {
// 	while( lcd(0, 1, 0, 0) & 128 );
// 	lcd(0, 0, 0x02, 0);

// }

void lcd_set_position(unsigned char zeile, unsigned char spalte)
{
	// zeile = 0, 1
	// Spalte = 0, 1,  ... 15



	// Abbrechen, falls ungültige Zeile oder Spalte angegeben wurde


	// DD-RAM-Adresse bestimmen


	// Warten, bis Busy-Flag nicht mehr gesetzt ist


	// Befehl an das Display schicken


}


void print_single_character(char c)
{



}


void print_string(char* s)
{
	unsigned int i = 0;

	for(i = 0; s[i]; i++) print_single_character(s[i]);
}


void print_integer(long long zahl)
{



















}

void print_float32(float zahl)
{
	signed char sign, exp, d, rounds;
	unsigned char e;
	unsigned long f, m, vorkomma;
	unsigned long long nachkomma;
	unsigned long bits;

	// Compiler-Warnung "-Wstrict-aliasing" temporär ausschalten
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"

	bits = (*((unsigned long*)(&zahl)));

	// Compiler-Warnung wieder einschalten
	#pragma GCC diagnostic warning "-Wstrict-aliasing"


	// Bits: s = 31; e = 30..23; f = 22..0
	sign = bits >> 31;					// Bit 31 ist Vorzeichen
	e = ((bits << 1) >> 24);			// Bits 30..23 nach 7..0 schieben
	exp = e - 127;						// Exponent: exp = e - K (127)
	f = bits & 0x7FFFFF;				// f (fraction) aus 1.f
	m = f | 0x800000;					// Mantisse = 1.f


	// *** Spezialfälle ***
	// Null
	if(bits == 0x00000000 || bits == 0x80000000)
	{
		print_string("0,000000");
		return;
	}
	// Unendlich
	else if(e == 255 && f == 0)
	{
		if(sign) print_single_character('-');
		else print_single_character('+');
		print_string("inf");
		return;
	}
	// Not a number
	else if(e == 255 && f != 0)
	{
		print_string("NaN");
		return;
	}
	// Denormalisierte Zahlen werden nicht unterstützt,
	// da so viele Nuller auf dem Display nicht darstellbar sind
	else if(e == 0 && f != 0)
	{
		print_string("Denorm. not supp");
		return;
	}

	// *** Normalisierte Gleitkommazahl ***

	// Zahl nach links (Komma nach rechts) schieben oder nicht schieben
	if(exp >= 0)
	{
		// Vorkomma-Bits 23...(23-exp) extrahieren
		vorkomma = m >> (23 - exp);

		// Nachkomma-Bits (22-exp)...0 extrahieren
		nachkomma = ( m << (31 - (22 - exp)) ) >> (31 - (22 - exp));

		// '-', Vorkomma-Stellen und ',' ausgeben
		if(sign) print_single_character('-');
		print_integer(vorkomma);
		print_single_character(',');

		// Nachkommastellen ausgeben
		// Bits pro Dezimalstelle: log_10(10) / log_10(2) = 3,3219
		rounds = ((23 - exp) / 3.32) + 0.5;
		for( ; rounds > 0; rounds--)
		{
			nachkomma *= 10;
			d = (nachkomma >> (23-exp)) % 10;	// auszugebende Ziffer
			print_single_character(d + '0');	// als Zeichen ausgeben
		}
	}

	// Zahl nach rechts (Komma nach links) schieben
	else
	{
		if(sign) print_single_character('-');
		print_single_character('0');
		print_single_character(',');

		nachkomma = m;

		rounds = ((23 - exp) / 3.32) + 0.5;
		for( ; rounds > 0; rounds--)
		{
			nachkomma *= 10;
			d = (nachkomma >> (23-exp)) % 10;
			print_single_character(d + '0');
		}
	}
}

int main(void)
{
	DDRD = 1;	// Data Direction LED
	PORTD = 0;	// LED off


	// while(1)
	// {
	// 	TOGGLE_LED;
	// 	wait_ms(1000);	// Werte: 1000, 100, 10, 1
	// }

	lcd_reset();
	lcd_init();


	// unsigned long v = 0x7F800000;	// +inf
	// unsigned long v = 0xFF800000;	// -inf
	// unsigned long v = 0x00000001;		// NaN
	// print_float32((*((float*)((unsigned long*) &v))));


	// AUFGABE:
	// Zahl -1132.23845 mit selbstgebauter Funktion print_float32 und 
	// mit printf  ausgeben; man sieht: printf gibt noch Stellen aus,
	// die gar keine gültige Wertigkeit mehr haben.
	print_float32(-1132.23845);	// -1132,2384
	// printf("%f", -1132.23845);	// -1132.238403


	while(1);

}