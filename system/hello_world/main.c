#include "uart.h"

int main(void)
{
    uart_init();
    printf("Hello RISC-V 32!\n");
    printf("Number %d = 0x%x\n", 1234, 1234);
    while (1);
}