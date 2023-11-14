#include "delay.h"

void delay(volatile unsigned int d)
{
	while (d--)
		;
}
