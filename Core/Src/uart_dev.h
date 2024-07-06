/*
 * uart_dev.h
 *
 *  Created on: Jul 6, 2024
 *      Author: Juyoung Sunwoo
 */

#ifndef SRC_UART_DEV_H_
#define SRC_UART_DEV_H_

#define UART_SIZE 0xFF

typedef struct ring_buffer{
	uint8_t tx[UART_SIZE];	// data from buffer to uart
	uint8_t rx[UART_SIZE];	// data from uart to buffer
	uint8_t ptrTxHead;
	uint8_t ptrTxTail;
	uint8_t ptrRxHead;
	uint8_t ptrRxTail;
	uint16_t length;
}RingBuffer;

void USART1_RingBuffer_Init(void);
void SerialHandler();
uint8_t write_Rx_RingBuffer(RingBuffer *buffer, uint8_t data);
uint8_t read_Rx_RingBuffer(RingBuffer *buffer, uint8_t *data);
uint8_t write_Tx_RingBuffer(RingBuffer *buffer, uint8_t data);
uint8_t read_Tx_RingBuffer(RingBuffer *buffer, uint8_t *data);

#endif /* SRC_UART_DEV_H_ */
