/*
 * main.c
 *
 *  Created on: 13-Oct-2020
 *      Author: RahulGarg
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f746xx.h"

#define MAX_UART_RX (100)

void uart_tx(char *data){
	uint8_t var;
	USART_TypeDef *pUSART_Handle;
	pUSART_Handle = USART2;
	for (var = 0; var < strlen(data); ++var) {
		while(!(pUSART_Handle->ISR & (USART_ISR_TXE)));
		pUSART_Handle->TDR = data[var];
	}
	return;
}

char * uart_rx(uint8_t length){
	uint8_t var;
	static char buff[MAX_UART_RX];
	USART_TypeDef *pUSART_Handle;
	pUSART_Handle = USART2;
	for (int var = 0; var < length ; ++var) {
		while(!(pUSART_Handle->ISR & (USART_ISR_RXNE)));
		buff[var] = pUSART_Handle->RDR;
	}
	return buff;
}

int main()
{
	uint32_t itr1,itr2;
	init_gpio();
	init_uart();
	char *buff;
	while(1){
		if( gpio_read(GPIOC,13) ){
			gpio_toggle(GPIOB,0);
		}
		buff = uart_rx(11);
		uart_tx(buff);
		for(itr1 = 0; itr1 < 1000; itr1++)
			for( itr2 = 0; itr2 < 1000; itr2++ );
	}
	return 0;
}
