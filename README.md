STM32F407 HD44780 LCD Driver (4-Bit Mode)

A custom, bare-metal C driver for the Hitachi HD44780U (and compatible) 16x2 Dot Matrix LCD. This project demonstrates low-level peripheral interfacing using the Motorola 6800-series parallel protocol on an STM32F407 Discovery board.
🚀 Key Features

    4-Bit Parallel Interface: Optimized to use only 4 data pins (D4-D7), saving valuable GPIOs for other peripherals.

    Layered Architecture: Clear separation between MCU-level GPIO wrappers and LCD-specific command logic for maximum portability.

    Custom Timing Logic: Precise microsecond delays implemented to match the HD44780 datasheet specifications for reliable initialization and data transfer.

    Full Instruction Set: Includes functions for clearing display, cursor positioning (Lines 1 & 2), and string printing.

🛠 Hardware Architecture

The driver follows a modular design to ensure that the application logic doesn't depend directly on the hardware registers.

    Core/: Contains the main application and interrupt handlers.

    MCU_Drivers/: Custom wrappers for STM32F4xx GPIO configuration.

    Int_Drivers/: The "Interface" layer—contains the HD44780 command logic and initialization sequence.

📌 Pin Mapping
LCD Pin	STM32 Pin	Function
RS	PD0	Register Select (Command/Data)
RW	PD1	Read/Write Select
EN	PD2	Enable (Execution Start)
D4	PD3	Data Bit 4
D5	PD4	Data Bit 5
D6	PD5	Data Bit 6
D7	PD6	Data Bit 7
💻 Code Example
C

#include "LCD_HD44780.h"

int main(void) {
    // 1. Initialize LCD (GPIOs and HD44780 4-bit sequence)
    LCD_init();
    
    // 2. Clear Screen
    LCDDisplayClear();
    
    // 3. Print to Line 1
    LCDPrintString("STM32 Bare Metal");
    
    // 4. Move to Line 2, Column 1
    LCDSetCursor(2, 1);
    LCDPrintString("HD44780 Driver");

    while(1);
}

📜 How to Setup

    Clone the repo:
    Bash

    git clone https://github.com/mirjunaid/STM32F4xx_LCD_Display_HD44780-_Interface.git

    Import into STM32CubeIDE:

        Go to File -> Import -> Existing Projects into Workspace.

    Include Paths:

        Ensure MCU_Drivers/Inc and Int_Drivers/Inc are added to your project's Include Paths in Project Properties.# STM32F4xx_LCD_Display_HD44780-_Interface
