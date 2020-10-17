/*
 * stm32f7xx_gpio.c
 *
 *  Created on: 13-Oct-2020
 *      Author: RahulGarg
 */

#include <stdbool.h>
#include "stm32f746xx.h"

/*
 * @brief :
 *
 * @note :
 *
 * 	How to use this driver :
 *		1. Enable the GPIO AHB clock.
 *		2. Configure the GPIO pin(s).
 *			- Configure the IO mode using MODER member from GPIO_TypeDef structure
 *			- Activate Pull-up, Pull-down resistor using OTYPER and PUPDR member from GPIO_TypeDef
 *			structure.
 *			- In case of Output or alternate function mode selection: the speed is configured through
 *			OSPEEDR member from GPIO_TypeDef structure.
 *			- In alternate mode is selection, the alternate function connected to the IO is configured
 *			through AFR member from GPIO_TypeDef structure.
 *			- Analog mode is required when a pin is to be used as ADC channel or DAC output.
 *			- In case of external interrupt/event selection the EXTI_TypeDef structure select the
 *			type (interrupt or event) and the corresponding trigger event (rising or falling orboth).
 *		3. In case of external interrupt/event mode selection, configure NVIC IRQ priority mapped
 *		to the EXTI line using NVIC_SetPriority() and enable it using NVIC_EnableIRQ().
 *		4. To get the level of a pin configured in input mode use GPIOx_IDR Register.
 *		5. To set/reset the level of a pin configured in output mode use GPIOx_BSRR and GPIOx_ODR.
 *		6. To lock pin configuration until next reset use GPIOx_LCKR.
 *		7. During and just after reset, the alternate functions are not active and the GPIO pins
 *		are configured in input floating mode (except JTAG pins).
 *		8. The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as general purpose (PC14 and
 *		PC15, respectively) when the LSE oscillator is off. The LSE has priority over the GPIO
 *		function.
 *		9. The HSE oscillator pins OSC_IN/OSC_OUT can be used as general purpose PH0 and PH1,
 *		respectively, when the HSE oscillator is off. The HSE has priority over the GPIO function.
 *
 */
void init_gpio(void)
{
	RCC_TypeDef *pRCC_Handle = RCC;
	pRCC_Handle->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	pRCC_Handle->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	pRCC_Handle->APB2ENR |= RCC_APB2LPENR_SYSCFGLPEN;

	GPIO_TypeDef *pGPIO_Handle = GPIOB;
	pGPIO_Handle->MODER = GPIO_MODER_MODER0_0|GPIO_MODER_MODER7_0|GPIO_MODER_MODER14_0;

	SYSCFG_TypeDef *pSYSCFG_Handle = SYSCFG;
	pSYSCFG_Handle->EXTICR[3] &= ~(0xf << 4);
	pSYSCFG_Handle->EXTICR[3] |=  (0x2 << 4);

	pGPIO_Handle = GPIOC;
	pGPIO_Handle->MODER &= ~(GPIO_MODER_MODER13);

	EXTI_TypeDef *pEXTI = EXTI;
	pEXTI->IMR |= EXTI_IMR_MR13;
	pEXTI->FTSR |= EXTI_FTSR_TR13;

	NVIC_EnableIRQ(EXTI15_10_IRQn);
	return;
}

void gpio_toggle(GPIO_TypeDef *gpioPort, uint32_t gpioPin)
{
	uint32_t temp;
	GPIO_TypeDef *pGPIO_Handle;
	pGPIO_Handle = gpioPort;
	temp = pGPIO_Handle->IDR;
	temp ^= (1 << gpioPin);
	pGPIO_Handle->ODR = temp;
}

bool gpio_read(GPIO_TypeDef *gpioPort, uint32_t gpioPin){
	uint32_t temp;
	GPIO_TypeDef *pGPIO_Handle;
	pGPIO_Handle = gpioPort;
	temp = pGPIO_Handle->IDR;
	if(temp & (1 << gpioPin))
		return true;
	return false;
}
