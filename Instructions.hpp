//
//  Instructions.hpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 09/06/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#ifndef Instructions_hpp
#define Instructions_hpp

#include <iostream>

using namespace std;

int ModCheck(string byte2);

void OpcodeCheck(string byte1, string byte2, int* instruc_byte_size);

#endif /* Instructions_hpp */
