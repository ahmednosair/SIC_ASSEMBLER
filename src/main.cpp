#include <iostream>
#include "../headers/Assembler.h"
#include "../headers/Util.h"

using namespace std;

int main() {
    Assembler assembler;
    string str;
    cout << "Welcome to SIC/XE assembler\n\n";
    cout << ">>To use enter: Source file path without quotes.\n>>To exit enter: Exit.\n>>";
    cin >> str;
    while (Util::toUpper(str) != "EXIT") {
        try {
            if (assembler.assemble(str)) {
                assembler.createListFile();
                cout << "\nSuccessful assembly! [Output Files: objectCode.txt, ListFile.txt]\n";
            }
        } catch (...) {
        }
        cout << "\n";
        cout << ">>To use enter: Source file path without quotes.\n>>To exit enter: Exit.\n>>";
        cin >> str;
    }


    return 0;

}
