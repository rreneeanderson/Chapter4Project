 #include <iostream>
 using namespace std;

struct item {
    string name; // to store variable name
    int intValue; // to store value
} symbolTable[100];
int index = 0; // index to top of symbol table

void add_symbol(string name, int value) {
    symbolTable[index].name = name;
    symbolTable[index].intValue = value;
    index++;
}

void prt_symbol() {
    cout << "Symbol table:";
    cout << "Name\tValue\n";
    for (int i=0; i<index; i++) {
        cout << symbolTable[i].name << "\t" << symbolTable[i].intValue << endl;
    }
}

bool search_symbol (string lexeme) {
    for (int i=0; i<index; i++) 
         if (symbolTable[i].name == lexeme) return true;
             return false;
}