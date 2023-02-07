#include "CLOCK.h"
#include "GPIO.h"
#include "SYS_INIT.h"
#include "USART.h"

#include <stdio.h>


#define RED 0
#define GREEN 1
#define YELLOW 10

void go(GPIO_TypeDef *);
void initPins(GPIO_TypeDef *, uint16_t pins);



int main(void) {
	
	initClock();
	sysInit();
	
	/* Enabling GPIOA and GPIOB in the AHB1 Bus */
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOAEN_Pos);
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOBEN_Pos);
	
	/* Initialize pin 0,1,4,5...9,10 */
	uint16_t myPins = 0b00000111111110011;
	initPins(GPIOA, myPins);
	initPins(GPIOB, myPins);
	
	return 0;
}

void initPins(GPIO_TypeDef *GPIOx, uint16_t pins) {
		GPIO_InitTypeDef Config;
	
		Config.Mode = GPIO_MODE_OUTPUT_PP;
		Config.Pull = GPIO_NOPULL;
		Config.Speed = GPIO_SPEED_FREQ_LOW;
		Config.Pin= pins;
	
		GPIO_Init(GPIOx, &Config);
}
