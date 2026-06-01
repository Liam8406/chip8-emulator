#include <iostream>
#include "chip8.h"

void op_00E0(chip8 &ch8);
void op_00EE(chip8 &ch8);
void op_1NNN(chip8 &ch8, uint16_t NNN);
void op_2NNN(chip8 &ch8, uint16_t NNN);
void op_3XNN(chip8 &ch8, uint8_t X, uint8_t NN);
void op_4XNN(chip8 &ch8, uint8_t X, uint8_t NN);
void op_5XY0(chip8 &ch8, uint8_t X, uint8_t Y);
void op_6XNN(chip8 &ch8, uint8_t X, uint8_t NN);
void op_7XNN(chip8 &ch8, uint8_t X, uint8_t NN);
//-----Logical and arithmetic instructions-----
void op_8XY0(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XY0(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XY1(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XY2(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XY3(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XY4(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XY5(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XY6(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XY7(chip8 &ch8, uint8_t X, uint8_t Y);
void op_8XYE(chip8 &ch8, uint8_t X, uint8_t Y);
//---------------------------------------------
void op_9XY0(chip8 &ch8, uint8_t X, uint8_t Y);
void op_ANNN(chip8 &ch8, uint16_t NNN);
void op_BNNN(chip8 &ch8, uint16_t NNN);
void op_CXNN(chip8 &ch8, uint8_t X, uint8_t NN);
void op_DXYN(chip8 &ch8, uint8_t X, uint8_t Y, uint8_t N);
void op_EX9E(chip8 &ch8, uint8_t X);
void op_EXA1(chip8 &ch8, uint8_t X);
void op_FX07(chip8 &ch8, uint8_t X);
void op_FX15(chip8 &ch8, uint8_t X);
void op_FX18(chip8 &ch8, uint8_t X);
void op_FX1E(chip8 &ch8, uint8_t X);
void op_FX0A(chip8  &ch8, uint8_t X);
void op_FX29(chip8 &ch8, uint8_t X);
void op_FX33(chip8 &ch8, uint8_t X);
void op_FX55(chip8 &ch8, uint8_t X);
void op_FX65(chip8 &ch8, uint8_t X);
