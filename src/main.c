#include "uart.h"

void delay(volatile unsigned int d);

void delay(volatile unsigned int d)
{
	while (d--)
		;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
        
	char c;
	uart_init();
	putchar('1');
	putchar('0');
	putchar('0');
	putchar('a');
	putchar('s');
	putchar('k');
	putchar('\r');
	putchar('\n');

	while (1) {
		c = getchar();
		putchar(c);
		putchar(c + 1);
	}

	return 0;
}
