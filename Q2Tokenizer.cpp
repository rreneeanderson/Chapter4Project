#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <cctype>
#include <string>
using namespace std;

ifstream infp;

enum Tokens { A, B, C, ENDFILE = 80, UNKNOWN= 99 };
			
const int SIZE = 100;
Tokens nextToken;
string lexeme;
char nextChar;

int errors = 0; // counter error 
int line = 1;   // source code
// print token line 
void prt (Tokens nt) {
	switch (nt) {
	case A:       cout << "<A>";      break;
	case B:       cout << "<B>";      break;
	case C:       cout << "<C>";      break;
	case ENDFILE: cout << "<ENDFILE>";break;	
	case UNKNOWN: cout << "<UNKNOWN>";break;
	}
};

//error message with line #
void errMsg (string msg) {
	cout << "Error at line: " << line << ": " << msg << endl;
	errors++;
}

void addChar(char nextChar) {
	lexeme += nextChar;
	if (lexeme.size() > 99) {
		errMsg ("Lexeme size exceeds 100 characters");
		exit(0);
	}
}
char getChar() {
	char ch = infp.get();
	if (ch == '\n') line++;
	return ch;
}
char getNonSpaceChar() {
	char ch = ' ';
	while (isspace(static_cast<unsigned char>(ch))) {
        if (!infp) return EOF;
		ch = getChar();
	}
	return ch;
}
Tokens lookupKeywords () {
	if (lexeme == "a") return A;
	if (lexeme == "b") return B;
	if (lexeme == "c") return C;
    return UNKNOWN;
}
Tokens tokenizer() {
	Tokens t = ENDFILE;
	lexeme.clear();

	if (isspace(static_cast<unsigned char>(nextChar))) 
        nextChar = getNonSpaceChar();
    if (!infp) {
        t = ENDFILE;
        lexeme = "EOF";
    }
	else if (nextChar == 'a') {
		t = A; lexeme = nextChar; nextChar = getChar();
	}
	else if (nextChar == 'b') {
		t = B; lexeme = nextChar; nextChar = getChar();	
	}
	else if (nextChar == 'c') {
		t = C; lexeme = nextChar; nextChar = getChar();	
    }
	else if (infp.eof()) {
			t = ENDFILE; lexeme = "EOF";
	}
	else {
        t = UNKNOWN;
        addChar(nextChar);
        nextChar = getChar();
    }
  cout << "Token read:\t"; prt(t); 
  cout << " \tLexeme:\t " << lexeme << endl;
  
  return t;
}
/*
int main() {
	infp.open(".\\prg3.in");
	if (!infp) {
		cout << "ERROR - cannot open file prg3.in\n";
		errors++;
        return 1;
	} else {
		nextChar = ' ';
		do {
			nextToken = tokenizer();
		} while (nextToken != ENDFILE);
	
	cout << "Total number of errors: " << errors << endl;
    infp.close();
	return 0;
    }
}
    */
