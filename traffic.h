#include "GPIO.h"

#define RED 4
#define GREEN 6
#define YELLOW 5

#define WHITE 7


uint16_t genpin(int *, int);
void initGPIO_OP (GPIO_TypeDef *);
void simulateTraffic(int, int);