#include <avr/io.h>
#include <printf.h>

// Taktrate Prozessor: 20 MHz => 1 Takt (1 cycle) dauert 50 ns



#define SET_RS 		(PORTB |= 1)
#define SET_RW		(PORTB |= 2)
#define SET_E		(PORTB |= 4)
#define CLEAR_E		(PORTB &= ~4)

#define SET_VDC_OFF	(PORTB |= 8);
#define SET_VDC_ON	(PORTB &= ~8);



void wait_ms(unsigned long ms)
{
	volatile unsigned long i, j;

	for(i = 0; i < ms; i++)
		for(j = 0; j < 554; j++);
}



void lcd_reset(void)
{
		DDRB = 0xFF;	// set Port Direction for VDC
		PORTB = 0;		// power off display controller

		SET_VDC_ON;		// power on display controller

		wait_ms(20);	// wait 20 ms

		SET_VDC_OFF;	// power off display controller;

		wait_ms(20);	// wait 20 ms

		SET_VDC_ON;		// power on display controller;

		wait_ms(20);
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
	PORTB = 0x08;

	// High-Pegel an RS ausgeben, falls rs == 1
	if(rs) SET_RS;

	// High-Pegel an RW ausgeben, falls rw == 1
	if(rw) SET_RW;

	// mind. 140 ns abwarten; 3 Zyklen zu je 50 ns => 150 ns
	asm volatile("nop\nnop\nnop\n");

	// Falls es sich um eine Lese-Operation handelt
	if(rw)	
	{
		// ***** Die oberen 4 Bits einlesen (bzw. 8-Bit-Operation) *****

		// PB7, PB6, PB5 und PB4 als Eingang konfigurieren
		// RS, RW, E und VDC bleiben als Ausgang konfiguriert
		DDRB &= 0x0F;

		// Steigende Flanke an E erzeugen
		SET_E;

		// mind. 320 ns abwarten, bis Daten verfügbar sind
		asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\n");

		// Datenbits einlesen und in oberen 4 Bits von read_data ablegen
		read_data = PINB & 0xF0;

		// Wartezyklen hinzufügen, High-Pegel von E mind. 450 ns
		asm volatile("nop\nnop\n");

		// E auf Low-Pegel legen
		CLEAR_E;

		// 500 ns warten, um mind. 1000 ns Zykluszeit von E zu erreichen
		asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

		// Im 8-Bit-Modus sind jetzt bereits alle Daten gelesen
		// Falls eight_bit_mode wahr ist, dann read_data zurückgeben
		if(eight_bit_mode) return read_data;


		// ****** Die unteren 4-Bits einlesen ******

		// E auf High-Pegel legen
		SET_E;

		// mind. 320 ns abwarten, bis Daten verfügbar sind
		asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\n");

		// Datenbits einlesen und an Position 3, 2, 1, 0 von 
		// read_data einfügen
		read_data |= (((PINB & 0xF0) >> 4) & 0x0F);

		// Wartezyklen hinzufügen; mind. 450 ns High-Pegel von E
		asm volatile("nop\nnop\n");

		// E auf Low-Pegel Legen
		CLEAR_E;

		// 500 ns warten, um mind. 1000 ns Zykluszeit von E zu erreichen
		asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

		// read_data zurückgeben
		return read_data;
	}

	// Falls es sich um einen Schreibzugriff auf das Display handelt
	else
	{
		// Alle Pins von Port B als Ausgang konfigurieren
		DDRB = 0xFF;
		// E auf High-Pegel legen
		SET_E;

		// Die oberen vier Bits von send_data über die oberen vier Bits
		// von PORTB an das Display ausgeben
		PORTB &= 0x0F;
		PORTB |= (send_data & 0xF0);

		// 500 ns warten
		asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
		
		// E auf Low-Pegel legen
		CLEAR_E;

		// nochmal 500 ns warten (Zykluszeit E mind. 1000 ns)
		asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

		// Im 8-Bit-Modus sind bereits alle Daten gesendet
		// Wenn eight_bit_mode == wahr, dann 0 zurückgeben
		if(eight_bit_mode) return 0;

		// ****** Die unteren 4 Bit senden *****

		// E auf High-Pegel legen
		SET_E;

		// Die unteren 4 Bit von send_data über die oberen
		// 4 Bit von PORTB ans Display ausgeben
		PORTB &= 0x0F;
		PORTB |= ((send_data << 4) & 0xF0);

		// 500 ns warten
		asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

		// An E Low-Pegel ausgeben
		CLEAR_E;

		// 500 ns warten um Zykluszeit von E (1000 ns) sicherzustellen
		asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

		// Funktion lcd durch Rückgabe des Wertes 0 beenden
		return 0;
	}
}




void lcd_init(void)
{
	// *** Hier noch im 8-Bit-Modus ***

	// Solange warten, wie Display beschäftigt ist (im 8-Bit-Modus)
	while(  lcd(0, 1, 0, 1) & 128  );

	// Display einstellen auf 4-Bit-Modus, 2 Zeilen, 5x7 und
	// solange warten, wie Display beschäftigt ist (im 8-Bit-Modus)
	lcd(0, 0, 0x28, 1);
	while(  lcd(0, 1, 0, 1) & 128  );

	
	// *** Ab hier ist Display im 4-Bit-Modus ***

	// Display einstellen auf 4-Bit-Modus, 2 Zeilen, 5x7, dann
	// Warten, solange Display beschäftigt ist (im 4 Bit Modus), dann
	lcd(0, 0, 0x28, 1);
	while( lcd(0, 1, 0, 0) & 128 );


	// Display anschalten, Cursor nicht anzeigen, Blinken aus
	// und warten, solange Display beschäftigt ist
	lcd(0, 0, 0x0C, 0);
	while( lcd(0, 1, 0, 0) & 128 );

	// Display löschen, Cursor an Position (1, 1) und
	// warten, solange Display beschäftigt ist
	lcd(0, 0, 0x01, 0);
	while( lcd(0, 1, 0, 0) & 128 );


	// Cursor auf "auto increment" einstellen und
	// warten, solange Display beschäftigt ist
	lcd(0, 0, 0x06, 0);
	while( lcd(0, 1, 0, 0) & 128 );

	// DD-RAM Adresse auf 0x00 setzen und
	// warten, solange Display beschäftigt ist
	lcd(0, 0, 0x80, 0);
	while( lcd(0, 1, 0, 0) & 128 );

}


void lcd_clear_display(void)
{
	while( lcd(0, 1, 0, 0) & 128 );
	lcd(0, 0, 0x01, 0);
}


void lcd_cursor_at_home(void)
{
	while( lcd(0, 1, 0, 0) & 128 );
	lcd(0, 0, 0x02, 0);

}

void lcd_set_position(unsigned char zeile, unsigned char spalte)
{
	// zeile = 0, 1
	// Spalte = 0, 1,  ... 15

	unsigned char address;

	if (zeile > 1 || spalte > 15) return;

	address = spalte | (zeile << 6);

	while( lcd(0, 1, 0, 0) & 128 );
	lcd(0, 0, 128 | address, 0);
}


void print_single_character(char c)
{
	while( lcd(0, 1, 0, 0) & 128 );
	lcd(1, 0, c, 0);
}

