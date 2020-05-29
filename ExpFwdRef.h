//
// Created by ahmed on 5/27/20.
//

#ifndef SIC_ASSEMBLER_EXPFWDREF_H
#define SIC_ASSEMBLER_EXPFWDREF_H


#include "Exp.h"

class ExpFwdRef {
public:
    ExpFwdRef();

public:
    ExpFwdRef(int locCnt, int base, bool e, bool x, int addr, bool isBase, const Exp &exp);

    int locCnt{};
    int base{};
    bool e{}, x{};
    int addr{};
    bool isBase{};
    Exp exp;
};


#endif //SIC_ASSEMBLER_EXPFWDREF_H
