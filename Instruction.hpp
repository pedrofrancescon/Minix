//
//  Instruction.hpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 14/06/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#ifndef Instruction_hpp
#define Instruction_hpp

#define TEXT_START_POS 0x20

#include <iostream>
#include <sstream>
#include <fstream>

#include "Binary.hpp"
#include "Definitions.hpp"

#include <vector>

string GetRegStr(char reg, bool w);

class Instruction
{
private:
    
    string str[3];
    
    int pos; //position of instruction in file
    
    /*-----------------------------------*/
    
    void SetBinary(int pc);
    
    void SetOpcode(char *binary);
    void SetD(char *binary);
    void SetW(char *binary);
    void SetMod(char *binary);
    void SetReg(char *binary);
    void SetRm(char *binary);
    void SetSW(char *binary);
    
public:
    
    char *binary; // binary of one instruction only
    char size;
    
    unsigned char opcode;
    bool d;
    bool w;
    char sw;
    
    char mod;
    char reg;
    char rm;
    
    char16_t data;
    tuple<vector<regs>, char16_t> ea; // Effective Address
    
    /*-----------------------------------*/
    
    Instruction(char *binary, int pc);
    
    int GetInstructionSize();
    void Print();
};

#endif /* Instruction_hpp */
