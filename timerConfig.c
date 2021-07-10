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

	// Configure PIN-E6 for input capture mode
	// Mode Register set up for Alternate function for PIN-E6
	GPIOE->MODER &= ~GPIO_MODER_MODE6_0;
	GPIOE->MODER |=  GPIO_MODER_MODE6_1;
	// Pull up / Pull down register set up for neither pull up or pull down
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD6;
	// Speed setup for low speed
	GPIOE->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED6;
	// Set up alternate function for PIN-E6 (TIM15_CH2 : 0010)
	GPIOE->AFR[0] |= GPIO_AFRL_AFSEL6_2;
}

void timer_Config(){
//**********************************************************************************************/
	//INPUT CAPTURE MODE TIMER CONFIGUREATION FOR TIMER 3
	// Enable clock for timer3 peripheral which is on the APB1 bus
	RCC->APB1LENR |= RCC_APB1LENR_TIM3EN;
	RCC->APB2ENR  |= RCC_APB2ENR_TIM15EN;
// BOTH APB1 AND APB2 TIMER CLOCKS ARE RUNNING AT 200Mhz CHANGE PSC VALUE ACCORDING TO YOUR OWN CLOCK SETTINGS TO GET 1ms PER CYCLE

	// BASIC TIMER CONFIGURATION FOR TIMER 3
	// Set direction to upcounter
	TIM3->CR1 &= ~TIM_CR1_DIR;
	// Set the prescaler value (199 not 200 cauz reset of counter takes 1 clock cycle)
	TIM3->PSC = 199;
	// Set the value for the timer auto-reload register
	TIM3->ARR = 65535;
	// Set clock source to internal clock
	TIM3->SMCR &= ~TIM_SMCR_SMS;

	// BASIC TIMER CONFIGURATION FOR TIMER 15
	// Set direction to upcounter
	TIM15->CR1 &= ~TIM_CR1_DIR;
	// Set the prescaler value (15 not 16 cauz reset of counter takes 1 clock cycle)
	TIM15->PSC = 199;
	// Set the value for the timer auto-reload register
	TIM15->ARR = 65535;
	// Set clock source to internal clock
	TIM15->SMCR &= ~TIM_SMCR_SMS;

//------------------------------------------------------------------------------------------//
	// INPUT CAPTURE MODE CONFIGURATIONS FOR TIMER 15 CHANNEL  1
	// Note: CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).
	// Making sure bit is clear
	TIM3->CCER &= ~TIM_CCER_CC1E;
	// channel is configured as input, IC1 is mapped on TI1
	TIM3->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM3->CCMR1 |=  TIM_CCMR1_CC1S_0;

	// Program the needed input filter duration (8)
	TIM3->CCMR1 &= ~TIM_CCMR1_IC1F;
	TIM3->CCMR1 |= TIM_CCMR1_IC1F_0 | TIM_CCMR1_IC1F_1;

	// Select what triggers capture(rising edge)
	TIM3->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
	// Program the input prescaler
	TIM3->CCMR1 &= ~TIM_CCMR1_IC1PSC;
	// Enable capture from the counter into the capture register
	TIM3->CCER  |= TIM_CCER_CC1E;
	// Enable interrupt
	TIM3->DIER  |= TIM_DIER_CC1IE;

	NVIC_SetPriority(TIM3_IRQn, 0);
	NVIC_EnableIRQ(TIM3_IRQn);
	// Enable timer3
	TIM3->CR1 |= TIM_CR1_CEN;
//------------------------------------------------------------------------------------------//
	// INPUT CAPTURE MODE CONFIGURATIONS FOR TIMER 15 CHANNEL  2
	// Note: CC1S bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).
	// Making sure bit is clear
	TIM15->CCER &= ~TIM_CCER_CC2E;
	// channel is configured as input, IC2 is mapped on TI2
	TIM15->CCMR1 &= ~TIM_CCMR1_CC2S;
	TIM15->CCMR1 |=  TIM_CCMR1_CC2S_0;

	// Program the needed input filter duration (8)
	TIM15->CCMR1 &= ~TIM_CCMR1_IC2F;
	TIM15->CCMR1 |= TIM_CCMR1_IC2F_0 | TIM_CCMR1_IC2F_1;

	// Select what triggers capture(rising edge)
	TIM15->CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
	// Program the input prescaler
	TIM15->CCMR1 &= ~TIM_CCMR1_IC2PSC;
	// Enable capture from the counter into the capture register
	TIM15->CCER  |= TIM_CCER_CC2E;
	// Enable interrupt
	TIM15->DIER  |= TIM_DIER_CC2IE;

	NVIC_SetPriority(TIM15_IRQn, 1);
	NVIC_EnableIRQ(TIM15_IRQn);
	// Enable timer3
	TIM15->CR1 |= TIM_CR1_CEN;
}
// Timer3 interrupt handler
void TIM3_IRQHandler(void){
// Capture/compare 1 interrupt flag(The counter value has been captured in TIM3_CCR1 register)
	if ((TIM3->SR & TIM_SR_CC1IF)){
		// Check if pin A6 is high or low in order to know the start and end of the pulse
		if ((GPIOA->IDR & 0b01000000)){
			channel_1_start = (int32_t)TIM3->CCR1;
			TIM3->CCER  |= TIM_CCER_CC1P; // Change Trigger condition to falling edge
		}
		else{
			channel_1 = (int32_t)TIM3->CCR1 - (int32_t)channel_1_start;
			if( channel_1 < 0)channel_1 += 0xFFFF;
			TIM3->CCER &= ~TIM_CCER_CC1P; // Change Trigger condition to rising edge
		}
	}
}
void TIM15_IRQHandler(void){
// Capture/compare 1 interrupt flag(The counter value has been captured in TIM3_CCR1 register)
	if ((TIM15->SR & TIM_SR_CC1IF)){
		// Check if pin E6 is high or low in order to know the start and end of the pulse
		if ((GPIOE->IDR & 0b01000000)){
			channel_2_start = (int32_t)TIM15->CCR1;
			TIM15->CCER  |= TIM_CCER_CC1P; // Change Trigger condition to falling edge
		}
		else{
			channel_2 = (int32_t)TIM15->CCR1 - (int32_t)channel_2_start;
			if( channel_2 < 0)channel_2 += 0xFFFF;
			TIM15->CCER &= ~TIM_CCER_CC1P; // Change Trigger condition to rising edge
		}
	}
}
