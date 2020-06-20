//
//  Binary.hpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 09/06/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#ifndef Binary_hpp
#define Binary_hpp

#include <sstream>
#include <fstream>

using namespace std;

string Binary2Bits(const string& s, int pos);

string Binary2Text(const string& s, int start_pos, long text_size);

int Binary2Dec(const string& s, int start_pos, int bytes_count);

string Byte2Hex(char s, bool upper_case = false);

string TwoBytes2Hex(char16_t s, bool upper_case = false);

#endif /* Binary_hpp */
