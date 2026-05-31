#include <iostream>
#include "chip8.h"
#include "opcodes.h"

// clear
void op_00E0(chip8 &ch8){
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            ch8.setPixels(y,x, 0);
        }
    }
}

// jump
void op_1NNN(chip8 &ch8, uint16_t NNN){
    ch8.setPC(NNN);
}

// set VX
void op_6XNN(chip8 &ch8, uint8_t X, uint8_t NN){
    ch8.setVX(X, NN);
}

// add to VX
void op_7XNN(chip8 &ch8, uint8_t X, uint8_t NN){
    ch8.setVX(X,ch8.getVX(X) + NN);
}

// set I
void op_ANNN(chip8 &ch8, uint16_t NNN){
    ch8.setI(NNN);
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
            uint8_t currPixel = pixelRow & (0x80 >> j);
            // chip8 sprites are drawn using XOR
            uint8_t xorPixel = ch8.getPixels(yPOS + i, xPOS + j) ^ currPixel;
            if(!xorPixel && currPixel)
                ch8.setVX(0xF, 1); // VF flag is set when collision is detected
            ch8.setPixels(yPOS + i, xPOS +j, xorPixel);
        }
    }
}
