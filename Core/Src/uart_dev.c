/*
 * uart_dev.c
 * Ring Buffer with read, write
 * Driven by an isr which indicates that
 * a byte has been received by a UART and written to a
 * memory mapped read address: UART_READ_ADDR
 * The buffer should run at 115200 bps
 * with min latency and interrupt safe
 *  Created on: Jul 6, 2024
 *      Author: Juyoung Sunwoo
 */

#include "stm32f0xx_hal.h"
#include "uart_dev.h"

uint8_t UART1_rxBuffer[255]={0};

 UART_HandleTypeDef UART1_RingBuffer;

 void SerialHandler(){

	// read_Rx_RingBuffer (&UART1_RingBuffer, UART1_rxBuffer);
	// write_Rx_RingBuffer(&UART1_RingBuffer, UART1_rxBuffer);
	  HAL_UART_Receive (&UART1_RingBuffer, UART1_rxBuffer, 12, 5000);
	  HAL_UART_Transmit(&UART1_RingBuffer, UART1_rxBuffer, 12, 100);
 }
/**
  * @brief USART1 Initialization Function
  * PA9 USART1 Tx
  * PA10 USART1 Rx
  * @param None
  * @retval None
  */
void USART1_RingBuffer_Init(void)
{
	UART1_RingBuffer.Instance = USART1;
	UART1_RingBuffer.Init.BaudRate = 115200;
	UART1_RingBuffer.Init.WordLength = UART_WORDLENGTH_8B;
	UART1_RingBuffer.Init.StopBits = UART_STOPBITS_1;
	UART1_RingBuffer.Init.Parity = UART_PARITY_NONE;
	UART1_RingBuffer.Init.Mode = UART_MODE_TX_RX;
	UART1_RingBuffer.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART1_RingBuffer.Init.OverSampling = UART_OVERSAMPLING_16;
	UART1_RingBuffer.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	UART1_RingBuffer.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&UART1_RingBuffer) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
uint8_t write_Rx_RingBuffer(RingBuffer *buffer, uint8_t data){

	// If the buffer is full, don't write
	if(buffer->ptrRxHead == buffer->ptrRxTail){
		return -1;
	}
	buffer->rx[buffer->ptrRxHead]=data;
	buffer->ptrRxHead+=1;
	return 0;
}

uint8_t read_Rx_RingBuffer(RingBuffer *buffer, uint8_t *data){

	// If the buffer is full, don't read
	if(buffer->ptrRxHead == buffer->ptrRxTail){
		return -1;
	}
	*data = buffer->rx[buffer->ptrRxTail];
	printf("%c", *data);
	buffer->ptrRxTail+=1;
	return 0;
}

uint8_t write_Tx_RingBuffer(RingBuffer *buffer, uint8_t data){

	// If the buffer is full, don't write
	if(buffer->ptrTxHead == buffer->ptrTxTail){
		return -1;
	}
	buffer->rx[buffer->ptrTxHead]=data;
	buffer->ptrTxHead+=1;
	return 0;
}

uint8_t read_Tx_RingBuffer(RingBuffer *buffer, uint8_t *data){

	// If the buffer is full, don't read
	if(buffer->ptrTxHead == buffer->ptrTxTail){
		return -1;
	}
	*data = buffer->rx[buffer->ptrTxTail];
	buffer->ptrTxTail+=1;
	return 0;
}
