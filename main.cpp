#include <iostream>
#include "Assembler.h"
#include "Util.h"
using namespace std;

int main() {
    string str;
    cout << ">>To use enter: file path\n>>To exit enter: Exit\n>>";
    cin >> str;
    while (Util::toUpper(str) != "EXIT") {
        Assembler assembler;
        try {
            if (assembler.assemble(str)) {
                cout << "Successful assembly! [Output file Name: objectCode.txt]\n";
            }
        } catch (...) {
        }
        cout << ">>To use enter: file path without quotes\n>>To exit enter: Exit\n>>";
        cin >> str;
    }


    return 0;

}
