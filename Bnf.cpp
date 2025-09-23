#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

#include "globals.cpp"
#include "Lex.cpp"
#include "symbolTable.cpp"

void lex();
void errMsg(string msg);
bool search_symbol(string name);
void add_symbol(string name, int value);
void prt_symbol();

void expr();
void term();
void factor();
void assign();
void initializeVar();
void intVar();
void declaration();
void stmt();
void program();

void expr() {
    term();
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();

    }

}
void term() {
    factor();
    while (nextToken == MUL_OP || nextToken == DIV_OP) {
        lex();
        factor();

    }

}
void factor() {
    if (nextToken == VAR || nextToken == INT_LIT) {
        lex();
    } else if (nextToken == LEFT_PAREN) {
        lex();
        expr();
        if (nextToken == RIGHT_PAREN) lex();
        else errMsg("Right parenthesis expected, found " + lexeme);
    } else {
        errMsg("Expected VAR, INT_LIT, or '(', found " + lexeme);

        lex();

    }

}
void assign() {
    if (nextToken == VAR) {
        if (!search_symbol(lexeme)) errMsg("Undefined variable " + string(lexeme));
        lex();
        if (nextToken == ASSIGN_OP) {
            lex();
            expr();

        } else {
            errMsg("Equal sign expected, found " + string(lexeme));

        }
    } else {
        errMsg("Variable expected, found " + string(lexeme));
        lex();

    }

}
void initializeVar() {
    if (nextToken != VAR) { errMsg("Variable expected, found " + string(lexeme)); return; }
    string varName = lexeme;
    lex();
    if (nextToken == ASSIGN_OP) {
        lex();
        if (nextToken == INT_LIT) {
            int value = atoi(lexeme.c_str());
            add_symbol(varName, value);
            lex();
        } else {
            errMsg("Integer initialization expected, found " + string(lexeme));
            add_symbol(varName, 0);

        }
    } else {
        add_symbol(varName, 0);
    }

}
void intVar() {
    if (nextToken == VAR) {
        initializeVar();
        while (nextToken == COMMA) {
            lex();
            if (nextToken == VAR) initializeVar();
            else { errMsg("Variable expected after comma, found " + string(lexeme)); break; }

        }
    } else {
        errMsg("Variable expected, found " + string(lexeme));

    }

}
void declaration() {
    if (nextToken == INT_KEYWORD) {
        lex();
        intVar();
    } else {
        errMsg("'int' keyword expected, found " + string(lexeme));

    }

}
void stmt() {
    if (nextToken == INT_KEYWORD) declaration();
    else assign();

}
void program() {
    while (nextToken != ENDFILE) {
        stmt();
        if (errors > 200) break;

    }

}
int main() {
    infp.open("prg1_bad_line2.in");
    if (!infp) {
        errMsg("ERROR - cannot open file");
        return 1;

    }
    lex();
    program();
    prt_symbol();
    cout << "Total number of errors: " << errors << endl;
    infp.close();
    return 0;

}