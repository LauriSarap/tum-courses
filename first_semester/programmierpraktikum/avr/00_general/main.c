/*
 * AVR Simulator Test File
 * 
 * This file tests all functionality needed for exercises 1-4.
 * Uncomment the test you want to run!
 */

#include <avr/io.h>

/* ============================================================================
 * TEST 1: LED ON (Exercise 01)
 * 
 * Expected: LED should be ON (green), DDRD=0x01, PORTD=0x01
 * This is exactly what the guide shows for exercise 01.
 * ============================================================================
 */
#define TEST_LED_ON

/* ============================================================================
 * TEST 2: LED OFF
 * 
 * Expected: LED should be OFF, DDRD=0x01, PORTD=0x00
 * ============================================================================
 */
// #define TEST_LED_OFF

/* ============================================================================
 * TEST 3: LED Blinking (Exercise 03)
 * 
 * Expected: LED blinks on/off. Watch the PORTD value toggle between 0x00/0x01
 * Uses volatile delay loop as shown in the guide.
 * ============================================================================
 */
// #define TEST_LED_BLINK

/* ============================================================================
 * TEST 4: Button Polling (Exercise 04)
 * 
 * Expected: LED starts ON. Press 'b' or SPACE to toggle LED.
 * Each button press toggles the LED state.
 * ============================================================================
 */
// #define TEST_BUTTON_POLLING

/* ============================================================================
 * TEST 5: Data Types (Exercise 02)
 * 
 * Expected: LED ON if sizeof(int) == 2 (16-bit, true on AVR, but 4 on PC!)
 * Note: On PC, int is 32-bit, so this will show LED OFF.
 * ============================================================================
 */
// #define TEST_DATATYPES


/* ========================================================================== */
/*                              TEST IMPLEMENTATIONS                          */
/* ========================================================================== */

#ifdef TEST_LED_ON
int main(void)
{
    // Configure PD0 as output
    DDRD = 1;   // 0b00000001: bit 0 = 1 means output
    
    // Set PD0 to HIGH -> LED ON
    PORTD = 1;  // 0b00000001: bit 0 = 1 means high voltage
    
    // Infinite loop (required to keep the program running)
    while(1);
}
#endif


#ifdef TEST_LED_OFF
int main(void)
{
    DDRD = 1;   // PD0 as output
    PORTD = 0;  // PD0 LOW -> LED OFF
    
    while(1);
}
#endif


#ifdef TEST_LED_BLINK
#define MAX 5000  // Reduced for faster simulation (original: 32000)

int main(void)
{
    DDRD = 1;   // PD0 as output
    PORTD = 0;  // Start with LED OFF
    
    // volatile prevents compiler from optimizing away the delay loop!
    volatile unsigned int i;
    
    while(1)
    {
        // Delay loop
        for(i = 0; i < MAX; i++);
        
        // Toggle LED: XOR flips bit 0
        // If PORTD was 0, becomes 1 (LED ON)
        // If PORTD was 1, becomes 0 (LED OFF)
        PORTD ^= 1;
    }
}
#endif


#ifdef TEST_BUTTON_POLLING
// Macros exactly as shown in the guide
#define KEY_PRESSED ((PIND & 8) == 0)   // PD3 is bit 3 (value 8), active LOW
#define SET_LED_ON  (PORTD |= 1)
#define SET_LED_OFF (PORTD &= ~1)
#define TOGGLE_LED  (PORTD ^= 1)

int main(void)
{
    volatile unsigned char key_pressed_before = 0;
    
    DDRD = 1;   // PD0 as output (LED), PD3 stays input (button)
    SET_LED_ON; // Start with LED on
    
    while(1)
    {
        // Detect button press (falling edge)
        if (KEY_PRESSED && !key_pressed_before)
        {
            TOGGLE_LED;
            key_pressed_before = 1;
        }
        
        // Detect button release
        if (!KEY_PRESSED)
            key_pressed_before = 0;
    }
}
#endif


#ifdef TEST_DATATYPES
int main(void)
{
    DDRD = 1;  // PD0 as output
    
    // On real AVR: int is 16-bit (2 bytes) -> LED ON
    // On PC simulator: int is 32-bit (4 bytes) -> LED OFF
    // This demonstrates a difference between AVR and PC!
    if (sizeof(int) == 2)
        PORTD = 1;  // LED ON
    else
        PORTD = 0;  // LED OFF
    
    while(1);
}
#endif
