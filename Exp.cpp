//
// Created by ahmed on 5/27/20.
//

#include "Exp.h"


Exp::Exp(string str) {
    str = regex_replace(str, regex(R"(\s+)"), "");
    smatch matches;
    regex_match(str, matches, regex(R"(^(-)?([^-\+\*\/]+)([-\+\*\/])([^-\+\*\/]+)$)"));
    fOpS = matches[1].matched ? "-" : "+";
    fOp = matches[2].str();
    sOpS = matches[3].str();
    sOp = matches[4].str();
}

int Exp::evaluate(int fOp, int sOp) {
    int val;
    val = fOpS == "+" ? 1 : -1;
    val *= fOp;
    switch (sOpS[0]) {
        case '+':
            val += sOp;
            break;
        case '-':
            val -= sOp;
            break;
        case '*':
            val *= sOp;
            break;
        case '/':
            val /= sOp;
            break;
    }
    return val;
}


Exp::Exp() = default;
