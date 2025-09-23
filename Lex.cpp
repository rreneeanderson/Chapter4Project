#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

//#include "globals.cpp"

static void addChar(char c) {
    lexeme += c;

    if ((int)lexeme.length() > MAX_SIZE - 1) {
        cout << "ERROR: lexeme too long.\n";
        errors++;

    }

}
static char getChar() {
    char c = infp.get();
    if (c == '\n') line++;
    return c;

}
static char getNonSpaceChar() {
    char c = getChar();
    while (isspace((unsigned char)c)) c = getChar();
    return c;

}
static bool isOperator(char c) {
    return (c=='+' || c=='-' || c=='*' || c=='/' ||
            c=='=' || c=='(' || c==')' || c==',');

}
static Tokens lookupKeyword(const string& lx) {
    return (lx == "int") ? INT_KEYWORD : VAR;

}
static Tokens lookupOp(const string& lx) {
    if (lx == "(") return LEFT_PAREN;
    if (lx == ")") return RIGHT_PAREN;
    if (lx == "+") return ADD_OP;
    if (lx == "-") return SUB_OP;
    if (lx == "*") return MUL_OP;
    if (lx == "/") return DIV_OP;
    if (lx == "=") return ASSIGN_OP;
    if (lx == ",") return COMMA;
    return UNKNOWN;

}
void prt(Tokens t) {
    switch (t) {
        case INT_KEYWORD: cout << "<INT_KEYWORD>"; break;
        case VAR:         cout << "<VAR>"; break;
        case INT_LIT:     cout << "<INT_LIT>"; break;
        case ASSIGN_OP:   cout << "<ASSIGN_OP>"; break;
        case ADD_OP:      cout << "<ADD_OP>"; break;
        case SUB_OP:      cout << "<SUB_OP>"; break;
        case MUL_OP:      cout << "<MUL_OP>"; break;
        case DIV_OP:      cout << "<DIV_OP>"; break;
        case LEFT_PAREN:  cout << "<LEFT_PAREN>"; break;
        case RIGHT_PAREN: cout << "<RIGHT_PAREN>"; break;
        case COMMA:       cout << "<COMMA>"; break;
        case ENDFILE:     cout << "<ENDFILE>"; break;
        default:          cout << "<UNKNOWN>"; break;

    }

}
void lex() {
    lexeme.clear();
    if (!infp.good()) { nextToken = ENDFILE; return; }
    int pk = infp.peek();
    if (pk == EOF) { nextToken = ENDFILE; return; }
    char nextChar = getNonSpaceChar();
    if (infp.eof()) { nextToken = ENDFILE; return; }
    if (isalpha((unsigned char)nextChar) || nextChar == '_') {

        while (isalpha((unsigned char)nextChar) ||
               isdigit((unsigned char)nextChar) || nextChar == '_') {
            addChar(nextChar);
            nextChar = getChar();
            if (infp.eof()) break;

        }
        if (!infp.eof()) infp.unget();
        nextToken = lookupKeyword(lexeme);
        return;

    }
    if (isdigit((unsigned char)nextChar)) {
        while (isdigit((unsigned char)nextChar)) {
            addChar(nextChar);
            nextChar = getChar();
            if (infp.eof()) break;

        }
        if (!infp.eof()) infp.unget();
        nextToken = INT_LIT;
        return;

    }
    if (isOperator(nextChar)) {
        string s(1, nextChar);
        nextToken = lookupOp(s);
        return;

    }
    nextToken = UNKNOWN;

}

