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
    size = 0;
    d = 0;
    pos = pc;
    
    SetOpcode(&binary[pc]);
    SetBinary(pc);
    
    cout << str[0];
    
    if (str[1] != "")
        cout << " " << str[1];
    if (str[2] != "")
        cout << ", " << str[2];
    
    cout << endl;
    
    //cout << str[0] << " " << str[1] << ", " << str[2] << endl;
}

void Instruction::SetOpcode(char* binary)
{
    // 100010dw mod reg r/m
    if (getOpcode6(binary) == 0x22)
    {
        size = 2;
        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        
        str[0] += "mov";
        return;
    }
    // 1011 w reg data data if w=1
    if (getOpcode4(binary) == 0xB)
    {
        str[0] += "mov";
        opcode = getOpcode4(binary);
        
        reg = binary[0] & 0x7;
        w = binary[0] >> 3 & 0x1;
        
        str[1] = GetRegStr(reg, w);
        
        if (w == 0x1)
        {
            data[1] = Binary2Hex(binary[1]);
            data[0] = Binary2Hex(binary[2]);
            size = 3;
        }
        else
        {
            data[1] = Binary2Hex(binary[1]);
            data[0] = "";
            size = 2;
        }
        
        str[2] = StrFromData();
        
        return;
    }
    // 000000dw mod reg r/m
    if (getOpcode6(binary) == 0)
    {
        size = 2;
        
        str[0] += "add";
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
        size = 3;
        
        opcode = getOpcode6(binary);
        SetMod(binary);
        SetRm(binary);
        SetSW(binary);
        //SetReg(binary);
        
        if (getReg(binary) == 0x0)
            str[0] += "add";
        else if (getReg(binary) == 0x7)
            str[0] += "cmp";
        else if (getReg(binary) == 0x5)
            str[0] += "sub";
        
        if (getSW(binary) == 0x1)
        {
            data[1] = Binary2Hex(binary[2]);
            data[0] = Binary2Hex(binary[3]);
            size++;
        }
        else
        {
            data[1] = Binary2Hex(binary[2]);
            data[0] = "";
        }
        
        str[2] = StrFromData();
        
        return;
    }
    // 001000dw mod 000 r/m
    if (getOpcode6(binary) == 0x8)
    {
        str[0] += "and";

        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        
        size = 2;
        return;
    }
    // 11101000 disp-low disp-high
    if (getOpcode8(binary) == 0xe8)
    {
        str[0] = "call";
        str[1] = Binary2Hex(binary[2]) + Binary2Hex(binary[1]);
        opcode = getOpcode8(binary);
        size = 3;
        return;
    }
    // PUSH: 11111111 mod 110 r/m
    // CALL: 11111111 mod 010 r/m
    if (getOpcode8(binary) == 0xff)
    {
        size = 2;
        opcode = getOpcode8(binary);
        SetMod(binary);
        //SetReg(binary);
        SetRm(binary);
        if (getReg(binary) == 0x6) //push
            str[0] += "push";
        else if (getReg(binary) == 0x2) //call
            str[0] += "call";
        return;
    }
    // 01001 reg
    if (getOpcode5(binary) == 0x9)
    {
        str[0] += "dec";
        reg = binary[0]&0x7;
        str[1] = GetRegStr(reg, 1);
        opcode = getOpcode5(binary);
        size = 1;
        return;
    }
    // 11110100
    if (getOpcode8(binary) == 0xf4)
    {
        str[0] += "hlt";
        opcode = getOpcode5(binary);
        size = 1;
        return;
    }
    // 1110010w port
    if (getOpcode7(binary) == 0x72)
    {
        str[0] += "in";
        opcode = getOpcode7(binary);
        SetW(binary);
        size = 2;
        return;
    }
    // 1110110w
    if (getOpcode7(binary) == 0x76)
    {
        str[0] += "in";
        opcode = getOpcode7(binary);
        SetW(binary);
        size = 1;
        return;
    }
    // 11001101 type
    if (getOpcode8(binary) == 0xcd)
    {
        str[0] += "int";
        str[1] = Binary2Hex(binary[1]);
        opcode = getOpcode8(binary);
        size = 2;
        return;
    }
    // 01110100 disp
    if (getOpcode8(binary) == 0x74)
    {
        str[0] += "je";
        str[1] = Binary2Hex(binary[1]);
        opcode = getOpcode8(binary);
        size = 2;
        return;
    }
    // 01111100 disp
    if (getOpcode8(binary) == 0x7c)
    {
        str[0] += "jl";
        str[1] = Binary2Hex(binary[1]);
        opcode = getOpcode8(binary);
        size = 2;
        return;
    }
    // 11101001 disp-low disp-high
    if (getOpcode8(binary) == 0xe9)
    {
        size = 3;
        
        char16_t current_pos = (pos - TEXT_START_POS) + size;
        unsigned char disp_low = binary[1];
        char16_t disp_high = binary[2] << 8;
        char16_t result = current_pos + disp_low + disp_high;

        str[0] += "jmp";
        
        str[1] = Binary2Hex((result&0xff00) >> 8);
        str[1] += Binary2Hex(result&0x00ff);
        
        opcode = getOpcode8(binary);
        
        return;
    }
    // 11101011 disp
    if (getOpcode8(binary) == 0xEB)
    {
        size = 2;
        
        char16_t current_pos = (pos - TEXT_START_POS) + size;
        char disp = binary[1];
        char16_t result = current_pos + disp;
        
        str[0] += "jmp short";
        
        str[1] = Binary2Hex((result&0xff00) >> 8);
        str[1] += Binary2Hex(result&0x00ff);
        
        opcode = getOpcode8(binary);
        
        return;
    }
    // 01110011 disp
    if (getOpcode8(binary) == 0x73)
    {
        str[0] += "jnb";
        str[1] = Binary2Hex(binary[1]);
        opcode = getOpcode8(binary);
        size = 2;
        return;
    }
    // 01110101 disp
    if (getOpcode8(binary) == 0x75)
    {
        str[0] += "jne";
        str[1] = Binary2Hex(binary[1]);
        opcode = getOpcode8(binary);
        size = 2;
        return;
    }
    // 01110101 disp
    if (getOpcode8(binary) == 0x7D)
    {
        str[0] += "jnl";
        str[1] = Binary2Hex(binary[1]);
        opcode = getOpcode8(binary);
        size = 2;
        return;
    }
    // 10001101 mod reg r/m
    if (getOpcode8(binary) == 0x8D)
    {
        str[0] += "lea";
        size = 2;
        d = 1;
        opcode = getOpcode8(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        return;
    }
    // 000010dw mod reg r/m
    if (getOpcode6(binary) == 0x2)
    {
        str[0] += "or";
        opcode = getOpcode6(binary);
        SetD(binary);
        SetW(binary);
        SetMod(binary);
        SetReg(binary);
        SetRm(binary);
        size = 2;
        return;
    }
    // 01011 reg
    if (getOpcode5(binary) == 0xB)
    {
        str[0] = "pop";
        reg = binary[0]&0x7;
        str[1] = GetRegStr(reg, 1);
        opcode = getOpcode5(binary);
        size = 1;
        return;
    }
    // 01010 reg
    if (getOpcode5(binary) == 0xA)
    {
        str[0] = "push";
        reg = binary[0]&0x7;
        str[1] = GetRegStr(reg, 1);
        opcode = getOpcode5(binary);
        size = 1;
        return;
    }
    // 11000011
    if (getOpcode8(binary) == 0xC3)
    {
        str[0] = "ret";
        opcode = getOpcode8(binary);
        size = 1;
        return;
    }
    // 110100vw mod 100 r/m
    if (getOpcode6(binary) == 0x34)
    {
        str[0] += "shl";
        size = 2;
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
        size = 2;
        opcode = getOpcode7(binary);
        SetW(binary);
        SetMod(binary);
        SetRm(binary);
        if (getReg(binary) == 0x3) // neg
        {
            str[0] += "neg";
            return;
        }
        else if (getReg(binary) == 0x0) // test
        {
            str[0] += "test";
            size++;
            
            data[1] = Binary2Hex(binary[2]);
            data[0] = "";
            
            if (w == 0x1)
            {
                data[0] = Binary2Hex(binary[3]);
                size++;
            }
        }
        
        str[2] = StrFromData();
        
        return;
    }
    // 001100dw mod reg r/m
    if (getOpcode6(binary) == 0xC)
    {
        str[0] += "xor";
        size = 2;
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
        str[0] += "sbb";
        size = 2;
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
    
    if (mod == 0x3) // mod = 11
    {
        str[d ? 2 : 1] = GetRegStr(getRm(binary), getW(binary));
    }
    else if (mod == 0x0 && getRm(binary) == 0x6) // mod = 00 and r/m = 110
    {
        data[1] = Binary2Hex(binary[2]);
        data[0] = Binary2Hex(binary[3]);
        size += 2;
    }
    else if (mod == 0x1) // mod = 01
    {
        data[1] = Binary2Hex(binary[2]);
        data[0] = "";
        size += 1;
    }
    else if (mod == 0x2) // mod = 10
    {
        data[1] = Binary2Hex(binary[2]);
        data[0] = Binary2Hex(binary[3]);
        size += 2;
    }
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
    
    int str_pos = d ? 1 : 2;
    
    str[str_pos] = GetRegStr(reg, w);
}

void Instruction::SetRm(char *binary)
{
    rm = getRm(binary);
    
    if (getMod(binary) == 0x3)
        return;
    
    int str_pos = d ? 2 : 1;
    
    switch (rm) {
        case 0x0:
            str[str_pos] = "[bx+si";
            break;
        case 0x1:
            str[str_pos] = "[bx+di";
            break;
        case 0x2:
            str[str_pos] = "[bp+si";
            break;
        case 0x3:
            str[str_pos] = "[bp+di";
            break;
        case 0x4:
            str[str_pos] = "[si";
            break;
        case 0x5:
            str[str_pos] = "[di";
            break;
        case 0x6:
            str[str_pos] = "[bp";
            break;
        case 0x7:
            str[str_pos] = "[bx";
            break;
    }
    
    if (StrFromData() != "")
    {
        str[str_pos] += "+" + StrFromData() + "]";
    }
    else
    {
        str[str_pos] += "]";
    }
}

void Instruction::SetSW(char *binary)
{
    sw = getSW(binary);
}

int Instruction::GetInstructionSize()
{
    return size;
}

void Instruction::SetBinary(int pc)
{
    binary = new char [size];

    for (int i = 0; i < size; i++)
    {
        binary[i] = binary[pc+i];
    }
}



string GetRegStr(char reg, bool w)
{
    switch (reg)
    {
        case 0x0:
            return w ? "ax" : "al";
        case 0x1:
            return w ? "cx" : "cl";
        case 0x2:
            return w ? "dx" : "dl";
        case 0x3:
            return w ? "bx" : "bl";
        case 0x4:
            return w ? "sp" : "ah";
        case 0x5:
            return w ? "bp" : "cd";
        case 0x6:
            return w ? "si" : "dh";
        case 0x7:
            return w ? "di" : "bh";
    }
    
    return "";
}

string Instruction::StrFromData()
{
    return data[0] + data[1];
}

