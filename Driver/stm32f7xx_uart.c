/*
 * stm32f7xx_uart.c
 *
 *  Created on: 18-Oct-2020
 *      Author: RahulGarg
 */

/*
 * @brief :
 *
 * @note :
 * 	The UART HAL driver can be used as follows:
 *		1. Declare a UART_HandleTypeDef handle structure.
 *		2. Initialize the UART low level resources :
 *			a. Enable the USARTx interface clock.
 *			b. UART pins configuration:
 *				- Enable the clock for the UART GPIOs.
 *				- Configure these UART pins as alternate function pull-up.
 *			c. NVIC configuration if you need to use interrupt process :
 *				- Configure the USARTx interrupt priority.
 *				- Enable the NVIC USART IRQ handle.
 *			d. DMA Configuration if you need to use DMA process:
 *				- Declare a DMA handle structure for the Tx/Rx stream.
 *				- Enable the DMAx interface clock.
 *				- Configure the declared DMA handle structure with the required Tx/Rx parameters.
 *				- Configure the DMA Tx/Rx Stream.
 *				- Associate the initialized DMA handle to the UART DMA Tx/Rx handle.
 *				- Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx/Rx Stream.
 *		3. Program the Baud Rate, Word Length, Stop Bit, Parity,Hardware flow control and Mode(Receiver/Transmitter) in the Init structure.
 *		4. For the UART asynchronous mode, initialize the UART registers.
 *
 */
void init_uart(void){

	return;
}

