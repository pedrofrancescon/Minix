//
//  Instruction.hpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 14/06/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#ifndef Instruction_hpp
#define Instruction_hpp

#include <iostream>
#include <sstream>
#include <fstream>

#include "Binary.hpp"

using namespace std;

inline unsigned char getOpcode4(char* binary) { return binary[0] >> 4 & 0xf; }
inline unsigned char getOpcode5(char* binary) { return binary[0] >> 3 & 0x1f; }
inline unsigned char getOpcode6(char* binary) { return binary[0] >> 2 & 0x3f; }
inline unsigned char getOpcode7(char* binary) { return binary[0] >> 1 & 0x7f; }
inline unsigned char getOpcode8(char* binary) { return binary[0] & 0xff; }

inline unsigned char getD(char* binary) { return binary[0] >> 1 & 0x1; }
inline unsigned char getW(char* binary) { return binary[0] & 0x1; }
inline unsigned char getSW(char* binary) { return binary[0] & 0x3; }

inline unsigned char getMod(char* binary) { return binary[1] >> 6 & 0x3; }
inline unsigned char getReg(char* binary) { return binary[1] >> 3 & 0x7; }
inline unsigned char getRm(char* binary) { return binary[1] & 0x7; }

enum Reg {
    ax = 0,     al = 0,
    cx = 1,     cl = 1,
    dx = 2,     dl = 2,
    bx = 3,     bl = 3,
    sp = 4,     ah = 4,
    bp = 5,     cd = 5,
    si = 6,     dh = 6,
    di = 7,     bh = 7,
};

class Instruction
{
private:
    
    char *instruction_binary;
    
    char instruction_size;
    
    unsigned char opcode;
    bool d;
    bool w;
    char sw;
    
    char mod;
    char reg;
    char rm;
    
    char data;
    
    /*-----------------------------------*/
    
    void SetOpcode(char *binary);
    void SetD(char *binary);
    void SetW(char *binary);
    void SetMod(char *binary);
    void SetReg(char *binary);
    void SetRm(char *binary);
    void SetSW(char *binary);
    
public:
    
    Instruction(char *binary, int pc);
    
    int GetInstructionSize();
};

#endif /* Instruction_hpp */
