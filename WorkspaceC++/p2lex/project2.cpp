/*
 * project2.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: cjdel
 */




/*
 * ProjectTwo.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: gerardryan
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

#include "p2lex.h"

int linenum = 1;

void
usage(const string& cmd, const string& msg) {
	cout << msg << endl;
	cout << "Usage is: " << cmd << " [-v] filename" << endl;
}

int
main(int argc, char *argv[])
{
    istream *br = &cin;
    ifstream infile;

    bool	verbose = false;

    for( int i=1; i<argc; i++ ) {
    	if( i == 1 && string(argv[i]) == "-v" )
    		verbose = true;
    	else {
    		if( br != &cin ) {
    			usage(argv[0], "too many file name arguments specified");
    			return 1;
    		}
            infile.open(argv[i]);
            if( infile.is_open() )
                    br = &infile;
            else {
                    usage(argv[0], "Cannot open " + string(argv[i]));
                    return 1;
            }
    	}
    }

    map<Token::TokenType,int> tokenCount;
    map<string,int> lexemeCount;
    Token t;

	while( (t = getToken(br)) != Token::TokenType::DONE && t != Token::TokenType::ERR ) {
		tokenCount[t.getType()]++;
		if( t == Token::TokenType::VAR
				|| t == Token::TokenType::SCONST
				|| t == Token::TokenType::ICONST ) {
			lexemeCount[t.getLexeme()]++;
		}

		if( verbose )
			cout << t << endl;
	}

	if( t == Token::TokenType::ERR ) {
		cout << t << endl;
		return 1;
	}

	extern map<Token::TokenType,string> TokenNames;
	bool printedHeader = false;
	for( pair<Token::TokenType,int> c : tokenCount ) {
		if( !printedHeader ) {
			printedHeader = true;
			cout << "Token counts:" << endl;
		}

		cout << TokenNames[c.first] << ":" << c.second << endl;
	}

	printedHeader = false;
	for( pair<string,int> l : lexemeCount ) {
		if( l.second == 1 ) continue;

		if( !printedHeader ) {
			printedHeader = true;
			cout << "Lexemes that appear more than once:" << endl;
		}

		cout << l.first << " (" << l.second << " times)" << endl;
	}

	return 0;
}
