### GPIO LED Traffic Simulation (STM32F446RE)

Bare‑metal GPIO demo that simulates a two‑way traffic light with lane indicators and simple “sensor” inputs. Timing is driven by SysTick; LEDs are toggled using BSRR writes. Built for Keil uVision.

### Features
- Output lanes on `GPIOA` and `GPIOB` pins 4..9 (progress bars) plus dedicated color pins
- Input sensors on `GPIOC` pins 6, 9, 10, 11 (polled)
- Alternates between two directions with green → yellow timing; adds extra green time if both sensors are inactive

### Key files
- `main.c`: sets up clocks, GPIO, input polling, and the traffic sequence
- `GPIO.c/.h`: minimal GPIO driver (`GPIO_Init`, `GPIO_WritePin`, `GPIO_ReadPin`)
- `CLOCK.c/.h`: HSE + PLL to 180 MHz
- `SYS_INIT.c/.h`: SysTick 1 ms tick and `ms_delay()`
- `USART.c/.h`: basic USART2 helpers (not required for the GPIO demo)

### Pin mapping (as used in `main.c`)
- Outputs (configured on both `GPIOA` and `GPIOB`):
  - Progress LEDs: pins 4,5,6 and 7,8,9 are swept in `go()`
  - Color control indices (used with `GPIO_WritePin`):
    - `GREEN = 0` (GPIOx pin 0)
    - `RED = 1` (GPIOx pin 1)
    - `YELLOW = 10` (GPIOx pin 10)
- Inputs (`GPIOC`): pins 6, 9, 10, 11 read as sensors to adjust timing

Adapt the mapping to your board by moving LED jumpers or changing constants in `main.c`.

### Build and run
1. Open `test1.uvprojx` in Keil uVision.
2. Build and flash to an STM32F446RE board (or run the simulator).
3. Observe LED sequences on ports A/B; toggle inputs on port C to vary green time.

### How it works
- `initPins()` calls `GPIO_Init()` with mode `GPIO_MODE_OUTPUT_PP` for outputs and `GPIO_MODE_INPUT` for inputs.
- `showTraffic()` lights left/right lane bars based on pseudo‑random counts.
- `go()` steps through pins 4..9 with 250 ms delays, creating a sweep effect.
- The main loop alternates active direction and inserts extra green time when both sensors are inactive.

### Notes
- Ensure RCC enables for GPIOA/B/C are set (done in `main.c`).
- If your board wiring differs, update the pin lists and color indices accordingly.