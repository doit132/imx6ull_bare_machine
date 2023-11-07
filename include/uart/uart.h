#ifndef __UART_H__
#define __UART_H__

#include "MCIMX6Y2.h"

void uart_init(void);
int getchar(void);
int putchar(char c);
#endif
