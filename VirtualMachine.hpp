//
//  VirtualMachine.hpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 19/07/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#ifndef VirtualMachine_hpp
#define VirtualMachine_hpp

#include "Instruction.hpp"
#include <vector>

enum regs {ax, cx, dx, bx, sp, bp, si, di};

class VirtualMachine
{

private:
    
    char16_t registers[8];
    
    vector<Instruction> instructions;
    
    char * file;
    ifstream::pos_type file_size;
    
    int text_size;
    int data_size;
    
    int pc;
    
public:
    
    VirtualMachine(char * file, ifstream::pos_type file_size);
    
    void Disassemble(bool print_result);
    void Interpret();
    
};

#endif /* VirtualMachine_hpp */
