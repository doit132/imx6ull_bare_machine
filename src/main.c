#include "led.h"

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
	led_init();

	while (1) {
		led_ctl(1);
		delay(1000000);
		led_ctl(0);
		delay(1000000);
	}

	return 0;
}
