#include "led.h"

void delay(volatile unsigned int d);
void led_flicker(void);

void delay(volatile unsigned int d)
{
	while (d--)
		;
}

void led_flicker(void)
{
	led_ctl(1);
	delay(1000000);
	led_ctl(0);
	delay(1000000);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	led_flicker();
	return 0;
}
