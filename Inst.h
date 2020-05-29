//
// Created by ahmed on 5/26/20.
//

#ifndef SIC_ASSEMBLER_INST_H
#define SIC_ASSEMBLER_INST_H

#include <bits/stdc++.h>
#include "Exp.h"

using namespace std;

class Inst {
private:
public:
    Inst();

public:
    bool n;
    bool i;
    bool x;
    bool e;
    bool isSym;
    bool Valid;
    bool isExp;
    int format;
    string opSym;
    string fOp;
    string sOp;
    string label;
    Exp exp;
};


#endif //SIC_ASSEMBLER_INST_H
