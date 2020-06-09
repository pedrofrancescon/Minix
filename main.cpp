//
//  main.cpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 26/05/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#include "Binary.hpp"
#include "Instructions.hpp"

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
    
     long text_size = Binary2Dec(string(memblock,size), 8, 4);
//     cout << text_size << endl;

//     string text = Binary2Text(string(memblock,size), 32, 2);
//     cout << text << endl;

//     string binary = Binary2Hex(string(memblock,size), true, true);
//     cout << binary << endl;
    
    int pointer = 32;
    
    while (pointer < 32 + text_size)
    {
        int instruc_byte_size = 0;
        
        string byte1 = Binary2Bits(string(memblock,size), pointer);
        string byte2 = Binary2Bits(string(memblock,size), pointer+1);
        
        OpcodeCheck(byte1, byte2, &instruc_byte_size);
        pointer += instruc_byte_size;
    }

    return 0;
    
}
