#ifndef __KEY_H
#define __KEY_H

#include "cc.h"

#define KEY_DOWN 1
#define KEY_UP 0

void key_init(void);
uint8_t key_read(void);

#endif
