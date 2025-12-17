/*
 * AVR ATmega1284p Simulator - Runtime Implementation
 *
 * DO NOT include avr_sim.h here - it would rename our main() to avr_main()!
 * We declare everything we need directly.
 */

#define _POSIX_C_SOURCE 199309L
#define _DEFAULT_SOURCE

#include <ncurses.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/*============================================================================
 * Register Storage (defined here, declared extern in avr_sim.h)
 *============================================================================*/

volatile uint8_t DDRA = 0x00;
volatile uint8_t DDRB = 0x00;
volatile uint8_t DDRC = 0x00;
volatile uint8_t DDRD = 0x00;

volatile uint8_t PORTA = 0x00;
volatile uint8_t PORTB = 0x00;
volatile uint8_t PORTC = 0x00;
volatile uint8_t PORTD = 0x00;

volatile uint8_t PINA = 0x00;
volatile uint8_t PINB = 0x00;
volatile uint8_t PINC = 0x00;
volatile uint8_t PIND = 0xFF; /* Pull-ups: default high */

volatile uint8_t SREG = 0x00;

/*============================================================================
 * Simulator State
 *============================================================================*/

static volatile sig_atomic_t sim_running = 1;
static volatile sig_atomic_t button_pressed = 0;
static volatile uint64_t tick_count = 0;

/* Update rate: ~30 FPS */
#define UPDATE_INTERVAL_MS 33

/*============================================================================
 * Forward Declarations
 *============================================================================*/

static void update_pin_registers(void);
static void update_display(void);
static void cleanup(void);

/*============================================================================
 * Signal Handler for Periodic Updates
 *============================================================================*/

static void timer_handler(int signum) {
    (void)signum;

    /* Read input (non-blocking due to nodelay) */
    int ch = getch();
    while (ch != ERR) {
        switch (ch) {
            case 'q':
            case 'Q':
            case 27: /* ESC */
                sim_running = 0;
                cleanup();
                printf("\nSimulator exited after %llu frames.\n", (unsigned long long)tick_count);
                printf("Final register state:\n");
                printf("  DDRD=0x%02X  PORTD=0x%02X  PIND=0x%02X\n", DDRD, PORTD, PIND);
                exit(0);
                break;
            case 'b':
            case 'B':
            case ' ':
                button_pressed = !button_pressed;
                break;
        }
        ch = getch();
    }

    /* Update PIN registers based on button state */
    update_pin_registers();

    /* Update display */
    update_display();

    tick_count++;
}

/*============================================================================
 * ncurses UI
 *============================================================================*/

static void draw_header(void) {
    attron(A_BOLD);
    mvprintw(0, 0, "+========================================================================+");
    mvprintw(1, 0, "|          ATmega1284p Simulator  -  TUM Programmierpraktikum           |");
    mvprintw(2, 0, "+========================================================================+");
    attroff(A_BOLD);
}

static void draw_chip(void) {
    int y = 4;
    int x = 2;

    mvprintw(y, x, "        +----------------+");
    mvprintw(y + 1, x, "   PB0 -| 1           40 |- PA0");
    mvprintw(y + 2, x, "   PB1 -| 2           39 |- PA1");
    mvprintw(y + 3, x, "   PB2 -| 3           38 |- PA2");
    mvprintw(y + 4, x, "   PB3 -| 4           37 |- PA3");
    mvprintw(y + 5, x, "   PB4 -| 5           36 |- PA4");
    mvprintw(y + 6, x, "   PB5 -| 6           35 |- PA5");
    mvprintw(y + 7, x, "   PB6 -| 7           34 |- PA6");
    mvprintw(y + 8, x, "   PB7 -| 8           33 |- PA7");
    mvprintw(y + 9, x, " RESET -| 9           32 |- AREF");
    mvprintw(y + 10, x, "   VCC -|10           31 |- GND");
    mvprintw(y + 11, x, "   GND -|11           30 |- AVCC");
    mvprintw(y + 12, x, " XTAL1 -|12           29 |- PC7");
    mvprintw(y + 13, x, " XTAL2 -|13           28 |- PC6");
    mvprintw(y + 14, x, "   PD0 -|14  LED      27 |- PC5");
    mvprintw(y + 15, x, "   PD1 -|15           26 |- PC4");
    mvprintw(y + 16, x, "   PD2 -|16           25 |- PC3");
    mvprintw(y + 17, x, "   PD3 -|17  BTN      24 |- PC2");
    mvprintw(y + 18, x, "   PD4 -|18           23 |- PC1");
    mvprintw(y + 19, x, "   PD5 -|19           22 |- PC0");
    mvprintw(y + 20, x, "   PD6 -|20           21 |- PD7");
    mvprintw(y + 21, x, "        +----------------+");
}

static void draw_led(void) {
    int y = 5;
    int x = 42;

    /* LED connected to PD0: on when DDR=1 (output) and PORT=1 (high) */
    int led_on = (DDRD & 0x01) && (PORTD & 0x01);

    mvprintw(y, x, "+-------------------+");
    mvprintw(y + 1, x, "|    LED  (PD0)     |");
    mvprintw(y + 2, x, "|                   |");

    if (led_on) {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(y + 3, x, "|     ########      |");
        mvprintw(y + 4, x, "|     ########      |");
        mvprintw(y + 5, x, "|       ON          |");
        attroff(COLOR_PAIR(1) | A_BOLD);
    } else {
        attron(A_DIM);
        mvprintw(y + 3, x, "|     ........      |");
        mvprintw(y + 4, x, "|     ........      |");
        mvprintw(y + 5, x, "|       OFF         |");
        attroff(A_DIM);
    }

    mvprintw(y + 6, x, "|                   |");
    mvprintw(y + 7, x, "+-------------------+");
}

static void draw_button(void) {
    int y = 14;
    int x = 42;

    mvprintw(y, x, "+-------------------+");
    mvprintw(y + 1, x, "|  BUTTON  (PD3)    |");
    mvprintw(y + 2, x, "|                   |");

    if (button_pressed) {
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(y + 3, x, "|    [PRESSED]      |");
        attroff(COLOR_PAIR(3) | A_BOLD);
    } else {
        mvprintw(y + 3, x, "|    [        ]     |");
    }

    mvprintw(y + 4, x, "|                   |");
    mvprintw(y + 5, x, "|  Press 'b'/SPACE  |");
    mvprintw(y + 6, x, "+-------------------+");
}

static void draw_registers(void) {
    int y = 4;
    int x = 64;

    attron(A_BOLD | A_UNDERLINE);
    mvprintw(y, x, "  REGISTERS  ");
    attroff(A_BOLD | A_UNDERLINE);

    y += 2;

    /* PORTD - most important for exercises */
    attron(COLOR_PAIR(4));
    mvprintw(y, x, "DDRD:  0x%02X", DDRD);
    mvprintw(y + 1, x, "PORTD: 0x%02X", PORTD);
    mvprintw(y + 2, x, "PIND:  0x%02X", PIND);
    attroff(COLOR_PAIR(4));

    y += 4;
    mvprintw(y, x, "DDRA:  0x%02X", DDRA);
    mvprintw(y + 1, x, "PORTA: 0x%02X", PORTA);

    y += 3;
    mvprintw(y, x, "DDRB:  0x%02X", DDRB);
    mvprintw(y + 1, x, "PORTB: 0x%02X", PORTB);

    y += 3;
    mvprintw(y, x, "DDRC:  0x%02X", DDRC);
    mvprintw(y + 1, x, "PORTC: 0x%02X", PORTC);

    /* Binary display for PORTD */
    y = 22;
    x = 42;
    mvprintw(y, x, "DDRD:  7 6 5 4 3 2 1 0");
    mvprintw(y + 1, x, "       %d %d %d %d %d %d %d %d", (DDRD >> 7) & 1, (DDRD >> 6) & 1,
             (DDRD >> 5) & 1, (DDRD >> 4) & 1, (DDRD >> 3) & 1, (DDRD >> 2) & 1,
             (DDRD >> 1) & 1, (DDRD >> 0) & 1);

    mvprintw(y + 2, x, "PORTD: 7 6 5 4 3 2 1 0");
    mvprintw(y + 3, x, "       %d %d %d %d %d %d %d %d", (PORTD >> 7) & 1, (PORTD >> 6) & 1,
             (PORTD >> 5) & 1, (PORTD >> 4) & 1, (PORTD >> 3) & 1, (PORTD >> 2) & 1,
             (PORTD >> 1) & 1, (PORTD >> 0) & 1);

    mvprintw(y + 4, x, "PIND:  7 6 5 4 3 2 1 0");
    mvprintw(y + 5, x, "       %d %d %d %d %d %d %d %d", (PIND >> 7) & 1, (PIND >> 6) & 1,
             (PIND >> 5) & 1, (PIND >> 4) & 1, (PIND >> 3) & 1, (PIND >> 2) & 1, (PIND >> 1) & 1,
             (PIND >> 0) & 1);
}

static void draw_help(void) {
    int y = 29;

    attron(A_DIM);
    mvprintw(y, 0, "------------------------------------------------------------------------");
    mvprintw(y + 1, 0, " Controls: [b]/[SPACE] Toggle button  |  [q]/[ESC] Quit");
    mvprintw(y + 2, 0, " Frame: %llu", (unsigned long long)tick_count);
    attroff(A_DIM);
}

static void update_display(void) {
    erase();
    draw_header();
    draw_chip();
    draw_led();
    draw_button();
    draw_registers();
    draw_help();
    refresh();
}

/*============================================================================
 * PIN Register Simulation
 *============================================================================*/

static void update_pin_registers(void) {
    /*
     * PIND reflects:
     * - For outputs (DDR bit = 1): the value being driven (PORT bit)
     * - For inputs (DDR bit = 0): external state or pull-up
     *
     * PD3 is our button input:
     * - Button pressed = LOW (0)
     * - Button released = HIGH (1) due to pull-up
     */

    uint8_t pind_value = 0xFF; /* Default: all high (pull-ups) */

    for (int i = 0; i < 8; i++) {
        if (DDRD & (1 << i)) {
            /* Output pin: reflects PORTD value */
            if (PORTD & (1 << i)) {
                pind_value |= (1 << i);
            } else {
                pind_value &= ~(1 << i);
            }
        } else {
            /* Input pin: external state or pull-up */
            if (i == 3) {
                /* Button on PD3: active low */
                if (button_pressed) {
                    pind_value &= ~(1 << 3); /* Button pressed = LOW */
                } else {
                    pind_value |= (1 << 3); /* Button released = HIGH */
                }
            }
            /* Other input pins stay high (pull-up) */
        }
    }

    PIND = pind_value;

    /* Other ports: just reflect output values for now */
    PINA = PORTA;
    PINB = PORTB;
    PINC = PORTC;
}

/*============================================================================
 * Timer Setup
 *============================================================================*/

static void setup_timer(void) {
    struct sigaction sa;
    struct itimerval timer;

    /* Set up signal handler */
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = timer_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);

    /* Configure timer for periodic updates */
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = UPDATE_INTERVAL_MS * 1000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = UPDATE_INTERVAL_MS * 1000;

    setitimer(ITIMER_REAL, &timer, NULL);
}

static void cleanup(void) {
    /* Disable timer */
    struct itimerval timer = {{0, 0}, {0, 0}};
    setitimer(ITIMER_REAL, &timer, NULL);

    /* Cleanup ncurses */
    endwin();
}

/*============================================================================
 * Main Entry Point
 *============================================================================*/

/* User's main function - renamed to avr_main by the macro in avr_sim.h */
extern int avr_main(void);

int main(void) {
    /* Initialize ncurses */
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    /* Initialize colors */
    if (has_colors()) {
        start_color();
        use_default_colors();
        init_pair(1, COLOR_GREEN, -1);  /* LED on */
        init_pair(2, COLOR_WHITE, -1);  /* Normal */
        init_pair(3, COLOR_YELLOW, -1); /* Button pressed */
        init_pair(4, COLOR_CYAN, -1);   /* Highlighted registers */
    }

    /* Set up periodic timer for display updates */
    setup_timer();

    /* Initial display */
    update_display();

    /* Run user's AVR code (this may block in while(1) loops) */
    avr_main();

    /* If user's main returns, wait for quit */
    while (sim_running) {
        pause();
    }

    /* Cleanup */
    cleanup();

    printf("\nSimulator exited after %llu frames.\n", (unsigned long long)tick_count);
    printf("Final register state:\n");
    printf("  DDRD=0x%02X  PORTD=0x%02X  PIND=0x%02X\n", DDRD, PORTD, PIND);

    return 0;
}
