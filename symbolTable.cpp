 #include <iostream>
 //#include "globals.cpp"
 using namespace std;
 

struct item {
    string name; // to store variable name
    int intValue; // to store value
} symbolTable[100];
int idx = 0; // index to top of symbol table

void add_symbol(string name, int value) {
    symbolTable[idx].name = name;
    symbolTable[idx].intValue = value;
    idx++;
}

void prt_symbol() {
    cout << "Symbol table:";
    cout << "Name\tValue\n";
    for (int i=0; i<idx; i++) {
        cout << symbolTable[i].name << "\t" << symbolTable[i].intValue << endl;
    }
}

bool search_symbol (string lexeme) {
    for (int i=0; i<idx; i++) 
         if (symbolTable[i].name == lexeme) return true;
             return false;
}