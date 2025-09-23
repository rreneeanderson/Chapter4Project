#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

#include "Q2Tokenizer.cpp"

Tokens AParser(Tokens nextToken);
Tokens BParser(Tokens nextToken);
Tokens CParser(Tokens nextToken);
Tokens S(Tokens nextToken);


Tokens AParser(Tokens nextToken) {
    if (nextToken == A) {
        while (nextToken == A) {
            nextToken = tokenizer();
        }
    } else {
        errMsg("Expectng A");
        }
        return nextToken;
    }
    
Tokens BParser(Tokens nextToken) {
    if (nextToken == B) {
        while (nextToken == B) {
            nextToken = tokenizer();
        }
    } else {
        errMsg("Expectng B");
        }
        return nextToken;
    }
    Tokens CParser(Tokens nextToken) {
    if (nextToken == C) {
        while (nextToken == C) {
            nextToken = tokenizer();
        }
    } else {
        errMsg("Expectng C");
        }
        return nextToken;
    }
    Tokens S(Tokens nextToken) {
        nextToken = AParser(nextToken); 
            if (nextToken == C) {
                nextToken = CParser(nextToken);
                nextToken = BParser(nextToken);
            }
        return nextToken;
    }
    int main() {
	    infp.open("prg3.in");
	    if (!infp) {
		cout << "ERROR - cannot open file prg3.in\n";
		errors++;
	}
		nextChar = ' ';
		Tokens nextToken = tokenizer();
		do {
			nextToken = S (nextToken);
			if (errors > 10) break;
		} while (nextToken != ENDFILE);
	cout << "Total number of errors: " << errors << endl;

infp.close();
	return (errors == 0) ? 0 : 1;
}

