/*
 * Copyright (c) 2022 
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "USART.h"
#include <string.h>
#include "CLOCK.h"
#include "stm32f446xx.h"


// Send a string to the UART PORTx
void USART2_SendString(char* s) {
    while(*s) {
        while(!(USART2->SR & USART_SR_TXE));
        USART2->DR = (*s++ & 0xFF);
    }
}

char USART2_GetChar(void) {
		while(!(USART2->SR & USART_SR_TXE));
		return (USART2->DR & 0xFF);
}


/**********************************
* USART 2 Configuration
***********************************/
void UART2_Config(void){
	/******************************************
	* 1. Enable UART clock and GPIO clock
	* 2. Configure UART pin for Alternate function
	* 3. Enable UART on USART_CR1 rgister
	* 4. Program M bit in USART CR1 to define the word length
	* 5. Select the baud rate using the USART_BRR register.
	* 6. Enable transmission TE and recieption bits in USART_CR1 register
	*******************************************/
	//1. Enable UART clock and GPIO clock
	RCC->APB1ENR |= (1<<17); //enable UART 2 

		
	//2. Configure UART pin for Alternate function
	GPIOA->MODER |= (2<<4); //bits [5:4] -> 1:0 -->Alternate function for pin PA2
	GPIOA->MODER |= (2<<6); //bits [7:6] -> 1:0 -->Alternate function for PA3
	
	GPIOA->OSPEEDR |= (3<<4) | (3<<6); //bits [5:4] -> 1:1 -> high speed PA2; bits [7:6] -> 1:1 -> high speed PA3 
	
	GPIOA->AFR[0] |= (7<<8);//Bytes (11:10:09:08) = 0:1:1:1 --> AF7 Alternate function for USART2 at pin PA2
	GPIOA->AFR[0] |= (7<<12); //Bytes (15:14:13:12) = 0:1:1:1 --> AF7 Alternate function for USART2 at pin PA3
	
	//3. Enable UART on USART_CR1 rgister
	USART2->CR1 = 0x00; //clear USART
	USART2->CR1 |= (1<<13);  // UE-bit enable USART
	
	//4. Program M bit in USART CR1 to define the word length
	USART2->CR1 &= ~(1U<<12); // set M bit  = 0 for 8-bit word length
	
	//5. Select the baud rate using the USART_BRR register.
	USART2->BRR |= (7<<0) | (24<<4); //115200
	
	//  6. Enable transmission TE and recieption bits in USART_CR1 register
	USART2->CR1 |= (1<<2); // enable RE for receiver 
	USART2->CR1 |= (1<<3); //enable TE for transmitter
	
	 USART2->CR1 |= USART_CR1_RXNEIE;

}

void initUART4(void) {
// Enable clock for UART4
RCC->APB1ENR |= RCC_APB1ENR_UART4EN;

	// Configure GPIO pins for UART4 : PA0 as TX and PA1 as RX
GPIOA->AFR[0] |= (8 << (0 * 4)) | (8 << (1 * 4));
GPIOA->MODER |= (2 << (0 * 2)) | (2 << (1 * 2));

// Configure UART4
UART4->BRR |= (7<<0) | (24<<4);
UART4->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
	
	UART4->CR1 |= USART_CR1_RXNEIE; //enable RXNEIE for reciever
	


}

void initUART5(void) {
// Enable clock for UART5
RCC->APB1ENR |= RCC_APB1ENR_UART5EN;

	// Configure GPIO pins for UART5 : PC12 as TX and PD2 as RX
GPIOC->AFR[1] |= (8 << ((12 - 8) * 4));
GPIOD->AFR[0] |= (8 << ((2 - 0) * 4));
GPIOC->MODER |= (2 << (12 * 2));
GPIOD->MODER |= (2 << (2 * 2));

// Configure UART5
UART5->BRR |= (7<<0) | (24<<4);
UART5->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

UART5->CR1 |= USART_CR1_RXNEIE; //enable RXNEIE for reciever

}

