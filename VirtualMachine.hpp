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
#include "Definitions.hpp"

#include <vector>

class VirtualMachine
{

private:
    
    char16_t registers[8];
    
    vector<Instruction> instructions;
    
    char * text;
    char * data;
    
    int text_size;
    int data_size;
    
public:
    
    VirtualMachine(char * file, ifstream::pos_type file_size);
    
    void Disassemble(bool print_result);
    void Interpret();
    
};

#endif /* VirtualMachine_hpp */
