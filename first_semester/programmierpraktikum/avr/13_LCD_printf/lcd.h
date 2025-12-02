#ifndef _LCD_H_
#define _LCD_H_

#include <stdarg.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

void lcd_reset(void);
void lcd_init(void);
void lcd_clear_display(void);
void lcd_cursor_at_home(void);
void lcd_set_position(unsigned char, unsigned char);


#ifdef __cplusplus
}
#endif


#endif  // _PRINTF_H_
