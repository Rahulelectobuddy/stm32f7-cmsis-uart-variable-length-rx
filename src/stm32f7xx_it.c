/*
 * stm32f7xx_it.c
 *
 *  Created on: 15-Oct-2020
 *      Author: RahulGarg
 */

#include "stm32f746xx.h"

extern char global_buff[10];

void EXTI15_10_IRQHandler(void){

	EXTI_TypeDef *pEXTI = EXTI;
	pEXTI->PR |= EXTI_PR_PR13;

	gpio_toggle(GPIOB,7);

	return;
}

void USART2_IRQHandler(void){
	USART_TypeDef *pUSART_Handle;
	pUSART_Handle = USART2;
	if( pUSART_Handle->ISR & USART_ISR_IDLE){
		uart_tx(global_buff);
		pUSART_Handle->ICR |= USART_ICR_IDLECF;
	}
	return;
}
