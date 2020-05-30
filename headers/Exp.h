//
// Created by ahmed on 5/27/20.
//

#ifndef SIC_ASSEMBLER_EXP_H
#define SIC_ASSEMBLER_EXP_H

#include <bits/stdc++.h>

using namespace std;

class Exp {
public:
    Exp();

    string fOpS;
    string fOp;
    string sOpS;
    string sOp;
public:
    Exp(string str);

    int evaluate(int fOp, int sOp) ;
};


#endif //SIC_ASSEMBLER_EXP_H
