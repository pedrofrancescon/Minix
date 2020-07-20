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
}

void VirtualMachine::Disassemble(bool print_result)
{
    int pc = 0;
    
    while (pc < text_size)
    {
        Instruction instruction (text, pc);
        
        instructions.push_back(instruction);
        
        if (print_result)
        {
            cout << hex << setfill('0') << setw(4) << pc << ":   ";
            instruction.Print();
        }
        
        pc += instruction.GetInstructionSize();
    }
}

void VirtualMachine::Interpret()
{
    for(std::vector<Instruction>::iterator it = instructions.begin(); it != instructions.end(); ++it) {
        
        // MOV: 1011 w reg data data if w=1
        if (it->opcode == 0xB)
        {
            registers[it->reg] = it->data;
        }
        
        // MOV: 100010dw mod reg r/m
        if (it->opcode == 0x22)
        {
            if (it->d)
                registers[it->reg] = registers[it->rm];
            else
                registers[it->rm] = registers[it->reg];
        }
        
        // INT: 11001101 type
        if (it->opcode == 0xCD)
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
        
        // SUB: 100000sw mod 101 r/m data data
        if (it->opcode == 0x20)
        {
            
            if (it->reg == 0x5) // SUB
            {
                data[get<1>(it->ea)] -= it->data;
            }
        }
        
        
    }
    
    
}
