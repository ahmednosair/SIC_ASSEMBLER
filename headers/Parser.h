//
// Created by ahmed on 5/26/20.
//

#ifndef SIC_ASSEMBLER_PARSER_H
#define SIC_ASSEMBLER_PARSER_H

#include <bits/stdc++.h>
#include "Inst.h"
#include "Directive.h"

using namespace std;

class Parser {
public:
    Parser();

private:

    string formatOne;
    string formatTwoWithTwoReg;
    string formatTwoWithOneReg;
    string formatThreeFourNoOp;
    string formatThreeFourSym;
    string formatThreeFourNonSym;
    string startDirective;
    string endDirective;
    string byteDirective;
    string wordDirective;
    string varsDirective;
    string equDirective;
    string orgDirective;
    string baseDirective;
    string noBaseDirective;
    regex fOne;
    regex fThreeFourNoOp;
    regex fTwoWithTwoReg;
    regex fTwoWithOneReg;
    regex fThreeFourSym;
    regex fThreeFourNonSym;
    regex byteD;
    regex wordD;
    regex varsD;
    regex equD;
    regex orgD;
    regex startD;
    regex endD;
    regex baseD;
    regex noBaseD;

public:
    Inst parseInstruction(string &line);

    Directive parseDirective(string &line);

    bool isComment(string &line);


};


#endif //SIC_ASSEMBLER_PARSER_H
