//
// Created by ahmed on 5/28/20.
//

#ifndef SIC_ASSEMBLER_UTIL_H
#define SIC_ASSEMBLER_UTIL_H

#include <bits/stdc++.h>

using namespace std;

class Util {
public:
    static string decToHex(int num);

    static string addZeros(string str, int n);

    static string printVector(vector<string> &list);

    static string strToHex(string str);

    static bool isNum(string str) ;

    static string toUpper(string str);
};


#endif //SIC_ASSEMBLER_UTIL_H
