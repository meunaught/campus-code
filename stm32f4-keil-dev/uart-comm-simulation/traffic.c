#include "traffic.h"
#include "GPIO.h"
#include "SYS_INIT.h"

uint16_t genpin(int *pins, int n) {
	uint16_t pin = 0;
	for(int i = 0; i < n; ++i) {
		pin |= 1U << pins[i];
	}
	return pin;
}

void initGPIO_OP (GPIO_TypeDef *GPIOx) {
		GPIO_InitTypeDef Config;
	
		int pins[] = {4,5,6,7};
	
		Config.Mode = GPIO_MODE_OUTPUT_PP;
		Config.Pull = GPIO_NOPULL;
		Config.Speed = GPIO_SPEED_FREQ_HIGH;
		Config.Pin= genpin(pins, 4);
	
		GPIO_Init(GPIOx, &Config);
}

void simulateTraffic(int rt, int yt) {
		rt *= 1000;
		yt *= 1000;
				GPIO_WritePin(GPIOB, RED, GPIO_PIN_SET);
				GPIO_WritePin(GPIOC, GREEN, GPIO_PIN_SET);
				GPIO_WritePin(GPIOC, WHITE, GPIO_PIN_SET);
	
	
				ms_delay(rt);
				
				GPIO_WritePin(GPIOB, RED, GPIO_PIN_RESET);
				GPIO_WritePin(GPIOC, GREEN, GPIO_PIN_RESET);
				GPIO_WritePin(GPIOC, WHITE, GPIO_PIN_RESET);
			
				GPIO_WritePin(GPIOB, YELLOW, GPIO_PIN_SET);
				GPIO_WritePin(GPIOC, YELLOW, GPIO_PIN_SET);
			
				ms_delay(yt);
			
				GPIO_WritePin(GPIOB, YELLOW, GPIO_PIN_RESET);
				GPIO_WritePin(GPIOC, YELLOW, GPIO_PIN_RESET);
			
				
				GPIO_WritePin(GPIOB, GREEN, GPIO_PIN_SET);
				GPIO_WritePin(GPIOC, RED, GPIO_PIN_SET);
				GPIO_WritePin(GPIOB, WHITE, GPIO_PIN_SET);
			
				ms_delay(rt);
				
				GPIO_WritePin(GPIOB, GREEN, GPIO_PIN_RESET);
				GPIO_WritePin(GPIOC, RED, GPIO_PIN_RESET);
				GPIO_WritePin(GPIOB, WHITE, GPIO_PIN_RESET);
				
				ms_delay(1000);
			
}