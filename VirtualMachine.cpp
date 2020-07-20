//
//  VirtualMachine.cpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 19/07/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#include "VirtualMachine.hpp"
#include "Binary.hpp"


VirtualMachine::VirtualMachine(char * file, ifstream::pos_type file_size)
{
    this->text_size = Binary2Dec(string(file,file_size), 0x8, 4);
    this->text = &(file[TEXT_START_POS]);
    
    this->data_size = Binary2Dec(string(file,file_size), 0xC, 4);
    this->data = &(file[TEXT_START_POS+text_size]);
    
    registers[sp] = 0xffdc;
    this->memory = new char16_t [registers[sp] + 2];
}

void VirtualMachine::Disassemble(bool print_result)
{
    int pc = 0;
    
    while (pc < text_size)
    {
        Instruction instruction (text, pc);
        
        instructions[pc] = instruction;
        
        if (print_result)
        {
            cout << hex << setfill('0') << setw(4) << pc << ":   ";
            instruction.Print();
        }
        
        pc += instruction.GetInstructionSize();
    }
}

void VirtualMachine::Execute()
{
    
    char16_t i = 0x0;
    
    while(i < text_size)
    {
        
        // MOV: 1011 w reg data data if w=1
        if (instructions[i].opcode == 0xB)
        {
            registers[instructions[i].reg] = instructions[i].data;
        }
        
        // MOV: 100010dw mod reg r/m
        if (instructions[i].opcode == 0x22)
        {
            if (instructions[i].d)
                registers[instructions[i].reg] = registers[instructions[i].rm];
            else
                registers[instructions[i].rm] = registers[instructions[i].reg];
        }
        
        // PUSH: 01010 reg
        if (instructions[i].opcode == 0xA)
        {
            memory[registers[sp]] = registers[instructions[i].reg];
            registers[sp] -= 2;
        }
        
        // INT: 11001101 type
        if (instructions[i].opcode == 0xCD)
        {
            char s_call_type = data[registers[bx]+2];
            
            if (s_call_type == EXIT)
            {
                return;
            }
            
            if (s_call_type == WRITE)
            {
                char16_t m_add = data[registers[bx]+0xa] + (data[registers[bx]+0xb] << 8);
                char16_t m_size = data[registers[bx]+0x6] + (data[registers[bx]+0x7] << 8);
                cout << Binary2Text(data, m_add, m_size);
            }
        }
        
        // ADD: 000000dw mod reg r/m
        if (instructions[i].opcode == 0)
        {
            
        }
        
        // ADD: 100000sw mod 000 r/m data data if sw = 01
        // SUB: 100000sw mod 101 r/m data data
        if (instructions[i].opcode == 0x20)
        {
            if (instructions[i].reg == 0x0) // ADD
            {
                data[get<1>(instructions[i].ea)] += instructions[i].data;
            }
            
            if (instructions[i].reg == 0x5) // SUB
            {
                data[get<1>(instructions[i].ea)] -= instructions[i].data;
            }
        }
        
        // JMP: 11101001 disp-low disp-high
        if (instructions[i].opcode == 0xe9)
        {
            i = instructions[i].data;
            continue;
        }
        
        // CALL: 11101000 disp-low disp-high
        if (instructions[i].opcode == 0xe8)
        {
            memory[registers[sp]] = i + instructions[i].size;
            registers[sp] -= 2;
            i = instructions[i].data;
            continue;
        }
        
        i += instructions[i].size;
        
    }
    
}
