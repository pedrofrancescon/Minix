//
//  Definitions.hpp
//  Minix
//
//  Created by Pedro Francescon Cittolin on 20/07/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#ifndef Definitions_h
#define Definitions_h

using namespace std;

inline unsigned char getOpcode4(char* binary) { return binary[0] >> 4 & 0xf; }
inline unsigned char getOpcode5(char* binary) { return binary[0] >> 3 & 0x1f; }
inline unsigned char getOpcode6(char* binary) { return binary[0] >> 2 & 0x3f; }
inline unsigned char getOpcode7(char* binary) { return binary[0] >> 1 & 0x7f; }
inline unsigned char getOpcode8(char* binary) { return binary[0] & 0xff; }

inline unsigned char getD(char* binary) { return binary[0] >> 1 & 0x1; }
inline unsigned char getW(char* binary) { return binary[0] & 0x1; }
inline unsigned char getSW(char* binary) { return binary[0] & 0x3; }

inline unsigned char getMod(char* binary) { return binary[1] >> 6 & 0x3; }
inline unsigned char getReg(char* binary) { return binary[1] >> 3 & 0x7; }
inline unsigned char getRm(char* binary) { return binary[1] & 0x7; }

#define EXIT 1
#define WRITE 4

enum regs {ax, cx, dx, bx, sp, bp, si, di};

#endif /* Definitions_h */
