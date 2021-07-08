/*
 * timerConfig.c
 *
 *  Created on: Jul 7, 2021
 *      Author: Yetu
 */

#include "timerConfig.h"

void timerGpio_Config(){
	// SET UP PINS FOR INPUT CAPTURE MODE
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;	// Enable peripheral clock for GPIOA

	// Configure PIN-A6 for input capture mode
	// Mode Register set up for Alternate function for PIN-A6
	GPIOA->MODER &= ~GPIO_MODER_MODE6_0;
	GPIOA->MODER |=  GPIO_MODER_MODE6_1;
	// Pull up / Pull down register set up for neither pull up or pull down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD6;
	// Speed setup for low speed
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED6;
	// Set up alternate function for PIN-A6 (TIM3_CH1 : 0010)
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL6_1;

	// Configure PIN-A8 for input capture mode
	// Mode Register set up for Alternate function for PIN-A8
	GPIOA->MODER &= ~GPIO_MODER_MODE8_0;
	GPIOA->MODER |=  GPIO_MODER_MODE8_1;
	// Pull up / Pull down register set up for neither pull up or pull down
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD8;
	// Speed setup for low speed
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED8;
	// Set up alternate function for PIN-A8 (TIM1_CH1 : 0010)
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL8_0;
}

void timer_Config(){
//**********************************************************************************************/
	//INPUT CAPTURE MODE TIMER CONFIGUREATION FOR TIMER 2
	// Enable clock for timer2 peripheral which is on the APB1 bus
	RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
	
	// BASIC TIMER CONFIGUR
	// Set direction to upcounter
	TIM3->CR1 &= ~TIM_CR1_DIR;
	// Set the prescaler value (15 not 16 cauz reset of counter takes 1 clock cycle)
	TIM3->PSC = 200;
	// Set the value for the timer auto-reload register
	TIM3->ARR = 65535;
	// Set clock source to internal clock
	TIM3->SMCR &= ~TIM_SMCR_SMS;
	
//------------------------------------------------------------------------------------------//
	// INPUT CAPTURE MODE CONFIGURATIONS FOR TIMER 2 CHANNEL  1
	// Note: CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).
	// Making sure bit is clear
	TIM2->CCER &= ~TIM_CCER_CC1E;
	// channel is configured as input, IC1 is mapped on TI1
	TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM2->CCMR1 |=  TIM_CCMR1_CC1S_0;
	
	// Program the needed input filter duration (8)
	TIM2->CCMR1 &= ~TIM_CCMR1_IC1F;
	TIM2->CCMR1 |= TIM_CCMR1_IC1F_0 | TIM_CCMR1_IC1F_1;
	
	// Select what triggers capture(rising edge)
	TIM2->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
	// Program the input prescaler
	TIM2->CCMR1 &= ~TIM_CCMR1_IC1PSC;
	// Enable capture from the counter into the capture register
	TIM2->CCER  |= TIM_CCER_CC1E;
	// Enable interrupt 
	TIM2->DIER  |= TIM_DIER_CC1IE;
}
