/*
 * stm32f7cc_dma.c
 *
 *  Created on: 02-Nov-2020
 *      Author: RahulGarg
 */


/*
 * How to use this driver
 *	1. Enable the DMA peripheral clock.
 *	2. Enable and configure the peripheral to be connected to the DMA Stream (except for
 *	internal SRAM/FLASH memories: no initialization is necessary)
 *	3. For a given Stream, program the required configuration through the following
 *	parameters:
 *		Transfer Direction, Source and Destination data formats, Circular, Normal or peripheral
 *		 flow control mode, Stream Priority level, Source and Destination Increment mode, FIFO
 *		 mode and its Threshold (if needed), Burst mode for Source and/or Destination.
 *
 *	Polling mode IO operation
 *		Use HAL_DMA_Start() to start DMA transfer after the configuration of Source address and
 *		 destination address and the Length of data to be transferred.
 *		Use HAL_DMA_PollForTransfer() to poll for the end of current transfer, in this case a
 *		 fixed Timeout can be configured by User depending from his application.
 *		Use HAL_DMA_Abort() function to abort the current transfer.
 *
 *	Interrupt mode IO operation
 *		Configure the DMA interrupt priority using HAL_NVIC_SetPriority()
 *		Enable the DMA IRQ handler using HAL_NVIC_EnableIRQ()
 *		Use HAL_DMA_Start_IT() to start DMA transfer after the configuration of Source address
 *		 and destination address and the Length of data to be transferred. In this case the DMA
 *		 interrupt is configured
 *		Use HAL_DMA_IRQHandler() called under DMA_IRQHandler() Interrupt subroutine
 *		At the end of data transfer HAL_DMA_IRQHandler() function is executed and user can add
 *		 his own function by customization of function pointer XferCpltCallback and
 *		 XferErrorCallback (i.e a member of DMA handle structure).
 *		1.Use HAL_DMA_GetState() function to return the DMA state and HAL_DMA_GetError() in
 *		 case of error detection.
 *		2.Use HAL_DMA_Abort_IT() function to abort the current transfer.
 *
 *	Note - In Memory-to-Memory transfer mode, Circular mode is not allowed. The FIFO is used
 *	mainly to reduce bus usage and to allow data packing/unpacking: it is possible to set
 *	different Data Sizes for the Peripheral and the Memory (ie. you can set Half-Word data
 *	size for the peripheral to access its data register and set Word data size for the Memory
 *	to gain in access time. Each two half words will be packed and written in a single access
 *	to a Word in the Memory).  When FIFO is disabled, it is not allowed to configure different
 *	Data Sizes for Source and Destination. In this case the Peripheral Data Size will be
 *	 applied to both Source and Destination.
 */

#include "stm32f746xx.h"

extern char global_buff[10];

void init_dma(void)
{
	RCC_TypeDef *pRCC_Handle = RCC;
	pRCC_Handle->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

	USART_TypeDef *pUSART_Handle;
	pUSART_Handle = USART2;

	DMA_TypeDef *pDMA;
	pDMA = DMA1;

	DMA_Stream_TypeDef *pDMA_Stream;
	pDMA_Stream = DMA1_Stream5;

	pDMA_Stream->CR |= DMA_SxCR_CHSEL_2;
	pDMA_Stream->PAR = 0x40004424;//(uint32_t) pUSART_Handle->RDR;
	pDMA_Stream->M0AR = global_buff;
	pDMA_Stream->CR |= DMA_SxCR_MINC;
	pDMA_Stream->NDTR = 10;
//	Direction is default to memory to peripheral
//	Size of memory and peripheral are default to 8 bits
	pDMA_Stream->FCR |= DMA_SxFCR_FTH_Msk;

	pDMA_Stream->CR |= DMA_SxCR_CIRC;
	pDMA_Stream->CR |= DMA_SxCR_EN;
//	Single mode default
//	Default stream priority

	return;
}
