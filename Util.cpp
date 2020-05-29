//
// Created by ahmed on 5/28/20.
//

#include "Util.h"

string Util::decToHex(int num) {
    stringstream stream;
    stream << hex << num;
    return stream.str();
}

string Util::addZeros(string str, int n) {
    string s(n - str.length(), '0');
    return s + str;
}

string Util::printVector(vector<string> &list) {
    stringstream stream;
    for (auto &i : list) {
        stream << i << " ";
    }
    return stream.str();

}

string Util::strToHex(string str) {
    string result, tmp;
    for (char &c:str) {
        result.append(addZeros(decToHex(c), 2));
    }
    return result;
}

bool Util::isNum(string str) {
    for (char &c:str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}


string Util::toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
