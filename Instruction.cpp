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
    
    instruction_binary = new char [instruction_size];

    for (int i = 0; i < instruction_size; i++)
    {
        instruction_binary[i] = binary[pc+i];
    }
}

void Instruction::SetOpcode(char* binary)
{
    // 100010dw mod reg r/m
    if (getOpcode6(binary) == 0x22)
    {
        instruction_size = 2;
        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        cout << "mov" << endl;
        return;
    }
    // 1011 w reg data data if w=1
    if (getOpcode4(binary) == 0xB)
    {
        cout << "mov" << endl;
        opcode = getOpcode4(binary);
        if ((binary[0] >> 3 & 0x1) == 0x1)
            instruction_size = 3;
        else
            instruction_size = 2;
        return;
    }
    // 000000dw mod reg r/m
    if (getOpcode6(binary) == 0)
    {
        instruction_size = 2;
        
        cout << "add" << endl;
        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        
        return;
    }
    // ADD: 100000sw mod 000 r/m data data if sw = 01
    // CMP: 100000sw mod 111 r/m data data if sw = 01
    // SUB: 100000sw mod 101 r/m data data
    if (getOpcode6(binary) == 0x20 )
    {
        instruction_size = 3;
        
        opcode = getOpcode6(binary);
        SetMod(binary);
        SetRm(binary);
        SetSW(binary);
        SetReg(binary);
        
        if (reg == 0x0)
            cout << "add" << endl;
        else if (reg == 0x7)
            cout << "cmp" << endl;
        else if (reg == 0x5)
            cout << "sub" << endl;
        
        if (getSW(binary) == 0x1)
            instruction_size++;
        
        return;
    }
    // 001000dw mod 000 r/m
    if (getOpcode6(binary) == 0x8)
    {
        cout << "and" << endl;

        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        
        instruction_size = 2;
        return;
    }
    // 11101000 disp-low disp-high
    if (getOpcode8(binary) == 0xe8)
    {
        cout << "call" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 3;
        return;
    }
    // PUSH: 11111111 mod 110 r/m
    // CALL: 11111111 mod 010 r/m
    if (getOpcode8(binary) == 0xff)
    {
        instruction_size = 2;
        opcode = getOpcode8(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        if (reg == 0x6) //push
            cout << "push" << endl;
        else if (reg == 0x2) //call
            cout << "call" << endl;
        return;
    }
    // 01001 reg
    if (getOpcode5(binary) == 0x9)
    {
        cout << "dec" << endl;
        opcode = getOpcode5(binary);
        instruction_size = 1;
        return;
    }
    // 11110100
    if (getOpcode8(binary) == 0xf4)
    {
        cout << "hlt" << endl;
        opcode = getOpcode5(binary);
        instruction_size = 1;
        return;
    }
    // 1110010w port
    if (getOpcode7(binary) == 0x72)
    {
        cout << "in" << endl;
        opcode = getOpcode7(binary);
        SetW(binary);
        instruction_size = 2;
        return;
    }
    // 1110110w
    if (getOpcode7(binary) == 0x76)
    {
        cout << "in" << endl;
        opcode = getOpcode7(binary);
        SetW(binary);
        instruction_size = 1;
        return;
    }
    // 11001101 type
    if (getOpcode8(binary) == 0xcd)
    {
        cout << "int" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 2;
        return;
    }
    // 01110100 disp
    if (getOpcode8(binary) == 0x74)
    {
        cout << "je" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 2;
        return;
    }
    // 01111100 disp
    if (getOpcode8(binary) == 0x7c)
    {
        cout << "jl" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 2;
        return;
    }
    // 11101001 disp-low disp-high
    if (getOpcode8(binary) == 0xe9)
    {
        cout << "jmp" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 3;
        return;
    }
    // 11101011 disp
    if (getOpcode8(binary) == 0xEB)
    {
        cout << "jmp" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 2;
        return;
    }
    // 01110011 disp
    if (getOpcode8(binary) == 0x73)
    {
        cout << "jnb" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 2;
        return;
    }
    // 01110101 disp
    if (getOpcode8(binary) == 0x75)
    {
        cout << "jne" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 2;
        return;
    }
    // 01110101 disp
    if (getOpcode8(binary) == 0x7D)
    {
        cout << "jnl" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 2;
        return;
    }
    // 10001101 mod reg r/m
    if (getOpcode8(binary) == 0x8D)
    {
        cout << "lea" << endl;
        instruction_size = 2;
        opcode = getOpcode8(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        return;
    }
    // 000010dw mod reg r/m
    if (getOpcode6(binary) == 0x2)
    {
        cout << "or" << endl;
        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        instruction_size = 2;
        return;
    }
    // 01011 reg
    if (getOpcode5(binary) == 0xB)
    {
        cout << "pop" << endl;
        opcode = getOpcode5(binary);
        instruction_size = 1;
        return;
    }
    // 01010 reg
    if (getOpcode5(binary) == 0xA)
    {
        cout << "push" << endl;
        opcode = getOpcode5(binary);
        instruction_size = 1;
        return;
    }
    // 11000011
    if (getOpcode8(binary) == 0xC3)
    {
        cout << "ret" << endl;
        opcode = getOpcode8(binary);
        instruction_size = 1;
        return;
    }
    // 110100vw mod 100 r/m
    if (getOpcode6(binary) == 0x34)
    {
        cout << "shl" << endl;
        instruction_size = 2;
        opcode = getOpcode6(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        return;
    }
    // NEG: 1111011w mod 011 r/m
    // TEST:  1111011w mod 000 r/m data data if w=1
    if (getOpcode7(binary) == 0x7B)
    {
        instruction_size = 2;
        opcode = getOpcode7(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        if (reg == 0x3) // neg
        {
            cout << "neg" << endl;
            return;
        }
        else if (reg == 0x0) // test
        {
            cout << "test" << endl;
            instruction_size++;
            
            if (w == 0x1)
                instruction_size++;
        }
        return;
    }
    // 001100dw mod reg r/m
    if (getOpcode6(binary) == 0xC)
    {
        cout << "xor" << endl;
        instruction_size = 2;
        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        return;
    }
    // 000110dw mod reg r/m
    if (getOpcode6(binary) == 0x6)
    {
        cout << "sbb" << endl;
        instruction_size = 2;
        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        return;
    }
}


void Instruction::SetMod(char *binary)
{
    mod = getMod(binary);
    
    if (mod == 0x0 && getRm(binary) == 0x6) // mod = 00 and r/m = 110
        instruction_size += 2;
    else if (mod == 0x1) // mod = 01
        instruction_size += 1;
    else if (mod == 0x2) // mod = 10
        instruction_size += 2;
}

void Instruction::SetD(char *binary)
{
    d = getD(binary);
}

void Instruction::SetW(char *binary)
{
    w = getW(binary);
}

void Instruction::SetReg(char *binary)
{
    reg = getReg(binary);
}

void Instruction::SetRm(char *binary)
{
    rm = getRm(binary);
}

void Instruction::SetSW(char *binary)
{
    sw = getSW(binary);
}

int Instruction::GetInstructionSize()
{
    return instruction_size;
}
