#include "chip8.h"
#include "opcodes.h"
#define INST ((opcode & 0xF000) >> 12)
#define X ((opcode & 0x0F00) >> 8)
#define Y ((opcode & 0x00F0) >> 4)
#define N (opcode & 0x000F)
#define NN (opcode & 0x00FF)
#define NNN (opcode & 0x0FFF)

uint8_t fontset[FONT_SIZE] = 
{
0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
0x20, 0x60, 0x20, 0x20, 0x70, // 1
0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
0x90, 0x90, 0xF0, 0x10, 0x10, // 4
0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
0xF0, 0x10, 0x20, 0x40, 0x40, // 7
0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
0xF0, 0x90, 0xF0, 0x90, 0x90, // A
0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
0xF0, 0x80, 0x80, 0x80, 0xF0, // C
0xE0, 0x90, 0x90, 0x90, 0xE0, // D
0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

uint8_t chip8::getRAM(uint16_t pos)
{
    return RAM[pos];
}

void chip8::setRAM(uint16_t pos, uint8_t val)
{
    RAM[pos] = val;
}

uint8_t chip8::getPixels(int y, int x)
{
    return pixels[y][x];
}

void chip8::setPixels(int y, int x, uint8_t val)
{
    pixels[y][x] = val;
}

uint16_t chip8::getPC()
{
    return PC;
}

void chip8::setPC(uint16_t loc)
{
    PC = loc;
}

uint16_t chip8::getI()
{
    return I;
}

void chip8::setI(uint16_t newI)
{
    I = newI;
}

uint8_t chip8::getVX(uint8_t x)
{
    return V[x];
}

void chip8::setVX(uint8_t x, uint8_t val)
{
    V[x] = val;
}

uint16_t chip8::getOpcode()
{
    return opcode;
}

void chip8::fetch()
{
    // combine two bytes into one 16 bit opcode
    opcode = RAM[PC] << 8 | RAM[PC+1];
    PC += 2;
    
}

void chip8::decode()
{
    switch (INST)
    {
    // clear
    case 0:
        op_00E0(*this);
        break;
    // jump
    case 1:
        op_1NNN(*this, NNN);
        break;
    // set VX
    case 6:
        op_6XNN(*this, X, NN);
        break;
    // add to VX
    case 7:
        op_7XNN(*this, X, NN);
        break;
    // set I
    case 0xA:
        op_ANNN(*this, NNN);
        break;
    // draw
    case 0xD:
        op_DXYN(*this, X, Y, N);
        break;
    default:
        break;
    }
}
