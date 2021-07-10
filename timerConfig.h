/*
 * timerConfig.h
 *
 *  Created on: Jul 7, 2021
 *      Author: Yetu
 */

#include <stm32h745xx.h>

#ifndef INC_TIMERCONFIG_H_
#define INC_TIMERCONFIG_H_



#endif /* INC_TIMERCONFIG_H_ */

// variables for receiver input
int32_t channel_1_start, channel_1;
int32_t channel_2_start, channel_2;
int32_t channel_3_start, channel_3;
int32_t channel_4_start, channel_4;

void timerGpio_Config(void);

void timer_Config(void);
