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
void initPins (GPIO_TypeDef *, uint16_t, uint16_t);
void showTraffic (GPIO_TypeDef *, uint16_t, uint16_t);
uint16_t genpin(int *, int);

 
int main(void) {
	
	initClock();
	sysInit();
	
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOAEN_Pos);
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOBEN_Pos);
	RCC->AHB1ENR |= (1<<RCC_AHB1ENR_GPIOCEN_Pos);
	
	int outPins[] = {0,1,4,5,6,7,8,9,10};
	int inPins[] = {6, 9, 10, 11};
	uint16_t out = genpin(outPins, 9);
	uint16_t in = genpin(inPins, 4);
	initPins(GPIOA, out, GPIO_MODE_OUTPUT_PP);
	initPins(GPIOB, out, GPIO_MODE_OUTPUT_PP);
	initPins(GPIOC, in, GPIO_MODE_INPUT);
	
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
			GPIO_PinState l = GPIO_ReadPin(GPIOC, 6);
			GPIO_PinState r = GPIO_ReadPin(GPIOC, 9);
			if(l == GPIO_PIN_RESET && r == GPIO_PIN_RESET) {
				extraTime = EXTRA;
			}
		}
		else {
			currGPIO = GPIOB;
			GPIO_WritePin(GPIOB, GREEN, GPIO_PIN_SET);
			GPIO_WritePin(GPIOA, RED, GPIO_PIN_SET);
			showTraffic(GPIOA, traffic[0], traffic[1]);
			showTraffic(GPIOB, traffic[2], traffic[3]);
			GPIO_PinState l = GPIO_ReadPin(GPIOC, 10);
			GPIO_PinState r = GPIO_ReadPin(GPIOC, 11);
			if(l == GPIO_PIN_RESET && r == GPIO_PIN_RESET) {
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

uint16_t genpin(int *pins, int n) {
	uint16_t pin = 0;
	for(int i = 0; i < n; ++i) {
		pin |= 1U << pins[i];
	}
	return pin;
}

void resetLED (void) {
	for(uint16_t i = 0; i <= 10; ++i) {
		if(i == 2 || i == 3) continue;
		GPIO_WritePin(GPIOA, i, GPIO_PIN_RESET);
		GPIO_WritePin(GPIOB, i, GPIO_PIN_RESET);
	}
}

void initPins(GPIO_TypeDef *GPIOx, uint16_t pins, uint16_t mode) {
		GPIO_InitTypeDef Config;
	
		Config.Mode = mode;
		Config.Pull = GPIO_NOPULL;
		Config.Speed = GPIO_SPEED_FREQ_HIGH;
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