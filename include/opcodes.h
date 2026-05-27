#include <iostream>
#include "chip8.h"

void op_00E0(chip8 &ch8);
void op_1NNN(chip8 &ch8, uint16_t NNN);
void op_6XNN(chip8 &ch8, uint8_t X, uint8_t NN);
void op_7XNN(chip8 &ch8, uint8_t X, uint8_t NN);
void op_ANNN(chip8 &ch8, uint16_t NNN);
void op_DXYN(chip8 &ch8, uint8_t X, uint8_t Y, uint8_t N);