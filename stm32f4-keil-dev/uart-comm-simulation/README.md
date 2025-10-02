### UART Communication Simulation (STM32F446RE)

Demonstrates multi‑UART setup with interrupts and a simple application that receives parameters over UART and drives a GPIO traffic light sequence.

### Features
- System clock at 180 MHz (HSE + PLL). SysTick 1 ms delay utilities
- USART2 configured on PA2/PA3; helper TX function `USART2_SendString`
- UART4 (PA0/PA1) and UART5 (PC12/PD2) configured with RXNE/TXE interrupts
- Simple RX/TX buffers filled in IRQ handlers; TXEIE used to transmit queued bytes
- `traffic.c` drives LEDs on `GPIOB`/`GPIOC` based on received timing values

### Key files
- `main.c`: clocks, NVIC config, UART init (USART2, UART4, UART5), IRQ handlers, traffic loop
- `USART.c/.h`: per‑UART configuration and helper routines (send/recv)
- `traffic.c/.h`: GPIO init for LED pins; `simulateTraffic(rt, yt)` cycles red/yellow/green timings
- `CLOCK.c/.h`, `SYS_INIT.c/.h`, `GPIO.c/.h`: shared support

### Pin mapping
- USART2: `PA2` (TX), `PA3` (RX), AF7
- UART4: `PA0` (TX), `PA1` (RX), AF8
- UART5: `PC12` (TX), `PD2` (RX), AF8
- LEDs:
  - Defined in `traffic.h`: `RED=4`, `YELLOW=5`, `GREEN=6`, `WHITE=7`
  - Outputs configured on `GPIOB` and `GPIOC` for pins 4..7

### Data flow
- Characters received on USART2/UART4/UART5 trigger `*_IRQHandler`.
- RX handlers push bytes into `rx_buffer`; TX handlers drain `tx_buffer` using TXEIE.
- After reception, `main.c` parses digits from `rx_buffer` to derive `RT`, `YT` (and others), then calls `simulateTraffic(GT, YT)` in a loop.

### Build and run
1. Open `uart.uvprojx` in Keil uVision.
2. Build and flash to an STM32F446RE board (or simulate).
3. Connect a USB‑UART adapter to the corresponding pins and send parameter frames to observe LED timing changes.

### Notes
- Ensure RCC clocks for GPIOA/B/C/D and relevant UARTs are enabled (done in code).
- The simple buffers and parsing are for educational purposes; add bounds‑checking and framing for robustness in real apps.