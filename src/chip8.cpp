#include "chip8.h"

uint8_t chip8::getRAM(uint8_t pos)
{
    return RAM[pos];
}

void chip8::setRAM(uint8_t pos, uint8_t val)
{
    RAM[pos] = val;
}

uint8_t chip8::getPixels(int x, int y)
{
    return pixels[x][y];
}

void chip8::setPixels(int x, int y, uint8_t val)
{
    pixels[x][y] = val;
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

void chip8::fetch()
{
    // combine two bytes into one 16 bit opcode
    opcode = RAM[PC] << 8 | RAM[PC+1];
    PC += 2;
    
}

void chip8::decode()
{
    return;
}
