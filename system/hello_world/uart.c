#include "uart.h"
#include <stdint.h>
#include <stdarg.h>

#define UART_BASE 0x10000000
static volatile uint32_t *uart = (uint32_t *)UART_BASE;

void uart_init(void) {}          // NS16550A 已由 QEMU 初始化

static void uart_putc(char c) 
{ 
    uart[0] = c; 
}

static void print_str(const char *s) 
{ 
    while (*s) uart_putc(*s++); 
}

static void print_num(unsigned long val, int base)
{
    const char *digits = "0123456789abcdef";
    char buf[32]; int i = 0;
    do { buf[i++] = digits[val % base]; val /= base; } while (val);
    while (i--) uart_putc(buf[i]);
}

void printf(const char *fmt, ...)
{
    va_list ap; va_start(ap, fmt);
    for (; *fmt; ++fmt) {
        if (*fmt != '%') { uart_putc(*fmt); continue; }
        switch (*++fmt) {
            case 'c': uart_putc(va_arg(ap, int)); break;
            case 's': print_str(va_arg(ap, char *)); break;
            case 'd': { long v = va_arg(ap, long);
                        if (v < 0) { uart_putc('-'); v = -v; }
                        print_num(v, 10); } break;
            case 'x': print_num(va_arg(ap, unsigned long), 16); break;
            default: break;
        }
    }
    va_end(ap);
}