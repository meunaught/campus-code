#include "CLOCK.h"
#include "GPIO.h"
#include "SYS_INIT.h"
#include "USART.h"

#include <stdio.h>

#define RED 1
#define GREEN 0
#define YELLOW 10
#define R2G 10 
#define R2Y 5
#define EXTRA 3

void go (GPIO_TypeDef *, int rep);
void resetLED (void);
void initPins (GPIO_TypeDef *, uint16_t pins);
void showTraffic (GPIO_TypeDef *, uint16_t, uint16_t);


int main(void) {
	
	initClock();
	sysInit();
	
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOAEN_Pos);
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOBEN_Pos);
	
	/* Initialize pin 0,1,4,5...9,10 */
	uint16_t myPins = 0b00000111111110011;
	initPins(GPIOA, myPins);
	initPins(GPIOB, myPins);
	
	uint16_t now = 0;
	
	while(1) {
		GPIO_TypeDef *currGPIO;
		uint16_t traffic[4];
		for(int i = 0; i < 4; ++i) {
			traffic[i] = (uint16_t) rand() % 4;
		}
		
		int extraTime = 0;
		
		if(now) {
			currGPIO = GPIOA;
			GPIO_WritePin(GPIOA, GREEN, GPIO_PIN_SET);
			GPIO_WritePin(GPIOB, RED, GPIO_PIN_SET);
			showTraffic(GPIOB, traffic[2], traffic[3]);
			showTraffic(GPIOA, traffic[0], traffic[1]);
			if(traffic[0] + traffic[1] < 3) {
				extraTime = EXTRA;
			}
		}
		else {
			currGPIO = GPIOB;
			GPIO_WritePin(GPIOB, GREEN, GPIO_PIN_SET);
			GPIO_WritePin(GPIOA, RED, GPIO_PIN_SET);
			showTraffic(GPIOA, traffic[0], traffic[1]);
			showTraffic(GPIOB, traffic[2], traffic[3]);
			if(traffic[2] + traffic[1] < 3) {
				extraTime = EXTRA;
			} 
		}
		
		go(currGPIO, R2G + extraTime);
		
		GPIO_WritePin(currGPIO, YELLOW, GPIO_PIN_SET);
    GPIO_WritePin(currGPIO, GREEN, GPIO_PIN_RESET);
		
		go(currGPIO, R2Y);
		
		now ^= 1;
		
		resetLED();
		
	}
	
	return 0;
}

void resetLED (void) {
	for(uint16_t i = 0; i <= 10; ++i) {
		if(i == 2 || i == 3) continue;
		GPIO_WritePin(GPIOA, i, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOB, i, GPIO_PIN_RESET);
	}
}

void initPins(GPIO_TypeDef *GPIOx, uint16_t pins) {
		GPIO_InitTypeDef Config;
	
		Config.Mode = GPIO_MODE_OUTPUT_PP;
		Config.Pull = GPIO_NOPULL;
		Config.Speed = GPIO_SPEED_FREQ_LOW;
		Config.Pin= pins;
	
		GPIO_Init(GPIOx, &Config);
}

void showTraffic(GPIO_TypeDef *GPIOx, uint16_t l, uint16_t r) {
		for(uint16_t i= 0; i < l; ++i) {
        GPIO_WritePin(GPIOx, (uint16_t) i + 4, GPIO_PIN_SET);
    }
    for(uint16_t j = 0; j < r; ++j){
        GPIO_WritePin(GPIOx, (uint16_t) j + 7, GPIO_PIN_SET);
    }
}

void go(GPIO_TypeDef *GPIOx, int rep){
		while(rep--) {
			for(uint16_t i = 4; i <= 9; ++i){
        GPIO_WritePin(GPIOx, i, GPIO_PIN_SET);
			}
			ms_delay(250);
			GPIO_WritePin(GPIOx, 4, GPIO_PIN_RESET);
			GPIO_WritePin(GPIOx, 7, GPIO_PIN_RESET);
			ms_delay(250);
			GPIO_WritePin(GPIOx, 5, GPIO_PIN_RESET);
			GPIO_WritePin(GPIOx, 8, GPIO_PIN_RESET);
			ms_delay(250);	
			GPIO_WritePin(GPIOx, 6, GPIO_PIN_RESET);
			GPIO_WritePin(GPIOx, 9, GPIO_PIN_RESET);
			ms_delay(250);		
		}
}