//
// Created by ahmed on 5/27/20.
//

#include "../headers/SymEntry.h"
#include "../headers/SymTable.h"
#include "../headers/Util.h"

bool SymTable::search(string &sym) {
    return table.count(sym);
}

void SymTable::add(string &sym, int address) {
    table[sym].addr = address;
    table[sym].addrSet = true;
}

void SymTable::add(string &sym) {
    table[sym];
}

SymEntry &SymTable::get(string &sym) {
    return table[sym];
}

vector<string> SymTable::getUnresolved() {
    vector<string> undefined;
    for (auto &entry:table) {
        if (!entry.second.addrSet) {
            undefined.push_back(entry.first);
        }
    }
    return undefined;
}

void SymTable::addFwdRef(string &sym, FwdRef fwd) {
    table[sym].addFwdRef(fwd);
}

void SymTable::addExpFwdRef(ExpFwdRef fwd) {
    expFwdRefers.push_back(fwd);
}

void SymTable::updateSymEntry(string &sym, int address, bool isAddressSet) {
    table[sym].addr = address;
    table[sym].addrSet = isAddressSet;
}

pair<vector<string>, string> SymTable::getUnresolvedExp() {
    stringstream s;
    vector<string> result;
    for (ExpFwdRef &expFwd:expFwdRefers) {
        bool fOpNum = Util::isNum(expFwd.exp.fOp);
        bool sOpNum = Util::isNum(expFwd.exp.sOp);
        if ((!search(expFwd.exp.fOp) && !fOpNum) || (!search(expFwd.exp.sOp) && !sOpNum)) {
            if (!search(expFwd.exp.fOp) && !fOpNum) {
                result.push_back(expFwd.exp.fOp);
            }
            if (!search(expFwd.exp.sOp) && !sOpNum) {
                result.push_back(expFwd.exp.sOp);
            }
        } else {
            int fVal = fOpNum ? stoi(expFwd.exp.fOp) : (expFwd.exp.fOp=="LC"?expFwd.locCnt:get(expFwd.exp.fOp).addr);
            int sVal = sOpNum ? stoi(expFwd.exp.sOp) : (expFwd.exp.sOp=="LC"?expFwd.locCnt:get(expFwd.exp.sOp).addr);
            SymEntry symEntry(true, expFwd.exp.evaluate(fVal, sVal));
            FwdRef f(expFwd.locCnt, expFwd.base, expFwd.e, expFwd.x, expFwd.addr, expFwd.isBase);
            s << (expFwd.e ? symEntry.resolveFormatFour(f) : symEntry.resolveFormatThree(f));
        }
    }
    return {result, s.str()};
}

SymTable::SymTable() = default;


