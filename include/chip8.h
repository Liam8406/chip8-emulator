#pragma once
#include <iostream>
#include <cstdint>
#include <vector>

const int WIDTH = 64;
const int HEIGHT = 32;
const int SCALE = 10;

const unsigned int FONT_SIZE = 0x50;

class chip8{
    private:
        uint8_t RAM[4096];
        uint8_t pixels[HEIGHT][WIDTH]; 
        bool drawFlag;
        uint16_t PC;
        uint16_t I; 
        std::vector<uint16_t> stack;
        uint8_t delay;
        uint8_t soundTimer;
        uint8_t V[16];
        uint16_t opcode;
        bool keys[16];
    public:
        chip8();
        uint8_t getRAM(uint16_t pos);
        void setRAM(uint16_t pos, uint8_t val);
        uint8_t getPixels(int y, int x);
        void setPixels(int y, int x, uint8_t val);
        bool getDrawFlag();
        void setDrawFlag(bool flag);
        uint16_t getPC();
        void setPC(uint16_t loc);
        uint16_t getI();
        void setI(uint16_t newI);
        void pushStack(uint16_t val);
        uint16_t popStack();
        uint8_t getDelay();
        void setDelay(uint8_t val);
        uint8_t getSoundTimer();
        void setSoundTimer(uint8_t val);
        uint8_t getVX(uint8_t x);
        void setVX(uint8_t x, uint8_t val);
        uint16_t getOpcode();
        bool getKeyState(uint8_t key);
        void setKeyState(uint8_t key, bool isPressed);
        void updateTimers();
        void fetch();
        void decode();
};
