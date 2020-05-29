//
// Created by ahmed on 5/28/20.
//

#include "TextRec.h"
#include "Util.h"

TextRec::TextRec(string startAddress) {
    txt.push_back('T');
    for (int i = startAddress.length(); i < 6; i++) {
        txt.push_back('0');
    }
    txt.append(startAddress);
    txt.append("^00^");
}

int TextRec::getLen() {
    return (int) txt.length();
}

void TextRec::append(string objCode) {
    txt.append(objCode);
}

string TextRec::getTextRecord() {
    int n = ((int) txt.length() - 11)/2;
    string str =(Util::addZeros(Util::decToHex(n), 2));
    txt[8] = str[0];
    txt[9] = str[1];
    if(n==0){
        return "";
    }
    return txt+'\n';
}

TextRec::TextRec() {}
