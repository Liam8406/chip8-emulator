#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "chip8.h"

// load a chip8 ROM into memory starting at address 0x200
void loadROM(const std::string& filename, chip8 &ch8) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "error openning ROM file" << std::endl;
        return;
    }

    // chip8 programs are conventionally loaded at memory address 0x200
    uint16_t currPos = 0x200; 
    char byteBuffer;

    // Read the ROM byte by byte and copy it into chip8 RAM
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

    file.close();
}

// translate keyboard keys into chip8 keypad values
uint16_t mapKeys(SDL_Keycode key){
    switch (key)
    {
    case SDLK_1:
        return 0x1;
    case SDLK_2:
        return 0x2;
    case SDLK_3:
        return 0x3;
    case SDLK_4:
        return 0xC;
    case SDLK_q:
        return 0x4;
    case SDLK_w:
        return 0x5;
    case SDLK_e:
        return 0x6;
    case SDLK_r:
        return 0xD;
    case SDLK_a:
        return 0x7;
    case SDLK_s:
        return 0x8;
    case SDLK_d:
        return 0x9;
    case SDLK_f:
        return 0xE;
    case SDLK_z:
        return 0xA;
    case SDLK_x:
        return 0x0;
    case SDLK_c:
        return 0xB;
    case SDLK_v:
        return 0xF;
    default:
        return 0xFFFF;
    }
}

// process SDL events and update the chip8 keypad state
void handleEvents(chip8 &ch8, bool &isRunning){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // mark keys as pressed
        if (event.type == SDL_KEYDOWN){
            uint16_t key = mapKeys(event.key.keysym.sym);
            if(key != 0xFFFF)
                ch8.setKeyState(key, 1);
        }
        // mark keys as released
        if (event.type == SDL_KEYUP){
            uint16_t key = mapKeys(event.key.keysym.sym);
            if(key != 0xFFFF)
                ch8.setKeyState(key, 0);
        }
    }
}

// render the chip8 framebuffer to the SDL window
void drawScreen(chip8 &ch8, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 125, 0, 125, 0);
    SDL_RenderClear(renderer);

    SDL_Rect pixelRect;
    pixelRect.w = SCALE;
    pixelRect.h = SCALE;

    // every chip8 pixel is scaled up to make them visible on modern displays
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (ch8.getPixels(y, x) != 0) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

                pixelRect.x = x * SCALE;
                pixelRect.y = y * SCALE;
                
                SDL_RenderFillRect(renderer, &pixelRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

int main() {
    chip8 ch8;

    // initialize SDL video and audio
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_AudioSpec wavSpec;
    uint32_t wavLength;
    uint8_t *wavBuffer;

    // create the SDL window and renderer
    if (SDL_CreateWindowAndRenderer(WIDTH * SCALE, HEIGHT * SCALE, 0, &window, &renderer) < 0) {
        std::cout << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // load the beep sound used by chip8 sound timer
    if(SDL_LoadWAV("assets/beep.wav", &wavSpec, &wavBuffer, &wavLength) == nullptr){
        std::cout << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    // open an audio device and prepare it for playback
    SDL_AudioDeviceID device = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
    SDL_PauseAudioDevice(device, 0);

    // Load the rom into chip8 RAM
    loadROM("roms/test6.ch8", ch8);
    bool isRunning = true;
    bool isBeeping = false;

    while(isRunning){
        // handle keyboard and window events
        handleEvents(ch8, isRunning);

        // execute multiple chip8 instructions every frame (change if you want)
        for(int i = 0; i < 10; i++)
        {
            ch8.fetch();
            ch8.decode();
        }


        // update the delay and sound timers
        ch8.updateTimers();

        // play beep sound while the sound timer running
        if(ch8.getSoundTimer() > 0 && !isBeeping){
            SDL_ClearQueuedAudio(device);
            SDL_QueueAudio(device, wavBuffer, wavLength);
            isBeeping = true;
        }
        if(ch8.getSoundTimer() == 0)
            isBeeping = false;

        // draw the current framebuffer contents
        drawScreen(ch8, renderer);

        // limit execution for about 60fps
        SDL_Delay(16);
    }

    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(wavBuffer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


