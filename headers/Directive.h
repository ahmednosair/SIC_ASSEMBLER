//
// Created by ahmed on 5/26/20.
//

#ifndef SIC_ASSEMBLER_DIRECTIVE_H
#define SIC_ASSEMBLER_DIRECTIVE_H

#include <bits/stdc++.h>
#include "Exp.h"

using namespace std;

class Directive {
public:
    Directive();

public:
    bool isValid;
    bool isSym;
    bool isExp;
    string label;
    string dSym;
    string value;
    Exp exp;
};


#endif //SIC_ASSEMBLER_DIRECTIVE_H
