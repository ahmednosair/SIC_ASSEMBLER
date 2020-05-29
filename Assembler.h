//
// Created by ahmed on 5/27/20.
//

#ifndef SIC_ASSEMBLER_ASSEMBLER_H
#define SIC_ASSEMBLER_ASSEMBLER_H

#include <bits/stdc++.h>
#include "Parser.h"
#include "SymTable.h"
#include "TextRec.h"

using namespace std;

class Assembler {
private:
    stringstream objectCode;
    Parser parser;
    unordered_map<string, int> opCode;
    int locCnt{};
    SymTable symTable;
    bool isBase;
    int base{};
    TextRec textRec;
    const string twentyFourZeros = "000000000000000000000000";
    const string sixteenZeros = "0000000000000000";
    string LC = "LC";

public:
    Assembler();

    bool assemble(string &filePath);

    string assembleInst(Inst &ins);

    string assembleDirect(Directive &dir);

    string assembleFormatOne(Inst &ins);

    string assembleFormatTwo(Inst &ins);

    string assembleFormatThree(Inst &ins);

    string assembleFormatFour(Inst &ins);

    int assembleExp(Exp &exp);

    void handleLabel(string &label);

    bool checkExp(Inst &inst);

    bool checkExpress(Exp &exp);
};


#endif //SIC_ASSEMBLER_ASSEMBLER_H
