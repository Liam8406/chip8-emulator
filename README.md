# CHIP-8 Emulator

A CHIP-8 emulator written in C++ as a systems programming learning project.

The goal of this project is to better understand how emulators work internally by building one from scratch and implementing the architecture step by step.

This project follows the TobiasVL CHIP-8 guide while implementing everything manually.

## Current Progress

Implemented so far:

- 4KB memory
- CHIP-8 fontset loaded into memory
- Registers (V0–VF)
- Index register (I)
- Program Counter (PC)
- Stack and subroutines
- Delay and sound timers
- Keypad state handling
- ROM loading
- Fetch cycle
- Full opcode decoder
- Complete CHIP-8 opcode implementation
- 64x32 display buffer
- XOR sprite rendering
- Collision flag handling (VF)
- BCD conversion
- Memory store/load instructions
- Font character lookup
- Random number generation
- Skip instructions and keypad instructions

Successfully runs the IBM Logo test ROM in the terminal.

## Implemented Opcodes

| Opcode | Description |
|----------|-------------|
| 00E0 | Clear screen |
| 00EE | Return from subroutine |
| 1NNN | Jump |
| 2NNN | Call subroutine |
| 3XNN | Skip if VX == NN |
| 4XNN | Skip if VX != NN |
| 5XY0 | Skip if VX == VY |
| 6XNN | Set VX |
| 7XNN | Add to VX |
| 8XY0 | Copy VY into VX |
| 8XY1 | Binary OR |
| 8XY2 | Binary AND |
| 8XY3 | Binary XOR |
| 8XY4 | Add VY to VX |
| 8XY5 | Subtract VX - VY |
| 8XY6 | Shift right |
| 8XY7 | Subtract VY - VX |
| 8XYE | Shift left |
| 9XY0 | Skip if VX != VY |
| ANNN | Set index register |
| BNNN | Jump with offset |
| CXNN | Random byte & NN |
| DXYN | Draw sprite |
| EX9E | Skip if key is pressed |
| EXA1 | Skip if key is not pressed |
| FX07 | Get delay timer |
| FX0A | Wait for key press |
| FX15 | Set delay timer |
| FX18 | Set sound timer |
| FX1E | Add VX to I |
| FX29 | Font character lookup |
| FX33 | Binary coded decimal conversion |
| FX55 | Store V0–VX in memory |
| FX65 | Load V0–VX from memory |
