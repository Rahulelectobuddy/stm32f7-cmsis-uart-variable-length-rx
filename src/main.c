/*
 * main.c
 *
 *  Created on: 13-Oct-2020
 *      Author: RahulGarg
 */

/*
 * Reference STM32 Nucleo-144 boards User Manual
 * Connector - C9
 *  +------------+-------------+-----------+
 *  | Pin Number | Signal name | STM32 Pin |
 *  |			4 		 | USART_B_RX  | 		 PD6	 |
 *  | 		6 		 | USART_B_RX	 | 		 PD5	 |
 *  +------------+-------------+-----------+
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

char * uart_rx_newline(){
	uint8_t var = 0;
	static char buff[MAX_UART_RX];
	USART_TypeDef *pUSART_Handle;
	pUSART_Handle = USART2;
	while(1) {
		while(!(pUSART_Handle->ISR & (USART_ISR_RXNE)));
		buff[var] = pUSART_Handle->RDR;
		if(buff[var] == '\n')
			break;
		var++;
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
		buff = uart_rx_newline();
		uart_tx(buff);
		for(itr1 = 0; itr1 < 1000; itr1++)
			for( itr2 = 0; itr2 < 1000; itr2++ );
	}
	return 0;
}
