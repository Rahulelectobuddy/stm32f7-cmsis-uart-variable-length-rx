# stm32f7-cmsis-uart-variable-length-rx
This repo contains implementation for receiving variable length on uart using dma and IDLE line interuppt.

Normally when we want to use DMA transfer we need to have the length of data to be transfered. To overcome this we are using DMA in circular mode. Considering you have maximum size of payload that you aspect to receive on UART. A global buffer is declared twice this size which will hold the data in circular manner. To detect the transfer complete we are using IDLE line interupt. Whenever uart receives idle character it will generate idle flag for uart. In the callback funtion for this interrupt we store the pointer for last position of data received. and through NDTR register of DMA we can get the current transaction's last pointer. This data is transferred to new char array.

## Usage
Currently only stm32F746 is supported.

It utilizes USART2 peripheral with IDLE interrupt enabled and DMA1 with stream 5 configured on clannel 4.

UART bautrate is 115200, 8N1 no handshake.

  | Pin Number | Signal name | STM32 Pin |
  | :---:        |     :---:      |       :---:   |
  |			4 		 | USART_B_RX  | 		 PD6	 |
  | 		6 		 | USART_B_TX	 | 		 PD5	 |
