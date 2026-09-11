# Dual-AVR ATmega32 Smart Home System

A comprehensive, fully automated smart home embedded system simulated in Proteus. This project features a dual-microcontroller architecture where a Master ATmega32 handles local environmental sensing, security, and a dynamic dashboard, while a Slave ATmega32 acts as a remote door controller via UART communication.

## 🌟 Key Features

*   **Security & Access Control:** Keypad-based PIN authentication. Includes a 3-attempt lockout system and a continuous "911 Alert" protocol after 4 failed attempts.
*   **Dual-Door Servo Control:** 
    *   **Door 1 (Local):** Controlled directly by the Master AVR via hardware Timer1.
    *   **Door 2 (Remote):** Controlled by the Slave AVR receiving custom UART commands.
*   **Automated Environmental Control:** 
    *   **Temperature (LM35):** Automatically adjusts DC fan speed using 8-bit Fast PWM based on HOT, WARM, or COLD thresholds.
    *   **Lighting (LDR):** Automatically toggles exterior and interior LEDs based on MORNING, AFTERNOON, and EVENING ambient light levels.
*   **Dynamic LCD Dashboard:** A real-time 16x2 LCD interface displaying temperature, lock states, and peripheral statuses using custom space-saving abbreviations.
*   **Auto vs. Manual Override:** A menu-driven system allowing the user to take manual control of the doors, lights, and fan. Activating manual mode safely locks out the automated sensor loops until the user re-enables "Auto Mode."

## ⚙️ Software Architecture & Optimizations

*   **Non-Blocking Keypad Polling:** Implemented a micro-delay timeout loop (500ms window) for the keypad. This ensures the LCD dashboard and ADC sensors update twice a second in real-time without freezing the system while waiting for user input.
*   **Dynamic Timer Re-allocation:** Solved hardware timer collisions by dynamically re-initializing Timer1 on the Master AVR. The system rapidly switches between a 50Hz configuration (for Servo movement) and an 8-bit Fast PWM configuration (for the DC Fan), allowing both to operate perfectly using a single hardware timer.
*   **UART Polling Optimization:** Implemented a custom `UART_u8DataAvailable()` check on the Slave AVR to prevent tight polling loops, drastically reducing CPU load and stabilizing the Proteus simulation frame rate.

## 🛠️ Technologies & Tools

*   **Language:** Embedded C
*   **Microcontroller:** ATmega32 (AVR Architecture)
*   **Simulation Environment:** Proteus ISIS
*   **Toolchain:** AVR GCC / Atmel Studio

## 🔌 Hardware Pin Mapping (Master AVR)

| Component | Port / Pin | Configuration |
| :--- | :--- | :--- |
| **16x2 LCD** | `PORTB` & `PORTC` | Output (Data & Command lines) |
| **Keypad 4x4** | `PORTB` | Input (Rows) / Output (Cols) |
| **Servo Motor (Door 1)** | `PD5` (OC1A) | Output (50Hz PWM) |
| **DC Motor (Fan)** | `PD4` (OC1B) | Output (8-bit Fast PWM) |
| **LM35 Sensor** | `PA1` (ADC1) | Input (Analog) |
| **LDR Sensor** | `PA0` (ADC0) | Input (Analog) |
| **Inside LED** | `PD6` | Output (Digital) |
| **Outside LED** | `PA3` | Output (Digital) |
| **Buzzer / Alarm** | `PD7` | Output (Digital) |
| **UART TX / RX** | `PD1` / `PD0` | Output / Input (Serial to Slave) |

## 🚀 How to Run the Simulation

1. Clone this repository to your local machine.
2. Compile the `main1.c` (Master) and `main2.c` (Slave) files using your preferred AVR compiler to generate the `.hex` files.
3. Open the provided `.pdsprj` schematic file in Proteus.
4. Double-click the **Master ATmega32**, load the `master.hex` file, and ensure the clock frequency is set to **8MHz**.
5. Double-click the **Slave ATmega32**, load the `slave.hex` file, and ensure the clock frequency is set to **8MHz**.
6. Run the simulation. The default system PIN is **951236**.

## 👥 Project Team

This project was developed by undergraduate engineering students at Alexandria University:
*   **Ahmed Gaber** 
*   **Mohamed Hany**
*   **Mahmoud Hany**
*   **Ezz Fadel**
