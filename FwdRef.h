//
// Created by ahmed on 5/27/20.
//

#ifndef SIC_ASSEMBLER_FWDREF_H
#define SIC_ASSEMBLER_FWDREF_H


#include "Exp.h"

class FwdRef {
public:
    FwdRef();

public:
    FwdRef(int locCount, int base, bool e, bool x, int address, bool isBase);

public:
    int locCnt{};
    int base{};
    bool e{},x{};
    int addr{};
    bool isBase{};
};


#endif //SIC_ASSEMBLER_FWDREF_H
