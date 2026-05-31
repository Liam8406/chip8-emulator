#pragma once
#include <iostream>
#include <cstdint>
#include <vector>

const int WIDTH = 64;
const int HEIGHT = 32;

const unsigned int FONT_SIZE = 0x50;

class chip8{
    private:
        uint8_t RAM[4096];
        uint8_t pixels[HEIGHT][WIDTH]; 
        uint16_t PC;
        uint16_t I; 
        std::vector<uint16_t> stack;
        uint8_t delay;
        uint8_t soundTimer;
        uint8_t V[16];
        uint16_t opcode;
    public:
        uint8_t getRAM(uint16_t pos);
        void setRAM(uint16_t pos, uint8_t val);
        uint8_t getPixels(int y, int x);
        void setPixels(int y, int x, uint8_t val);
        uint16_t getPC();
        void setPC(uint16_t loc);
        uint16_t getI();
        void setI(uint16_t newI);
        uint8_t getVX(uint8_t x);
        void setVX(uint8_t x, uint8_t val);
        uint16_t getOpcode();
        void fetch();
        void decode();


};
