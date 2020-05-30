//
// Created by ahmed on 5/26/20.
//
#include <bits/stdc++.h>
#include "../headers/Parser.h"
#include "../headers/Util.h"

using namespace std;


Parser::Parser() {
    formatOne = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(RSUB)(\s+(.*)$|$))";
    formatTwoWithTwoReg = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(ADDR|COMPR|DIVR|MULR|SHIFTL|SHIFTR|RMO|SUBR)\s+([AXLBSTF]|PC|SW)\s*,\s*([AXLBSTF]|PC|SW|[1-9]|[1][1-9]|[2][1-4])\s*$)";
    formatTwoWithOneReg = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(TIXR|CLEAR)\s+([AXLBSTF]|PC|SW)\s*$)";
    formatThreeFourSym = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(\+)?\s*(ADD|COMP|COMPF|DIV|DIVF|FIX|FLOAT|J|JLT|JEQ|JGT|JSUB|LDA|LDB|LDCH|LDF|LDL|LDS|LDT|LDX|LPS|MUL|MULF|NORM|OR|RD|RSUB|SSK|STA|STB|STCH|STF|STI|STL|STS|STSW|STT|STX|SUB|SUBF|TD|TIX|WD)\s+(#|@)?\s*([A-Z][A-Z0-9]*|((\s*([A-Z][A-Z0-9]*)\s*-\s*([A-Z][A-Z0-9]*)\s*)|(\s*-\s*([A-Z][A-Z0-9]*)\s*\+\s*([A-Z][A-Z0-9]*)\s*)|(\s*([A-Z][A-Z0-9]*)\s*[-\+]\s*\d+\s*)|(\s*[-\+]?\s*\d+\s*\+\s*([A-Z][A-Z0-9]*)\s*)))\s*(,\s*(X)\s*)?$)";
    formatThreeFourNonSym = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(\+)?\s*(ADD|COMP|COMPF|DIV|DIVF|FIX|FLOAT|JLT|J|JEQ|JGT|JSUB|LDA|LDB|LDCH|LDF|LDL|LDS|LDT|LDX|LPS|MUL|MULF|NORM|OR|RD|RSUB|SSK|STA|STB|STCH|STF|STI|STL|STS|STSW|STT|STX|SUB|SUBF|TD|TIX|WD)\s+(#|@)?\s*(\d+|(\s*[-\+]?\s*\d+\s*[-\+\*\/]\s*\d+\s*))\s*(,\s*(X)\s*)?$)";
    startDirective = R"(^\s*(([A-Z][A-Z0-9]{0,5})\s+)?(START)\s+([0-9A-F]+)\s*$)";
    endDirective = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(END)(\s+([A-Z][A-Z0-9]*))?\s*$)";
    byteDirective = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(BYTE)\s+(C|X)\s*'([^']*)'\s*$)";
    wordDirective = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(WORD)\s+(\d+)\s*$)";
    varsDirective = R"(^\s*(([A-Z][A-Z0-9]*)\s+)?(RESW|RESB)\s+(\d+)\s*$)";
    equDirective = R"(^\s*(([A-Z][A-Z0-9]*)\s+)\s*(EQU)\s+([A-Z][A-Z0-9]*|\d+|((\s*([A-Z][A-Z0-9]*)\s*-\s*([A-Z][A-Z0-9]*)\s*)|(\s*-\s*([A-Z][A-Z0-9]*)\s*\+\s*([A-Z][A-Z0-9]*)\s*)|(\s*([A-Z][A-Z0-9]*)\s*[-\+]\s*\d+\s*)|(\s*[-\+]?\s*\d+\s*\+\s*([A-Z][A-Z0-9]*)\s*)|(\s*[-\+]?\s*\d+\s*[-\+\*\/]\s*\d+\s*)))\s*$)";
    orgDirective = R"(^\s*(ORG)\s+([A-Z][A-Z0-9]*|\d+|((\s*([A-Z][A-Z0-9]*)\s*-\s*([A-Z][A-Z0-9]*)\s*)|(\s*-\s*([A-Z][A-Z0-9]*)\s*\+\s*([A-Z][A-Z0-9]*)\s*)|(\s*([A-Z][A-Z0-9]*)\s*[-\+]\s*\d+\s*)|(\s*[-\+]?\s*\d+\s*\+\s*([A-Z][A-Z0-9]*)\s*)|(\s*[-\+]?\s*\d+\s*[-\+\*\/]\s*\d+\s*)))\s*$)";
    baseDirective = R"(^\s*(BASE)\s+([A-Z][A-Z0-9]*|\d+|((\s*([A-Z][A-Z0-9]*)\s*-\s*([A-Z][A-Z0-9]*)\s*)|(\s*-\s*([A-Z][A-Z0-9]*)\s*\+\s*([A-Z][A-Z0-9]*)\s*)|(\s*([A-Z][A-Z0-9]*)\s*[-\+]\s*\d+\s*)|(\s*[-\+]?\s*\d+\s*\+\s*([A-Z][A-Z0-9]*)\s*)|(\s*[-\+]?\s*\d+\s*[-\+\*\/]\s*\d+\s*)))\s*$)";;
    noBaseDirective = R"(^\s*(NOBASE)\s*$)";
    fOne = regex(formatOne);
    fTwoWithOneReg = regex(formatTwoWithOneReg);
    fTwoWithTwoReg = regex(formatTwoWithTwoReg);
    fThreeFourSym = regex(formatThreeFourSym);
    fThreeFourNonSym = regex(formatThreeFourNonSym);
    byteD = regex(byteDirective);
    wordD = regex(wordDirective);
    varsD = regex(varsDirective);
    equD = regex(equDirective);
    orgD = regex(orgDirective);
    startD = regex(startDirective);
    endD = regex(endDirective);
    baseD = regex(baseDirective);
    noBaseD = regex(noBaseDirective);

}

Inst Parser::parseInstruction(string &line) {
    line = Util::toUpper(line);
    smatch matches;
    Inst result;
    if (regex_match(line, matches, fOne)) {
        result.Valid = true;
        result.format = 1;
        result.label = matches[2].str();
        result.opSym = matches[3].str();
    } else if (regex_match(line, matches, fTwoWithOneReg)) {
        result.Valid = true;
        result.format = 2;
        result.label = matches[2].str();
        result.opSym = matches[3].str();
        result.fOp = matches[4].str();
    } else if (regex_match(line, matches, fTwoWithTwoReg)) {
        result.Valid = true;
        result.format = 2;
        result.label = matches[2].str();
        result.opSym = matches[3].str();
        result.fOp = matches[4].str();
        result.sOp = matches[5].str();
        if (regex_match(result.sOp, regex(R"(\d+)"))) {
            result.isSym = false;
        }
    } else if (regex_match(line, matches, fThreeFourSym)) {
        result.isSym = true;
        result.Valid = (matches[20].matched && !matches[5].matched) || !(matches[20].matched);
        result.label = matches[2].str();
        result.format = matches[3].matched ? 4 : 3;
        result.opSym = matches[4].str();
        if (regex_match(matches[6].str(), regex(R"([A-Z][A-Z0-9]*)"))) {
            result.fOp = matches[6].str();
        } else {
            result.isExp = true;
            result.exp = Exp(matches[6].str());
        }
        result.e = (result.format == 4);
        result.i = matches[5].str() == "#";
        result.n = matches[5].str() == "@";
        if (result.i == result.n && !result.i) {
            result.i = result.n = true;
        }
        result.x = matches[20].matched;
    } else if (regex_match(line, matches, fThreeFourNonSym)) {
        result.isSym = false;
        result.Valid = (matches[9].matched && !matches[5].matched) || !(matches[9].matched);
        result.label = matches[2].str();
        result.format = matches[3].matched ? 4 : 3;
        result.opSym = matches[4].str();
        if (regex_match(matches[6].str(), regex(R"(\d+)"))) {
            result.fOp = matches[6].str();
        } else {
            result.isExp = true;
            result.exp = Exp(matches[6].str());
        }
        result.e = (result.format == 5);
        result.i = matches[5].str() == "#";
        result.n = matches[5].str() == "@";
        if (result.i == result.n && !result.i) {
            result.i = result.n = true;
        }
        result.x = matches[9].matched;
    }
    return result;
}

Directive Parser::parseDirective(string &line) {
    transform(line.begin(), line.end(), line.begin(), ::toupper);
    smatch matches;
    Directive result;
    if (regex_match(line, matches, byteD)) {
        result.isValid = true;
        result.label = matches[2].str();
        result.dSym = matches[3].str();
        result.isSym = matches[4].str() == "C";
        result.value = matches[5].str();
    } else if (regex_match(line, matches, wordD)) {
        result.isValid = true;
        result.label = matches[2].str();
        result.dSym = matches[3].str();
        result.value = matches[4].str();
    } else if (regex_match(line, matches, varsD)) {
        result.isValid = true;
        result.label = matches[2].str();
        result.dSym = matches[3].str();
        result.value = matches[4].str();
    } else if (regex_match(line, matches, equD)) {
        result.isValid = true;
        result.label = matches[2].str();
        result.dSym = matches[3].str();
        if (regex_match(matches[4].str(), regex(R"([A-Z][A-Z0-9]*|\d+)"))) {
            result.value = matches[4].str();
            result.isSym = !regex_match(matches[4].str(), regex(R"(^[0-9]+$)"));
        } else {
            result.isExp = true;
            result.exp = Exp(matches[4].str());
        }
    } else if (regex_match(line, matches, orgD)) {
        result.isValid = true;
        result.dSym = matches[1].str();
        if (regex_match(matches[2].str(), regex(R"([A-Z][A-Z0-9]*|\d+)"))) {
            result.value = matches[2].str();
            result.isSym = !regex_match(matches[2].str(), regex(R"(^[0-9]+$)"));
        } else {
            result.isExp = true;
            result.exp = Exp(matches[2].str());
        }
    } else if (regex_match(line, matches, startD)) {
        result.isValid = true;
        result.label = matches[2].str();
        result.dSym = matches[3].str();
        result.value = matches[4].str();
    } else if (regex_match(line, matches, endD)) {
        result.isValid = true;
        result.label = matches[2].str();
        result.dSym = matches[3].str();
        result.value = matches[5].str();
    } else if (regex_match(line, matches, baseD)) {
        result.isValid = true;
        result.dSym = matches[1].str();
        if (regex_match(matches[2].str(), regex(R"([A-Z][A-Z0-9]*|\d+)"))) {
            result.value = matches[2].str();
            result.isSym = !regex_match(matches[2].str(), regex(R"(^[0-9]+$)"));
        } else {
            result.isExp = true;
            result.exp = Exp(matches[2].str());
        }
    } else if (regex_match(line, matches, noBaseD)) {
        result.isValid = true;
        result.dSym = matches[1].str();
    }
    return result;
}

bool Parser::isComment(string &line) {
    if (line.empty()) {
        return false;
    }
    return line[0] == '.';
}
