#include "led.h"
#include "key.h"

void delay(volatile unsigned int d);
void key_led(void);

void delay(volatile unsigned int d)
{
	while (d--)
		;
}

void key_led(void)
{
	led_init();
	key_init();
	while (1) {
		if (key_read() == KEY_DOWN) {
			led_ctl(1);
			delay(1000000);
		} else {
			led_ctl(0);
			delay(1000000);
		}
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	key_led();
	return 0;
}
