/*
 * stm32f7xx_it.c
 *
 *  Created on: 15-Oct-2020
 *      Author: RahulGarg
 */

#include "stm32f746xx.h"

extern char global_buff[10];
extern char rx_buff[10];

void EXTI15_10_IRQHandler(void){

	EXTI_TypeDef *pEXTI = EXTI;
	pEXTI->PR |= EXTI_PR_PR13;

	gpio_toggle(GPIOB,7);

	return;
}

void USART2_IRQHandler(void){
	USART_TypeDef *pUSART_Handle;
	pUSART_Handle = USART2;
	uint8_t itr1=0;
	static uint8_t itr2=0;
	DMA_Stream_TypeDef *pDMA_Stream;
	pDMA_Stream = DMA1_Stream5;
//	itr2=itr1;
	if( pUSART_Handle->ISR & USART_ISR_IDLE){
		pUSART_Handle->ICR |= USART_ICR_IDLECF;
		while( itr2 != ( 10 - pDMA_Stream->NDTR ) ){
			rx_buff[itr1] = global_buff[itr2];
			itr2++;
			if(itr2 == 10)
				itr2=0;
			itr1++;
		}
		rx_buff[itr1] = '\0';
		uart_tx(rx_buff);
	}
	return;
}
