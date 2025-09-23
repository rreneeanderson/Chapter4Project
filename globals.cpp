#include <iostream>
#include <fstream>
#include <string>
#pragma once
using namespace std;


enum Tokens {INT_LIT, INT_KEYWORD, DECL, VAR, ASSIGN_OP, ADD_OP, SUB_OP, MUL_OP, DIV_OP, 
             LEFT_PAREN, RIGHT_PAREN, LETTER, DIGIT, COMMA, UNKNOWN, ENDFILE};


const int MAX_SIZE = 100; // maximum size per line
string lexeme = ""; // current lexeme
Tokens nextToken;
int errors = 0; // keep track of number of errors
int line = 1;  // keep track of current line reache
ifstream infp;

void errMsg (string msg)
{
    cout << "Error at line: " << line << ": " << msg << endl;
    errors++;
    //lex();
}