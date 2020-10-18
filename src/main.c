/*
 * main.c
 *
 *  Created on: 13-Oct-2020
 *      Author: RahulGarg
 */

#include <stdint.h>
#include "stm32f746xx.h"

void uart_tx(){
	uint8_t var;
	USART_TypeDef *pUSART_Handle;
	pUSART_Handle = USART2;
	char data[12]="hello world\n";
	for (var = 0; var < 12; ++var) {
		while(!(pUSART_Handle->ISR & (USART_ISR_TXE)));
		pUSART_Handle->TDR = data[var];
	}
	return;
}

int main()
{
	uint32_t itr1,itr2;
	init_gpio();
	init_uart();
	while(1){
		if( gpio_read(GPIOC,13) ){
			gpio_toggle(GPIOB,0);
			uart_tx();
		}
		for(itr1 = 0; itr1 < 1000; itr1++)
			for( itr2 = 0; itr2 < 1000; itr2++ );
	}
	return 0;
}
