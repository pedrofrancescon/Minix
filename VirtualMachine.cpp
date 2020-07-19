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
    this->file = file;
    this->file_size = file_size;
    
    this->text_size = Binary2Dec(string(file,file_size), 8, 4);
    this->pc = TEXT_START_POS;
}

void VirtualMachine::Disassemble(bool print_result)
{
    while (pc < TEXT_START_POS + text_size)
    {
        Instruction instruction (file, pc);
        
        instructions.push_back(instruction);
        
        if (print_result)
        {
            cout << hex << setfill('0') << setw(4) << pc - TEXT_START_POS << ":   ";
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
    }
}
