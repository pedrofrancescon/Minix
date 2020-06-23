//
//  main.cpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 26/05/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#include "Binary.hpp"
#include "Instruction.hpp"

#define MASK >> 5 & 0x3

int main(int argc, const char * argv[]) {
    
    ifstream::pos_type size;
    char * memblock;

    ifstream file ("a.out", ios::in|ios::binary|ios::ate);
    if (!file.is_open())
    {
        cout << "Could not open the file" << endl;
        return 0;
    }

    size = file.tellg();
    memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();
    
//    Instruction test (memblock, 0x1108 + TEXT_START_POS);
    
    long text_size = Binary2Dec(string(memblock,size), 8, 4);
    int pc = TEXT_START_POS;

    while (pc < TEXT_START_POS + text_size)
    {
        cout << hex << setfill('0') << setw(4) << pc - TEXT_START_POS << ":   ";

        Instruction instruction (memblock, pc);
        if (instruction.GetInstructionSize() == 0)
        {
            cout << hex << "STOPPED: " << pc - TEXT_START_POS <<  endl;
            cout << endl;
            break;
        }
        pc += instruction.GetInstructionSize();
    }

    return 0;
    
}
