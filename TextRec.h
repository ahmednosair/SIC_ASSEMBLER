//
// Created by ahmed on 5/28/20.
//

#ifndef SIC_ASSEMBLER_TEXTREC_H
#define SIC_ASSEMBLER_TEXTREC_H

#include <bits/stdc++.h>

using namespace std;

class TextRec {
private:
    string txt;
public:
    TextRec(string startAddress);

    TextRec();

    int getLen();

    void append(string objCode);

    string getTextRecord();


};


#endif //SIC_ASSEMBLER_TEXTREC_H
