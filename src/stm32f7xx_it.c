/*
 * stm32f7xx_it.c
 *
 *  Created on: 15-Oct-2020
 *      Author: RahulGarg
 */

#include "stm32f746xx.h"

void EXTI15_10_IRQHandler(void){

	EXTI_TypeDef *pEXTI = EXTI;
	pEXTI->PR |= EXTI_PR_PR13;

	gpio_toggle(GPIOB,7);

	return;
}
