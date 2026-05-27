#include <iostream>
#include "chip8.h"

void clear(chip8 &ch8){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            ch8.setPixels(i,j, 0);
        }
    }
}

void jump(chip8 &ch8, uint16_t NNN){
    ch8.setPC(NNN);
}

void setVX(chip8 &ch8, uint8_t x, uint8_t NN){
    ch8.setVX(x, NN);
}

void addVX(chip8 &ch8, uint8_t x, uint8_t NN){
    ch8.setVX(x,ch8.getVX(x) + NN);
}

void setI(chip8 &ch8, uint16_t NNN){
    ch8.setI(NNN);
}

void draw(chip8 &ch8, uint8_t X, uint8_t Y, uint8_t N){
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
            uint8_t xorPixel = ch8.getPixels(xPOS + j, yPOS + i) ^ currPixel;
            if(!xorPixel && currPixel)
                ch8.setVX(0xF, 1); // VF flag is set when collision is detected
            ch8.setPixels(xPOS + j, yPOS + i, xorPixel);
        }
    }
}
