# CHIP-8 Emulator

A CHIP-8 emulator written in C++ as a systems programming learning project.

The goal of this project is to better understand how emulators work internally by building one from scratch and implementing the architecture step by step.

This project follows the TobiasVL CHIP-8 guide while implementing everything manually.

## Current Progress

Implemented so far:
- 4KB memory
- CHIP-8 fontset
- Registers, stack, PC and index register
- Opcode fetch cycle
- Basic opcode decoder
- Basic opcode implementations
- 64x32 display buffer
- XOR sprite drawing
- Collision flag handling (VF)

## Implemented Opcodes

| Opcode | Description |
|--------|-------------|
| 00E0 | Clear screen |
| 1NNN | Jump |
| 6XNN | Set VX |
| 7XNN | Add to VX |
| ANNN | Set index register |
| DXYN | Draw sprite |

## Project Structure

```txt
chip8-emulator/
├── include/
├── src/
├── roms/
├── screenshots/
```