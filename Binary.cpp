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
    int result = s[start_pos];
    
    for (int i = start_pos+1; i < start_pos + bytes_count; i++)
    {
        result += (s[i] << shifter);
        shifter += 8;
    }

    return result;
}

string Binary2Hex(const string& s, bool upper_case, bool add_space)
{
    stringstream ret;

    for (string::size_type i = 0; i < s.length(); ++i)
    {
        int z = s[i]&0xff;
        ret << hex << setfill('0') << setw(2) << (upper_case ? uppercase : nouppercase) << z;
        ret << (add_space ? " " : "");
    }

    return ret.str();
}
