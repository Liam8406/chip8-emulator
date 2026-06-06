#include <iostream>
#include <random>
#include <Windows.h>
#include <conio.h> 
#include "chip8.h"
#include "opcodes.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distrib(0, 255);

// clear
void op_00E0(chip8 &ch8){
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            ch8.setPixels(y,x, 0);
        }
    }
}

// return from a subroutine
void op_00EE(chip8 &ch8)
{
    ch8.setPC(ch8.popStack());
}

// jump
void op_1NNN(chip8 &ch8, uint16_t NNN){
    ch8.setPC(NNN);
}

// call the subroutine
void op_2NNN(chip8 &ch8, uint16_t NNN)
{
    ch8.pushStack(ch8.getPC());
    ch8.setPC(NNN);
}

// skip if VX == NN
void op_3XNN(chip8 &ch8, uint8_t X, uint8_t NN)
{
    if(ch8.getVX(X) == NN)
        ch8.setPC(ch8.getPC() + 2);
}

// skip if VX != NN
void op_4XNN(chip8 &ch8, uint8_t X, uint8_t NN)
{
    if(ch8.getVX(X) != NN)
        ch8.setPC(ch8.getPC() + 2);
}

// skip if VX == VY
void op_5XY0(chip8 &ch8, uint8_t X, uint8_t Y)
{
    if(ch8.getVX(X) == ch8.getVX(Y))
        ch8.setPC(ch8.getPC() + 2);
}

// set VX
void op_6XNN(chip8 &ch8, uint8_t X, uint8_t NN){
    ch8.setVX(X, NN);
}

// add to VX
void op_7XNN(chip8 &ch8, uint8_t X, uint8_t NN){
    ch8.setVX(X,ch8.getVX(X) + NN);
}

//-----Logical and arithmetic instructions-----
// set
void op_8XY0(chip8 &ch8, uint8_t X, uint8_t Y)
{
    ch8.setVX(X, ch8.getVX(Y));
}

// binary OR
void op_8XY1(chip8 &ch8, uint8_t X, uint8_t Y)
{
    ch8.setVX(X, ch8.getVX(X) | ch8.getVX(Y));
    ch8.setVX(0xF, 0);
}

// binary AND
void op_8XY2(chip8 &ch8, uint8_t X, uint8_t Y)
{
    ch8.setVX(X, ch8.getVX(X) & ch8.getVX(Y));
    ch8.setVX(0xF, 0);
}

// logical XOR
void op_8XY3(chip8 &ch8, uint8_t X, uint8_t Y)
{
    ch8.setVX(X, ch8.getVX(X) ^ ch8.getVX(Y));
    ch8.setVX(0xF, 0);
}

// add VY to VX
void op_8XY4(chip8 &ch8, uint8_t X, uint8_t Y)
{
    uint16_t sum = ch8.getVX(X) + ch8.getVX(Y);
    if(sum > 255){
        ch8.setVX(X, sum % 256);
        ch8.setVX(0xF, 1);
    }
    else{
        ch8.setVX(X, (uint8_t)sum);
        ch8.setVX(0xF, 0);
    }
}

// subtract VX - VY
void op_8XY5(chip8 &ch8, uint8_t X, uint8_t Y)
{
    int sub = ch8.getVX(X) - ch8.getVX(Y);
    if(sub >= 0){
        ch8.setVX(X, sub);
        ch8.setVX(0xF, 1);
    }
    else{
        ch8.setVX(X, 256 + sub);
        ch8.setVX(0xF, 0);
    }
}

// put VY in VX and shift 1 bit right
void op_8XY6(chip8 &ch8, uint8_t X, uint8_t Y)
{
    bool lastBit = ch8.getVX(Y) & 0x1;
    ch8.setVX(X, ch8.getVX(Y) >> 1);
    if(lastBit)
        ch8.setVX(0xF, 1);
    else
        ch8.setVX(0xF, 0);
}

// subtract VY - VX
void op_8XY7(chip8 &ch8, uint8_t X, uint8_t Y)
{
    int sub = ch8.getVX(Y) - ch8.getVX(X);
    if(sub >= 0){
        ch8.setVX(X, sub);
        ch8.setVX(0xF, 1);
    }
    else{
        ch8.setVX(X, 256 + sub);
        ch8.setVX(0xF, 0);
    }
}

// put VY in VX and shift 1 bit to the left
void op_8XYE(chip8 &ch8, uint8_t X, uint8_t Y)
{
    bool lastBit = ch8.getVX(Y) & 0x80;
    ch8.setVX(X, ch8.getVX(Y) << 1);
    if(lastBit)
        ch8.setVX(0xF, 1);
    else
        ch8.setVX(0xF, 0);
}
//---------------------------------------------

// skip if VX != VY
void op_9XY0(chip8 &ch8, uint8_t X, uint8_t Y)
{
    if(ch8.getVX(X) != ch8.getVX(Y))
        ch8.setPC(ch8.getPC() + 2);
}

// set I
void op_ANNN(chip8 &ch8, uint16_t NNN){
    ch8.setI(NNN);
}

// jump with offset
void op_BNNN(chip8 &ch8, uint16_t NNN)
{
    ch8.setPC(NNN + ch8.getVX(0));
}

// set VX to a random 8 bit number & NN
void op_CXNN(chip8 &ch8, uint8_t X, uint8_t NN)
{
    uint8_t randNum = distrib(gen);

    ch8.setVX(X, randNum & NN);
}

// draw
void op_DXYN(chip8 &ch8, uint8_t X, uint8_t Y, uint8_t N){
    uint8_t xPOS = ch8.getVX(X) & 63;
    uint8_t yPOS = ch8.getVX(Y) & 31;

    ch8.setVX(0xF, 0);

    for(uint8_t i = 0; i < N; i++){
        if(yPOS + i >= 32)
            break;
        uint8_t pixelRow = ch8.getRAM(ch8.getI() + i);
        for(uint8_t j = 0; j < 8; j++){
            if(xPOS + j >= 64)
                break;
            // extract current sprite bit from most significant to least significant bit
            uint8_t currPixel = ((pixelRow & (0x80 >> j)) != 0);
            // chip8 sprites are drawn using XOR
            uint8_t xorPixel = ch8.getPixels(yPOS + i, xPOS + j) ^ currPixel;
            if(!xorPixel && currPixel)
                ch8.setVX(0xF, 1); // VF flag is set when collision is detected
            ch8.setPixels(yPOS + i, xPOS +j, xorPixel);
        }
    }
}

// skip inst if a key corresponding to the val of VX is pressed
void op_EX9E(chip8 &ch8, uint8_t X)
{
    if(ch8.getKeyState(ch8.getVX(X)))
        ch8.setPC(ch8.getPC()+2);
}

// skip inst if a key corresponding to the val of VX is not pressed
void op_EXA1(chip8 &ch8, uint8_t X)
{
    if(!ch8.getKeyState(ch8.getVX(X)))
        ch8.setPC(ch8.getPC()+2);
}

// set VX to the val of the delay timer
void op_FX07(chip8 &ch8, uint8_t X)
{
    ch8.setVX(X, ch8.getDelay());
}

// set the delay timer to the val of VX
void op_FX15(chip8 &ch8, uint8_t X)
{
    ch8.setDelay(ch8.getVX(X));
}

// set the sound timer to the val of VX
void op_FX18(chip8 &ch8, uint8_t X)
{
    ch8.setSoundTimer(ch8.getVX(X));
}

// add the val of VX to I
void op_FX1E(chip8 &ch8, uint8_t X)
{
    uint16_t sum = ch8.getI() + ch8.getVX(X);
    if(sum > 0x0FFF){
        ch8.setI(sum);
        ch8.setVX(0xF, 1);
    }
    else{
        ch8.setI(sum);
        ch8.setVX(0xF, 0);
    }
}

// block the next instructions and waits for a key to be pressed
void op_FX0A(chip8 &ch8, uint8_t X)
{
    for(uint8_t i = 0; i < 16; i++){
        if(ch8.getKeyState(i)){
            ch8.setVX(X, i);
            return;
        }
    }
    ch8.setPC(ch8.getPC() - 2);
}

// font char
void op_FX29(chip8 &ch8, uint8_t X){
    uint8_t chr = ch8.getVX(X) & 0x0F;
    ch8.setI(chr * 5);
}

// binary coded decimal conversion
void op_FX33(chip8 &ch8, uint8_t X)
{
    uint8_t toDec = ch8.getVX(X);
    int currI = ch8.getI() + 2;

    for(uint8_t i = 0; i < 3; i++){
        uint8_t tmp = toDec % 10; 
        ch8.setRAM(currI, tmp);
        currI--;
        toDec /= 10;
    }
}

// store and load memory from V0 - VX in I, I+1 - I+X
void op_FX55(chip8 &ch8, uint8_t X)
{
    for(uint8_t i = 0; i <= X; i++){
        ch8.setRAM(ch8.getI() + i, ch8.getVX(i));
    }
    ch8.setI(ch8.getI()+X+1);
}

// store and load memory from I - I+X in V0 - VX
void op_FX65(chip8 &ch8, uint8_t X)
{
    for(uint8_t i = 0; i <= X; i++)
        ch8.setVX(i, ch8.getRAM(ch8.getI() + i));
    ch8.setI(ch8.getI()+X+1);
}
