//
// Created by ahmed on 5/27/20.
//

#ifndef SIC_ASSEMBLER_SYMTABLE_H
#define SIC_ASSEMBLER_SYMTABLE_H

#include <bits/stdc++.h>
#include "SymEntry.h"

using namespace std;


class SymTable {
public:
    SymTable();

    bool search(string &sym);

    void add(string &sym, int address);

    void add(string &sym);

    void updateSymEntry(string &sym, int address, bool isAddressSet);

    void addFwdRef(string &sym, FwdRef fwd);

    SymEntry &get(string &sym);

    void addExpFwdRef(ExpFwdRef fwd);

    vector<string> getUnresolved();

    pair<vector<string>, string> getUnresolvedExp();

private:
    unordered_map<string, SymEntry> table;
    vector<ExpFwdRef> expFwdRefers;

};


#endif //SIC_ASSEMBLER_SYMTABLE_H
