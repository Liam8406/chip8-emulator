#include "chip8.h"
#include "opcodes.h"
#define INST ((opcode & 0xF000) >> 12)
#define lastNib (opcode & 0x000F)
#define lastByte (opcode & 0x00FF)
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

chip8::chip8()
{
    for(uint8_t i = 0; i < 0x50; i++)
        RAM[i] = fontset[i];
}

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

void chip8::pushStack(uint16_t val)
{
    stack.push_back(val);
}

uint16_t chip8::popStack()
{
    if(stack.empty()){
        throw std::underflow_error("Stack is empty");
    }
    uint16_t top = stack.back();
    stack.pop_back();
    return top;
}

uint8_t chip8::getDelay()
{
    return delay;
}

void chip8::setDelay(uint8_t val)
{
    delay = val;
}

void chip8::setSoundTimer(uint8_t val)
{
    soundTimer = val;
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

bool chip8::getKeyState(uint8_t key)
{
    return keys[key];
}

void chip8::setKeyState(uint8_t key, bool isPressed)
{
    keys[key] = isPressed;
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
    case 0:
        switch (lastByte)
        {
        // clear
        case 0xE0:
            op_00E0(*this);
            break;
        // return from subroutine
        case 0xEE:
            op_00EE(*this);
        default:
            break;
        }
        break;
    // jump
    case 1:
        op_1NNN(*this, NNN);
        break;
    // call the subroutine
    case 2:
        op_2NNN(*this, NNN);
        break;
    // skip if VX == NN
    case 3:
        op_3XNN(*this, X, NN);
        break;
    // skip if VX != NN
    case 4:
        op_4XNN(*this, X, NN);
        break;
    // skip if VX == VY
    case 5:
        op_5XY0(*this, X, Y);
        break;
    // set VX
    case 6:
        op_6XNN(*this, X, NN);
        break;
    // add to VX
    case 7:
        op_7XNN(*this, X, NN);
        break;
    case 8:
        switch (lastNib)
        {
        //binary AND
        case 0:
            op_8XY0(*this, X, Y);
            break;
        //binary OR
        case 1:
            op_8XY1(*this, X, Y);
            break;
        case 2:
            op_8XY2(*this, X, Y);
            break;
        // logical XOR
        case 3:
            op_8XY3(*this, X, Y);
            break;
        // add VY to VX
        case 4:
            op_8XY4(*this, X, Y);
            break;
        // subtract VX - VY
        case 5:
            op_8XY5(*this, X, Y);
            break;
        // put VY in VX and shift 1 bit to the right
        case 6:
            op_8XY6(*this, X, Y);
            break;
        // subtract VY - VX
        case 7:
            op_8XY7(*this, X, Y);
            break;
        // put VY in VX and shift 1 bit to the left
        case 0xE:
            op_8XYE(*this, X, Y);
            break;
        default:
            break;
        }
        break;
    // skip if VX != VY
    case 9:
        op_9XY0(*this, X, Y);
        break;
    // set I
    case 0xA:
        op_ANNN(*this, NNN);
        break;
    // jump with offset
    case 0xB:
        op_BNNN(*this, NNN);
        break;
    // set VX to a random 8 bit number & NN
    case 0xC:
        op_CXNN(*this, X, NN);
        break;
    // draw
    case 0xD:
        op_DXYN(*this, X, Y, N);
        break;
    case 0xE:
        switch (lastByte)
        {
        // skip inst if a key corresponding to the val of VX is pressed
        case 0x9E:
            op_EX9E(*this, X);
            break;
        // skip inst if a key corresponding to the val of VX is not pressed
        case 0xA1:
            op_EXA1(*this, X);
            break;
        default:
            break;
        }
        break;
    case 0xF:
        switch (lastByte)
        {
        // set VX to the val of the delay timer
        case 0x07:
             op_FX07(*this, X);
            break;
        // block the next instructions and waits for a key to be pressed 
        case 0x0A:
            op_FX0A(*this, X);
            break;
        // set the delay timer to the val of VX
        case 0x15:
            op_FX15(*this, X);
            break;
        // set the sound timer to the val of VX
        case 0x18:
            op_FX18(*this, X);
            break;
        // add the val of VX to I
        case 0x1E:
            op_FX1E(*this, X);
            break;
        // font char 
        case 0x29:
            op_FX29(*this, X);
            break;
        // binary coded decimal conversion
        case 0x33:
            op_FX33(*this, X);
            break;
        // store and load memory from V0 - VX in I, I+1 - I+X
        case 0x55:
            op_FX55(*this, X);
            break;
        // store and load memory from I - I+X in V0 - VX 
        case 0x65:
            op_FX65(*this, X);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
