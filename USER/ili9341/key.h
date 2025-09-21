
#ifndef __key_H
#define __key_H

#include "main.h"
#include "stdbool.h"

extern uint8_t Trg;	 	 // 全局变量，单次触发
extern uint8_t Cont; 	 // 全局变量，长按

void Key_Read(void);

#endif
