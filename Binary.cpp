//
//  Binary.cpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 09/06/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#include "Binary.hpp"

string Binary2Bits(const string& s, int pos)
{
    stringstream bits;
    
    bits << hex << int(s[pos]&0xff);
    
    unsigned n;
    bits >> n;
    bitset<8> b(n);
    return b.to_string();
}

string Binary2Text(const string& s, int start_pos, long text_size)
{
    stringstream text;

    for (long i = start_pos; i < start_pos + text_size; i++)
    {
        text << char(int(s[i]&0xff));
    }

    return text.str();
}

int Binary2Dec(const string& s, int start_pos, int bytes_count)
{
    int shifter = 8;
    int result = s[start_pos]&0xff;
    
    for (int i = start_pos+1; i < start_pos + bytes_count; i++)
    {
        result += (int(s[i]&0xff) << shifter);
        shifter += 8;
    }

    return result;
}

string Byte2Hex(char s, bool upper_case, bool is_signed)
{
    stringstream result;
    
    if (is_signed)
        result << hex << (s<0?"-":"") << setfill('0') << setw(2) << (upper_case ? uppercase : nouppercase) <<  (s<0?-(unsigned)s:s);
    else
        result << hex << setfill('0') << setw(2) << (upper_case ? uppercase : nouppercase) << int(s&0xff);
    

    return result.str();
}

string TwoBytes2Hex(char16_t s, bool upper_case)
{
    stringstream result;
    
    result << hex << (s<0?"-":"") << setfill('0') << setw(4) << (upper_case ? uppercase : nouppercase) <<  (s<0?-(unsigned)s:s);
    
    return result.str();
    
}

int Binary2Dec(char s)
{
    return int(s&0xff);
}
