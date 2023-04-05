#include "CLOCK.h"
#include "GPIO.h"
#include "SYS_INIT.h"
#include "USART.h"
#include "traffic.h"
#include <string.h>


static char tx_buffer[50],rx_buffer[50];
static uint32_t tx,rx, i;

void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void USART2_IRQHandler(void);
void initTransmit(USART_TypeDef *);




int main(void) {
	initClock();
	sysInit();
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOAEN_Pos);
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOBEN_Pos);
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOCEN_Pos);
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIODEN_Pos);
	
	UART2_Config();
	initUART4();
	initUART5();
	
	  NVIC_SetPriority(USART2_IRQn, 0);
    NVIC_EnableIRQ(USART2_IRQn);
    NVIC_SetPriority(UART4_IRQn, 0);
    NVIC_EnableIRQ(UART4_IRQn);
    NVIC_SetPriority(UART5_IRQn, 0);
    NVIC_EnableIRQ(UART5_IRQn);
	
	
		i = 0;
		uint32_t j = 100;

		char cnt[1000];
		
		sprintf(cnt, "%d", j += 20);
		strcat(cnt, " ");
		USART2->DR = '!';
		ms_delay(4000);
		strcat(cnt, tx_buffer);	
		strcat(cnt, "\n");
		USART2_SendString(cnt);
		
		initGPIO_OP(GPIOB);
		initGPIO_OP(GPIOC);
		while(1) {
			simulateTraffic(1, 3);
		}
			
}


void USART2_IRQHandler(void){
    if(USART2->SR & USART_SR_RXNE){
        char c = (uint8_t) USART2->DR & 0xFF;
				if(c == '@') {
					tx_buffer[i++] = '\0';
				}
				else {
					tx_buffer[i++] = c;
				}
        
    }
		else USART2->SR &= ~(USART_SR_RXNE);
}

void UART4_IRQHandler(void)
{   
    if (UART4->SR & USART_SR_RXNE){
        
        rx_buffer[rx] = (uint8_t) UART4->DR;
        
        UART4->SR &= ~(USART_SR_RXNE);
    }
    
    if (UART4->SR & USART_SR_TXE){

        UART4->DR = tx_buffer[tx];
        
        UART4->SR &= ~(USART_SR_TXE);
        UART4->CR1 &= ~(USART_CR1_TXEIE);
    }
    
}

void UART5_IRQHandler(void){
    
    if (UART5->SR & USART_SR_RXNE){   
        
        rx_buffer[rx] = (uint8_t) UART5->DR; 
        
        UART5->SR &= ~(USART_SR_RXNE);
        
    }
    if (UART5->SR & USART_SR_TXE){

        UART5->DR = tx_buffer[tx];      
        
        UART5->SR &= ~(USART_SR_TXE);
        UART5->CR1 &= ~USART_CR1_TXEIE;
    }
}

void initTransmit(USART_TypeDef *UARTx) {
			UARTx->CR1 |= USART_CR1_TXEIE; 	
			while((UARTx->CR1 & USART_CR1_TXEIE));	
			ms_delay(1);
}