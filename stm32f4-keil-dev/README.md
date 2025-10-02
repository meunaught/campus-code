### Embedded Systems– Learning Projects (GPIO, UART, I2C, SPI)

This repository contains small STM32F446RE learning projects built with Keil uVision (MDK-ARM). They focus on bare‑metal register‑level programming to learn core MCU peripherals, timing, and interrupt handling.

- **MCU**: STM32F446RE (Cortex‑M4F)
- **Clock**: System clock set to 180 MHz via HSE + PLL
- **IDE/Toolchain**: Keil uVision (.uvprojx, .uvoptx)
- **Peripherals used**: GPIO, SysTick, USART (UART2, UART4, UART5)

### Projects

- `gpio-led-traffic-simulation/`
  - LED traffic pattern and simple sensor inputs using GPIOA/GPIOB outputs and GPIOC inputs.
  - Demonstrates pin initialization, BSRR writes, polling inputs, timing via SysTick.

- `uart-comm-simulation/`
  - Multi‑UART demo: configures USART2, UART4, UART5; uses RXNE/TXE interrupts and ring‑like buffers to move data; drives a traffic light sequence based on received parameters.

### Build and run (Keil uVision)

1. Open the appropriate `.uvprojx` in Keil:
   - `gpio-led-traffic-simulation/test1.uvprojx`
   - `uart-comm-simulation/uart.uvprojx`
2. Select target STM32F446RETx.
3. Build (F7) and download to your board (Ctrl+F8) or run in the Keil simulator.

### Common modules

- `CLOCK.c/.h`: Configures HSE and PLL for 180 MHz system clock.
- `SYS_INIT.c/.h`: Initializes SysTick to 1 ms tick; provides `ms_delay()`.
- `GPIO.c/.h`: Minimal GPIO driver: `GPIO_Init`, `GPIO_WritePin`, `GPIO_ReadPin` using MODER/OTYPER/OSPEEDR/PUPDR and BSRR.
- `USART.c/.h` (each project): Lightweight UART helpers for send/receive and per‑instance configuration.

### Hardware notes

- Ensure HSE clock source matches your board (Nucleo‑F446RE uses 8 MHz HSE). The PLL settings here assume 8 MHz HSE → 180 MHz SYSCLK.
- Pin mappings are documented per project README; connect LEDs/sensors accordingly.

### License and credit

Portions of this code include educational starter material credited to the University of Dhaka, CSE Batch 25, and Prof. Mosaddek Tushar (see headers).


