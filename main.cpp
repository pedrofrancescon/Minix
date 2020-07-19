//
//  main.cpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 26/05/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#include "Binary.hpp"
#include "Instruction.hpp"
#include "VirtualMachine.hpp"


ifstream::pos_type OpenFile(const char * file_name[], char ** memblock)
{
    ifstream file (file_name[1], ios::in|ios::binary|ios::ate);
    
    if (!file.is_open())
    {
        cout << "Unable to open file";
        return 0;
    }
    
    ifstream::pos_type size;
    
    size = file.tellg();
    *memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (*memblock, size);
    file.close();
    
    return size;
}

int main(int argc, const char * argv[]) {
    
    if (argc != 2)
    {
        cout << "Incorrect argument!";
        return 0;
    }

    char * memblock;
    ifstream::pos_type size = OpenFile(argv,&memblock);

    VirtualMachine vm (memblock, size);

    vm.Disassemble(true);
    
    return 0;
    
}
