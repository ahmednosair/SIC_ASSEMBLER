//
// Created by ahmed on 5/27/20.
//

#include <bits/stdc++.h>
#include "../headers/SymEntry.h"
#include "../headers/TextRec.h"
#include "../headers/Util.h"

using namespace std;

SymEntry::SymEntry(bool isAddressSet, int address) : addrSet(isAddressSet), addr(address) {}

SymEntry::SymEntry() {
    addrSet = false;
}

string SymEntry::resolveFwdRef() {
    stringstream result;
    for (auto &fwdRefer : fwdRefers) {
        if (fwdRefer.e) {
            result << resolveFormatFour(fwdRefer);
        } else {
            result << resolveFormatThree(fwdRefer);
        }
    }
    return result.str();
}

void SymEntry::addFwdRef(FwdRef &fwd) {
    fwdRefers.push_back(fwd);
}

string SymEntry::resolveFormatThree(FwdRef &fwdRefer) const {
    TextRec textRecord(Util::addZeros(Util::decToHex(fwdRefer.addr), 6));
    int val = addr;
    string flags((fwdRefer.x ? "1000" : "0000"));
    if (val - fwdRefer.locCnt >= -2048 && val - fwdRefer.locCnt < 2047) {
        flags[2] = '1';
        val -= (fwdRefer.locCnt );
    } else if (fwdRefer.isBase && val - fwdRefer.base >= 0 && val - fwdRefer.base < 4096) {
        flags[1] = '1';
        val -= fwdRefer.base;
    } else {
        cout << "Out of range addressing for format 3.\nIncomplete assembly!\n";
        throw exception();
    }
    bitset<24> bits(flags + bitset<12>(val).to_string());
    textRecord.append(Util::addZeros(Util::decToHex((int) bits.to_ulong()), 4));
    return textRecord.getTextRecord();
}

string SymEntry::resolveFormatFour(FwdRef &fwdRefer) const {
    TextRec textRecord(Util::addZeros(Util::decToHex(fwdRefer.addr), 6));
    bitset<24> bits((fwdRefer.x ? "1001" : "0001") + bitset<20>(addr).to_string());
    textRecord.append(Util::addZeros(Util::decToHex((int) bits.to_ulong()), 6));
    return textRecord.getTextRecord();
}
