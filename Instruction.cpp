//
//  Instruction.cpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 14/06/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#include "Instruction.hpp"

Instruction::Instruction(char* binary, int pc)
{
    instruction_size = 0;
    
    SetOpcode(&binary[pc]);
}

void Instruction::SetOpcode(char* binary)
{
    
    // 000000dw mod reg r/m
    if (getOpcode6(binary) == 0)
    {
        cout << "add" << endl;
        instruction_size = 2 + SetMod(binary);
        return;
    }
    // ADD: 100000sw mod 000 r/m data data if sw = 01
    // CMP: 100000sw mod 111 r/m data data if sw = 01
    // SUB: 100000sw mod 101 r/m data data
    if (getOpcode6(binary) == 0x20 )
    {
        instruction_size = 3 + SetMod(binary);
        if (getReg(binary) == 0x0)
            cout << "add" << endl;
        else if (getReg(binary) == 0x7)
            cout << "cmp" << endl;
        else if (getReg(binary) == 0x5)
            cout << "sub" << endl;
        
        if (getSW(binary) == 0x1)
            instruction_size++;
        
        return;
    }
    // 001000dw mod 000 r/m
    if (getOpcode6(binary) == 0x8)
    {
        cout << "and" << endl;
        instruction_size = 2;
        return;
    }
    // 11101000 disp-low disp-high
    if (getOpcode8(binary) == 0xe8)
    {
        cout << "call" << endl;
        instruction_size = 3;
        return;
    }
    // PUSH: 11111111 mod 110 r/m
    // CALL: 11111111 mod 010 r/m
    if (getOpcode8(binary) == 0xff)
    {
        instruction_size = 2 + SetMod(binary);
        if (getReg(binary) == 0x6) //push
            cout << "push" << endl;
        else if (getReg(binary) == 0x2) //call
            cout << "call" << endl;
        return;
    }
    // 01001 reg
    if (getOpcode5(binary) == 0x9)
    {
        cout << "dec" << endl;
        instruction_size = 1;
        return;
    }
    // 11110100
    if (getOpcode8(binary) == 0xf4)
    {
        cout << "hlt" << endl;
        instruction_size = 1;
        return;
    }
    // 1110010w port
    if (getOpcode7(binary) == 0x72)
    {
        cout << "in" << endl;
        instruction_size = 2;
        return;
    }
    // 1110110w
    if (getOpcode7(binary) == 0x76)
    {
        cout << "in" << endl;
        instruction_size = 1;
        return;
    }
    // 11001101 type
    if (getOpcode8(binary) == 0xcd)
    {
        cout << "int" << endl;
        instruction_size = 2;
        return;
    }
    // 01110100 disp
    if (getOpcode8(binary) == 0x74)
    {
        cout << "je" << endl;
        instruction_size = 2;
        return;
    }
    // 01111100 disp
    if (getOpcode8(binary) == 0x7c)
    {
        cout << "jl" << endl;
        instruction_size = 2;
        return;
    }
    // 11101001 disp-low disp-high
    if (getOpcode8(binary) == 0xe9)
    {
        cout << "jmp" << endl;
        instruction_size = 3;
        return;
    }
    // 11101011 disp
    if (getOpcode8(binary) == 0xEB)
    {
        cout << "jmp" << endl;
        instruction_size = 2;
        return;
    }
    // 01110011 disp
    if (getOpcode8(binary) == 0x73)
    {
        cout << "jnb" << endl;
        instruction_size = 2;
        return;
    }
    // 01110101 disp
    if (getOpcode8(binary) == 0x75)
    {
        cout << "jne" << endl;
        instruction_size = 2;
        return;
    }
    // 01110101 disp
    if (getOpcode8(binary) == 0x7D)
    {
        cout << "jnl" << endl;
        instruction_size = 2;
        return;
    }
    // 10001101 mod reg r/m
    if (getOpcode8(binary) == 0x8D)
    {
        cout << "lea" << endl;
        instruction_size = 2 + SetMod(binary);
        return;
    }
    // 100010dw mod reg r/m
    if (getOpcode6(binary) == 0x22)
    {
        instruction_size = 2 + SetMod(binary);
        cout << "mov" << endl;
        return;
    }
    // 1011 w reg data data if w=1
    if (getOpcode4(binary) == 0xB)
    {
        cout << "mov" << endl;
        if ((binary[0] >> 3 & 0x1) == 0x1)
            instruction_size = 3;
        else
            instruction_size = 2;
        return;
    }
    // 000010dw mod reg r/m
    if (getOpcode6(binary) == 0x2)
    {
        cout << "or" << endl;
        instruction_size = 2;
        return;
    }
    // 01011 reg
    if (getOpcode5(binary) == 0xB)
    {
        cout << "pop" << endl;
        instruction_size = 1;
        return;
    }
    // 01010 reg
    if (getOpcode5(binary) == 0xA)
    {
        cout << "push" << endl;
        instruction_size = 1;
        return;
    }
    // 11000011
    if (getOpcode8(binary) == 0xC3)
    {
        cout << "ret" << endl;
        instruction_size = 1;
        return;
    }
    // 110100vw mod 100 r/m
    if (getOpcode6(binary) == 0x34)
    {
        cout << "shl" << endl;
        instruction_size = 2;
        return;
    }
    // NEG: 1111011w mod 011 r/m
    // TEST:  1111011w mod 000 r/m data data if w=1
    if (getOpcode7(binary) == 0x7B)
    {
        instruction_size = 2;
        if (getReg(binary) == 0x3) // neg
        {
            cout << "neg" << endl;
            return;
        }
        else if (getReg(binary) == 0x0) // test
        {
            cout << "test" << endl;
            (instruction_size)++;
            if (getW(binary) == 0x1)
                (instruction_size)++;
        }
        return;
    }
    // 001100dw mod reg r/m
    if (getOpcode6(binary) == 0xC)
    {
        cout << "xor" << endl;
        instruction_size = 2;
        return;
    }
    // 000110dw mod reg r/m
    if (getOpcode6(binary) == 0x6)
    {
        cout << "sbb" << endl;
        instruction_size = 2 + SetMod(binary);
        return;
    }
}


int Instruction::SetMod(char *binary)
{
    int size = 0;
    
    if (getMod(binary) == 0x0 && getRm(binary) == 0x6) // mod = 00 and r/m = 110
    {
        size += 2;
    }
    else if (getMod(binary) == 0x1) // mod = 01
        size += 1;
    else if (getMod(binary) == 0x2) // mod = 10
        size += 2;
    
    return size;
}

int Instruction::GetInstructionSize()
{
    return instruction_size;
}
