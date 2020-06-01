//
// Created by ahmed on 5/27/20.
//

#include "../headers/Assembler.h"
#include <bits/stdc++.h>
#include "../headers/Util.h"

using namespace std;

Assembler::Assembler() {
    isBase = false;
    opCode["ADD"] = 0x18;
    opCode["ADDF"] = 0x58;
    opCode["ADDR"] = 0x90;
    opCode["AND"] = 0x40;
    opCode["CLEAR"] = 0xB4;
    opCode["COMP"] = 0x28;
    opCode["COMPF"] = 0x88;
    opCode["COMPR"] = 0xA0;
    opCode["DIV"] = 0x24;
    opCode["DIVF"] = 0x64;
    opCode["DIVR"] = 0x9C;
    opCode["FIX"] = 0xC4;
    opCode["FLOAT"] = 0xC0;
    opCode["HIO"] = 0x1;
    opCode["J"] = 0x3C;
    opCode["JEQ"] = 0x30;
    opCode["JGT"] = 0x34;
    opCode["JLT"] = 0x38;
    opCode["JSUB"] = 0x4B;
    opCode["LDA"] = 0x0;
    opCode["LDB"] = 0x68;
    opCode["LDCH"] = 0x50;
    opCode["LDF"] = 0x70;
    opCode["LDL"] = 0x8;
    opCode["LDS"] = 0x6C;
    opCode["LDT"] = 0x74;
    opCode["LDX"] = 0x4;
    opCode["LPS"] = 0xD0;
    opCode["MUL"] = 0x20;
    opCode["MULF"] = 0x60;
    opCode["MULR"] = 0x98;
    opCode["NORM"] = 0xC8;
    opCode["OR"] = 0x44;
    opCode["RD"] = 0xD8;
    opCode["RMO"] = 0xAC;
    opCode["RSUB"] = 0x4C;
    opCode["SHIFTL"] = 0xA4;
    opCode["SHIFTR"] = 0xA8;
    opCode["SIO"] = 0xF0;
    opCode["SSK"] = 0xEC;
    opCode["STA"] = 0x0C;
    opCode["STB"] = 0x78;
    opCode["STCH"] = 0x54;
    opCode["STF"] = 0x80;
    opCode["STI"] = 0xD4;
    opCode["STL"] = 0x14;
    opCode["STS"] = 0x7C;
    opCode["STSW"] = 0xE8;
    opCode["STT"] = 0x84;
    opCode["STX"] = 0x10;
    opCode["SUB"] = 0x1C;
    opCode["SUBF"] = 0x5C;
    opCode["SUBR"] = 0x94;
    opCode["SVC"] = 0xB0;
    opCode["TD"] = 0xE0;
    opCode["TIO"] = 0xF8;
    opCode["TIX"] = 0x2C;
    opCode["TIXR"] = 0xB8;
    opCode["A"] = 0;
    opCode["X"] = 1;
    opCode["L"] = 2;
    opCode["B"] = 3;
    opCode["S"] = 4;
    opCode["T"] = 5;
    opCode["F"] = 6;
    opCode["PC"] = 8;
    opCode["SW"] = 9;

}

bool Assembler::assemble(string &filePath) {
    clear();
    ifstream input;
    input.open(filePath);
    Inst instruction;
    Directive directive;
    string line, startStr;
    string startPosition;
    int startPos;
    int cnt = 2;
    int mx = INT_MIN;
    while (getline(input, line) && (line.empty() || parser.isComment(line))) {
        cnt++;
    }
    directive = parser.parseDirective(line);
    if (!directive.isValid || directive.dSym != "START") {
        cout << "\nNo program START found or invalid START\nIncomplete assembly\n";
        input.close();
        return false;
    } else {
        startStr.append("H" + directive.label);
        for (int i = directive.label.length(); i < 6; i++) {
            startStr.push_back(' ');
        }
        startStr.push_back('^');
        try {
            locCnt = stoi(directive.value, nullptr, 16);
            if (locCnt > 1048576) {
                cout << "\nOut of Range starting addr\nIncomplete assembly\n";
                input.close();
                return false;
            }
        } catch (exception &e) {
            cout << "\nOut of Range starting addr\nIncomplete assembly\n";
            input.close();
            return false;
        }
        startPos = locCnt;
        startPosition = Util::addZeros(directive.value, 6);
        startStr.append(startPosition);
        startStr.push_back('^');
    }
    textRec = TextRec(Util::decToHex(locCnt));
    symTable.add(LC, locCnt);
    string objCode;
    while (getline(input, line)) {
        if (!line.empty() && !parser.isComment(line)) {
            instruction = parser.parseInstruction(line);
            if (instruction.Valid) {
                objCode = (assembleInst(instruction));
                if (objCode.length() + textRec.getLen() <= 71) {
                    textRec.append(objCode);
                } else {
                    objectCode << textRec.getTextRecord();
                    textRec = TextRec(Util::decToHex(locCnt));
                    textRec.append(objCode);
                }
                locCnt += (int) objCode.length() / 2;
            } else {
                directive = parser.parseDirective(line);
                if (directive.isValid) {
                    if (directive.dSym == "END") {
                        objectCode << textRec.getTextRecord();
                        break;
                    }
                    objCode = (assembleDirect(directive));
                    if (objCode.length() + textRec.getLen() <= 71) {
                        textRec.append(objCode);
                    } else {
                        objectCode << textRec.getTextRecord();
                        textRec = TextRec(Util::decToHex(locCnt));
                        textRec.append(objCode);
                    }
                    locCnt += (int) objCode.length() / 2;
                } else {
                    cout << "\nLine: " << cnt << " Invalid statement\nIncomplete assembly\n";
                    input.close();
                    return false;
                }
            }
        }
        symTable.updateSymEntry(LC, locCnt, true);
        mx = max(locCnt, mx);
        cnt++;
    }
    vector<string> unresolved = symTable.getUnresolved();
    if (!unresolved.empty()) {
        cout << "\nThe program contains undefined symbols: " << Util::printVector(unresolved)
             << ".\nIncomplete assembly\n";
        input.close();
        return false;
    }
    pair<vector<string>, string> result = symTable.getUnresolvedExp();
    objectCode << result.second;
    if (!result.first.empty()) {
        cout << "\nThe program contains undefined symbols: " << Util::printVector(result.first)
             << ".\nIncomplete assembly\n";
        input.close();
        return false;
    }
    if (directive.dSym != "END") {
        cout << "\nMissing program END.\nIncomplete assembly\n";
        input.close();
        return false;
    }
    if (directive.value.empty()) {
        objectCode << "E" << startPosition;
    } else {
        if (!symTable.search(directive.value) || !symTable.get(directive.value).addrSet) {
            cout << "\nUndefined label to start program with.\nIncomplete assembly\n";
            input.close();
            return false;
        }
        objectCode << "E" << Util::addZeros(Util::decToHex(symTable.get(directive.value).addr), 6);
    }
    string tmp = line;
    while (getline(input, line) && (line.empty() || parser.isComment(line)));
    if (!line.empty() && tmp != line && !parser.isComment(line)) {
        cout << "\nThe program contains statements after END statement.\nIncomplete assembly\n";
        input.close();
        return false;
    }
    input.close();
    startStr.append(Util::addZeros(Util::decToHex(mx - startPos - 1), 6) + '\n');
    ofstream output;
    output.open("objectCode.txt", ofstream::trunc);
    output << Util::toUpper(startStr) << Util::toUpper(objectCode.str());
    output.close();
    return true;
}

string Assembler::assembleInst(Inst &ins) {
    handleLabel(ins.label);
    if (ins.format == 1) {
        return assembleFormatOne(ins);
    } else if (ins.format == 2) {
        return assembleFormatTwo(ins);
    } else if (ins.format == 3) {
        return assembleFormatThree(ins);
    } else {
        return assembleFormatFour(ins);

    }
}

string Assembler::assembleDirect(Directive &dir) {
    if (dir.dSym == "BYTE") {
        handleLabel(dir.label);
        if (dir.isSym) {
            return Util::strToHex(dir.value);
        }
        return dir.value;
    } else if (dir.dSym == "WORD") {
        handleLabel(dir.label);
        int val = stoi(dir.value);
        if (val < -((int) (1u << 23u)) || val > ((int) (1u << 23u) - 1)) {
            cout << "\nOut of 3 byte integer range!\nIncomplete assembly";
            throw exception();
        }
        return Util::addZeros(Util::decToHex(val), 6);
    } else if (dir.dSym == "RESW") {
        handleLabel(dir.label);
        int val = stoi(dir.value);
        if (val > ((int) (1u << 20u) - locCnt) / 3) {
            cout << "\n" << dir.label << " is too large !Out of memory!\nIncomplete assembly";
            throw exception();
        }
        locCnt += val * 3;
        objectCode << textRec.getTextRecord();
        textRec = TextRec(Util::decToHex(locCnt));
        return "";
    } else if (dir.dSym == "RESB") {
        int val = stoi(dir.value);
        handleLabel(dir.label);
        if (val > ((int) (1u << 20u) - locCnt)) {
            cout << "\n" << dir.label << " is too large !Out of memory!\nIncomplete assembly";
            throw exception();
        }
        locCnt += val;
        objectCode << textRec.getTextRecord();
        textRec = TextRec(Util::decToHex(locCnt));
        return "";
    } else if (dir.dSym == "EQU") {
        int val;
        if (dir.isExp) {
            if (!checkExpress(dir.exp)) {
                cout << "Undefined expression operands use in directives isn't allowed!\nIncomplete assembly!\n";
                throw exception();
            }
            val = assembleExp(dir.exp);
        } else {
            if (dir.isSym) {
                val = symTable.get(dir.value).addr;
            } else {
                val = stoi(dir.value);
            }
        }
        if (symTable.search(dir.label)) {
            SymEntry l = symTable.get(dir.label);
            if (l.addrSet) {
                cout << "Duplicate Label: " << dir.label;
                throw exception();
            } else {
                l.addr = val;
                l.addrSet = true;
                objectCode << textRec.getTextRecord();
                objectCode << l.resolveFwdRef();
                textRec = TextRec(Util::decToHex(locCnt));
            }
        } else {
            symTable.add(dir.label, val);
        }

        return "";
    } else if (dir.dSym == "ORG") {
        if (dir.isExp) {
            if (!checkExpress(dir.exp)) {
                cout << "Undefined expression operands use in directives isn't allowed!\nIncomplete assembly!\n";
                throw exception();
            }
            locCnt = assembleExp(dir.exp);
        } else {
            if (dir.isSym) {
                locCnt = symTable.get(dir.value).addr;
            } else {
                locCnt = stoi(dir.value);
            }
        }
        return "";
    } else if (dir.dSym == "BASE") {
        if (dir.isExp) {
            if (!checkExpress(dir.exp)) {
                cout << "Undefined expression operands use in directives isn't allowed!\nIncomplete assembly!\n";
                throw exception();
            }
            base = assembleExp(dir.exp);
        } else {
            if (dir.isSym) {
                base = symTable.get(dir.value).addr;
            } else {
                base = stoi(dir.value);
            }
        }
        isBase = true;
        return "";
    } else if (dir.dSym == "NOBASE") {
        isBase = false;
    }
    return "";
}

bool Assembler::checkExpress(Exp &exp) {
    bool isFOpNum = Util::isNum(exp.fOp);
    bool isSOpNum = Util::isNum(exp.sOp);
    if (!isFOpNum) {
        if (!symTable.search(exp.fOp) || !symTable.get(exp.fOp).addrSet) {
            return false;
        }
    }
    if (!isSOpNum) {
        if (!symTable.search(exp.sOp) || !symTable.get(exp.sOp).addrSet) {
            return false;
        }
    }
    return true;
}

int Assembler::assembleExp(Exp &exp) {
    bool isFOpNum = Util::isNum(exp.fOp);
    bool isSOpNum = Util::isNum(exp.sOp);
    int fVal = isFOpNum ? stoi(exp.fOp) : symTable.get(exp.fOp).addr;
    int sVal = isSOpNum ? stoi(exp.sOp) : symTable.get(exp.sOp).addr;
    return exp.evaluate(fVal, sVal);
}

bool Assembler::checkExp(Inst &inst) {
    bool isFOpNum = Util::isNum(inst.exp.fOp);
    bool isSOpNum = Util::isNum(inst.exp.sOp);
    if (!isFOpNum) {
        if (!symTable.search(inst.exp.fOp) || !symTable.get(inst.exp.fOp).addrSet) {
            symTable.addExpFwdRef(ExpFwdRef(locCnt + inst.format, base, inst.e, inst.x, locCnt + 1, isBase, inst.exp));
            return false;
        }
    }
    if (!isSOpNum) {
        if (!symTable.search(inst.exp.sOp) || !symTable.get(inst.exp.sOp).addrSet) {
            symTable.addExpFwdRef(ExpFwdRef(locCnt + inst.format, base, inst.e, inst.x, locCnt + 1, isBase, inst.exp));
            return false;
        }
    }
    return true;
}

void Assembler::handleLabel(string &label) {
    if (!label.empty()) {
        if (symTable.search(label)) {
            if (symTable.get(label).addrSet) {
                if (symTable.search(label) && symTable.get(label).addrSet) {
                    cout << "Duplicate label: " << label << "\nIncomplete assembly!\n";
                    throw exception();
                }
            } else {
                symTable.updateSymEntry(label, locCnt, true);
                objectCode << textRec.getTextRecord();
                objectCode << symTable.get(label).resolveFwdRef();
                textRec = TextRec(Util::decToHex(locCnt));
            }
        } else {
            symTable.add(label, locCnt);
        }
    }
}

string Assembler::assembleFormatOne(Inst &ins) {
    return Util::addZeros(Util::decToHex(opCode[ins.opSym]), 2);
}

string Assembler::assembleFormatTwo(Inst &ins) {
    int r1 = opCode[ins.fOp];
    int r2 = 0;
    if (!ins.sOp.empty()) {
        r2 = ins.isSym ? opCode[ins.sOp] : (stoi(ins.sOp) - 1);
    }
    return Util::addZeros(Util::decToHex(opCode[ins.opSym]), 2) + Util::decToHex(r1) + Util::decToHex(r2);
}

string Assembler::assembleFormatThree(Inst &ins) {
    if (ins.opSym == "RSUB") {
        return "4F0000";
    }
    bitset<8> op(opCode[ins.opSym]);
    op[1] = ins.n;
    op[0] = ins.i;
    if (ins.isExp) {
        int val = checkExp(ins) ? assembleExp(ins.exp) : 0;
        string flags((ins.x ? "1000" : "0000"));
        if (val - (locCnt + 3) >= -2048 && val - (locCnt + 3) < 2047) {
            flags[2] = '1';
            val -= (locCnt + 3);
        } else if (isBase && val - base >= 0 && val - base < 4096) {
            flags[1] = '1';
            val -= base;
        } else {
            cout << "Out of range addressing for format 3.\nIncomplete assembly!\n";
            throw exception();
        }
        int mask = (int) bitset<24>(op.to_string() + flags + bitset<12>(val).to_string()).to_ulong();
        return Util::addZeros(Util::decToHex(mask), 6);
    } else {
        if (ins.isSym) {
            if (symTable.search(ins.fOp)) {
                if (symTable.get(ins.fOp).addrSet) {
                    int val = symTable.get(ins.fOp).addr;
                    string flags((ins.x ? "1000" : "0000"));
                    if (val - (locCnt + 3) >= -2048 && val - (locCnt + 3) < 2047) {
                        flags[2] = '1';
                        val -= (locCnt + 3);
                    } else if (isBase && val - base >= 0 && val - base < 4096) {
                        flags[1] = '1';
                        val -= base;
                    } else {
                        cout << "Out of range addressing for format 3.\nIncomplete assembly!\n";
                        throw exception();
                    }
                    int mask = (int) bitset<24>(op.to_string() + flags + bitset<12>(val).to_string()).to_ulong();
                    return Util::addZeros(Util::decToHex(mask), 6);
                } else {
                    symTable.addFwdRef(ins.fOp, FwdRef(locCnt + 3, base, ins.e, ins.x, locCnt + 1, isBase));
                    return Util::addZeros(Util::decToHex((int) bitset<24>(
                            op.to_string() + sixteenZeros).to_ulong()), 6);
                }
            } else {
                symTable.add(ins.fOp);
                FwdRef f(locCnt + 3, base, ins.e, ins.x, locCnt + 1, isBase);
                symTable.addFwdRef(ins.fOp, f);
                int mask = (int) bitset<24>(op.to_string() + sixteenZeros).to_ulong();
                return Util::addZeros(Util::decToHex(mask), 6);
            }

        } else {
            int val = stoi(ins.fOp);
            string flags((ins.x ? "1000" : "0000"));
            if (val >= 0 && val <= 4096) {
            } else if (val - (locCnt + 3) >= -2048 && val - (locCnt + 3) < 2047) {
                flags[2] = '1';
                val -= (locCnt + 3);
            } else if (isBase && val - base >= 0 && val - base < 4096) {
                flags[1] = '1';
                val -= base;
            } else {
                cout << "Out of range addressing for format 3.\nIncomplete assembly!\n";
                throw exception();
            }
            return Util::addZeros(Util::decToHex(
                    (int) bitset<24>(op.to_string() + flags + bitset<12>(val).to_string()).to_ulong()),
                                  6);
        }
    }
}

string Assembler::assembleFormatFour(Inst &ins) {
    bitset<8> op(opCode[ins.opSym]);
    op[1] = ins.n;
    op[0] = ins.i;
    if (ins.opSym == "RSUB") {
        return "4F100000";
    }
    if (ins.isExp) {
        int value = checkExp(ins) ? assembleExp(ins.exp) : 0;
        string val = bitset<20>(value).to_string();
        int mask = (int) bitset<32>(op.to_string() + (ins.x ? "1001" : "0001") + val).to_ulong();
        return Util::addZeros(Util::decToHex(mask), 8);
    } else {
        if (ins.isSym) {
            if (symTable.search(ins.fOp)) {
                if (symTable.get(ins.fOp).addrSet) {
                    string val = bitset<20>(symTable.get(ins.fOp).addr).to_string();
                    int mask = (int) bitset<32>(op.to_string() + (ins.x ? "1001" : "0001") + val).to_ulong();
                    return Util::addZeros(Util::decToHex(mask), 8);
                } else {
                    FwdRef f(locCnt + 4, base, ins.e, ins.x, locCnt + 1, isBase);
                    symTable.addFwdRef(ins.fOp, f);
                    int mask = (int) bitset<32>(op.to_string() + twentyFourZeros).to_ulong();
                    return Util::addZeros(Util::decToHex(mask), 8);
                }
            } else {
                symTable.add(ins.fOp);
                FwdRef f(locCnt + 4, base, ins.e, ins.x, locCnt + 1, isBase);
                symTable.addFwdRef(ins.fOp, f);
                int mask = (int) bitset<32>(op.to_string() + twentyFourZeros).to_ulong();
                return Util::addZeros(Util::decToHex(mask), 8);
            }

        } else {
            string val = bitset<20>(stoi(ins.fOp)).to_string();
            int mask = (int) bitset<32>(op.to_string() + (ins.x ? "1001" : "0001") + val).to_ulong();
            return Util::addZeros(Util::decToHex(mask), 8);
        }
    }
}

void Assembler::createListFile() {
    ofstream listing;
    listing.open("listFile.txt");
    listing << symTable.getTable();
    listing.close();
}

void Assembler::clear() {
    objectCode.str("");
    symTable.clear();
    isBase = false;
}


