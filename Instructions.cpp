//
//  Instructions.cpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 09/06/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#include "Instructions.hpp"

int ModCheck(string byte2)
{
    int size = 0;
    
    if (byte2.substr(0,2) == "00" && byte2.substr(5,3) == "110") // mod = 00 and r/m = 110
    {
        size += 2;
    }
    else if (byte2.substr(0,2) == "01") // mod = 01
        size += 1;
    else if (byte2.substr(0,2) == "10") // mod = 10
        size += 2;
    
    return size;
}

void OpcodeCheck(string byte1, string byte2, int* instruc_byte_size)
{
    // 000000dw mod reg r/m
    if (byte1.substr(0,6) == "000000")
    {
        cout << "add" << endl;
        *instruc_byte_size = 2 + ModCheck(byte2);
        return;
    }
    // ADD: 100000sw mod 000 r/m data data if sw = 01
    // CMP: 100000sw mod 111 r/m data data if sw = 01
    // SUB: 100000sw mod 101 r/m data data
    if (byte1.substr(0,6) == "100000")
    {
        *instruc_byte_size = 3 + ModCheck(byte2);
        if (byte2.substr(2,3) == "000")
            cout << "add" << endl;
        else if (byte2.substr(2,3) == "111")
            cout << "cmp" << endl;
        else if (byte2.substr(2,3) == "101")
            cout << "sub" << endl;
        
        if (byte1.substr(6,2) == "01")
            (*instruc_byte_size)++;
        
        return;
    }
    // 001000dw mod 000 r/m
    if (byte1.substr(0,6) == "001000")
    {
        cout << "and" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 11101000 disp-low disp-high
    if (byte1.substr(0,8) == "11101000")
    {
        cout << "call" << endl;
        *instruc_byte_size = 3;
        return;
    }
    // PUSH: 11111111 mod 110 r/m
    // CALL: 11111111 mod 010 r/m
    if (byte1.substr(0,8) == "11111111")
    {
        *instruc_byte_size = 2 + ModCheck(byte2);
        if (byte2.substr(2,3) == "110") //push
            cout << "push" << endl;
        else if (byte2.substr(2,3) == "010") //call
            cout << "call" << endl;
        return;
    }
    // 01001 reg
    if (byte1.substr(0,5) == "01001")
    {
        cout << "dec" << endl;
        *instruc_byte_size = 1;
        return;
    }
    // 11110100
    if (byte1.substr(0,8) == "11110100")
    {
        cout << "hlt" << endl;
        *instruc_byte_size = 1;
        return;
    }
    // 1110010w port
    if (byte1.substr(0,7) == "1110010")
    {
        cout << "in" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 1110110w
    if (byte1.substr(0,7) == "1110110")
    {
        cout << "in" << endl;
        *instruc_byte_size = 1;
        return;
    }
    // 11001101 type
    if (byte1.substr(0,8) == "11001101")
    {
        cout << "int" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 01110100 disp
    if (byte1.substr(0,8) == "01110100")
    {
        cout << "je" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 01111100 disp
    if (byte1.substr(0,8) == "01111100")
    {
        cout << "jl" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 11101001 disp-low disp-high
    if (byte1.substr(0,8) == "11101001")
    {
        cout << "jmp" << endl;
        *instruc_byte_size = 3;
        return;
    }
    // 11101011 disp
    if (byte1.substr(0,8) == "11101011")
    {
        cout << "jmp" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 01110011 disp
    if (byte1.substr(0,8) == "01110011")
    {
        cout << "jnb" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 01110101 disp
    if (byte1.substr(0,8) == "01110101")
    {
        cout << "jne" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 01110101 disp
    if (byte1.substr(0,8) == "01111101")
    {
        cout << "jnl" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 10001101 mod reg r/m
    if (byte1.substr(0,8) == "10001101")
    {
        cout << "lea" << endl;
        *instruc_byte_size = 2 + ModCheck(byte2);
        return;
    }
    // 100010dw mod reg r/m
    if (byte1.substr(0,6) == "100010")
    {
        *instruc_byte_size = 2 + ModCheck(byte2);
        cout << "mov" << endl;
        return;
    }
    if (byte1.substr(0,4) == "1011")
    { // 1011 w reg data data if w=1
        cout << "mov" << endl;
        if (byte1.substr(4,1) == "1")
            *instruc_byte_size = 3;
        else
            *instruc_byte_size = 2;
        return;
    }
    // 000010dw mod reg r/m
    if (byte1.substr(0,6) == "000010")
    {
        cout << "or" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 01011 reg
    if (byte1.substr(0,5) == "01011")
    {
        cout << "pop" << endl;
        *instruc_byte_size = 1;
        return;
    }
    // 01010 reg
    if (byte1.substr(0,5) == "01010")
    {
        cout << "push" << endl;
        *instruc_byte_size = 1;
        return;
    }
    // 11000011
    if (byte1.substr(0,8) == "11000011")
    {
        cout << "ret" << endl;
        *instruc_byte_size = 1;
        return;
    }
    // 110100vw mod 100 r/m
    if (byte1.substr(0,6) == "110100")
    {
        cout << "shl" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // NEG: 1111011w mod 011 r/m
    // TEST:  1111011w mod 000 r/m data data if w=1
    if (byte1.substr(0,7) == "1111011")
    {
        *instruc_byte_size = 2;
        if (byte2.substr(2,3) == "011") // neg
        {
            cout << "neg" << endl;
            return;
        }
        else if (byte2.substr(2,3) == "000") // test
        {
            cout << "test" << endl;
            (*instruc_byte_size)++;
            if (byte1.substr(7,1) == "1")
                (*instruc_byte_size)++;
        }
        return;
    }
    // 001100dw mod reg r/m
    if (byte1.substr(0,6) == "001100")
    {
        cout << "xor" << endl;
        *instruc_byte_size = 2;
        return;
    }
    // 000110dw mod reg r/m
    if (byte1.substr(0,6) == "000110")
    {
        cout << "sbb" << endl;
        *instruc_byte_size = 2 + ModCheck(byte2);
        return;
    }
}
