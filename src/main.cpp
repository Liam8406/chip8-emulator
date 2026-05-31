#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "chip8.h"

void loadROM(const std::string& filename, chip8 &ch8) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "error openning ROM file" << std::endl;
        return;
    }

    uint16_t currPos = 0x200; 
    char byteBuffer;

    while (file.read(&byteBuffer, 1)) {
        if (currPos >= 4096) {
            std::cerr << "ROM is too large for chip8 memory" << std::endl;
            file.close();
            return;
        }

        uint8_t val = static_cast<uint8_t>(byteBuffer);
        ch8.setRAM(currPos, val);

        currPos++;
    }

    std::cout << "loaded bytes into RAM successfully" << std::endl;
    file.close();
}

void drawScreen(chip8 &ch8){
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            if(ch8.getPixels(y, x) == 0)
                std::cout << " ";
            else
                std::cout << "#";
        }
        std::cout << std::endl;
    }
}

int main(){
    chip8 ch8;
    loadROM("roms/IBM Logo.ch8", ch8);
    ch8.setPC(0x200);
    
        for(int i = 0; i < 4096; i++){
            ch8.fetch();
            int toInt = ch8.getOpcode();
            std::cout << std::hex << toInt << std::endl;
            ch8.decode();
        }
        drawScreen(ch8);

    return 0;
}