//
// Created by ahmed on 5/27/20.
//

#ifndef SIC_ASSEMBLER_SYMENTRY_H
#define SIC_ASSEMBLER_SYMENTRY_H

#include <bits/stdc++.h>
#include "FwdRef.h"
#include "ExpFwdRef.h"

using namespace std;


class SymEntry {
public:
    SymEntry();

public:
    SymEntry(bool isAddressSet, int address);

public:
    bool addrSet{};
    int addr{};
    vector<FwdRef> fwdRefers;
    string resolveFwdRef();
    void addFwdRef(FwdRef &fwd);
    string resolveFormatThree(FwdRef &fwdRefer) const;
    string resolveFormatFour(FwdRef &fwdRefer) const;

};


#endif //SIC_ASSEMBLER_SYMENTRY_H
