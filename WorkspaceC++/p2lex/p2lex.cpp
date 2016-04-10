/*
 * p2lex.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: cjdel
 */




/*
 * p2lex.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: gerardryan
 */

#include <map>
using namespace std;

#include "p2lex.h"

// copy constructor
Token::Token(const Token& src)
{
	ttype = src.ttype;
	tlexeme = src.tlexeme;
}

// assignment op
const Token&
Token::operator=(const Token& rhs)
{
	ttype = rhs.ttype;
	tlexeme = rhs.tlexeme;
	return *this;
}

// handy table of string names for token types
map<Token::TokenType,string> TokenNames = {
		{ Token::TokenType::VAR, "var" },		// an identifier
		{ Token::TokenType::SCONST, "sconst" },		// a string enclosed in ""
		{ Token::TokenType::ICONST, "iconst" },		// an integer constant
		{ Token::TokenType::PLUSOP, "plusop" },		// the + operator
		{ Token::TokenType::MINUSOP, "minusop" },	// the - operator
		{ Token::TokenType::STAROP, "starop" },		// the * operator
		{ Token::TokenType::EQOP, "eqop" },		// the assignment op
		{ Token::TokenType::PRINTKW, "printkw" },		// print
		{ Token::TokenType::INTKW, "intkw" },			// int
		{ Token::TokenType::STRKW, "strkw" },			// string
		{ Token::TokenType::LPAREN, "lparen" },		// left parenthesis
		{ Token::TokenType::RPAREN, "rparen" },		// right parenthesis
		{ Token::TokenType::SC, "sc" },		// the semicolon
		{ Token::TokenType::ERR, "err" },		// some error condition was reached
		{ Token::TokenType::DONE,	"done" },	// end of file
};

// handy table to control if lexeme is printed
static map<Token::TokenType,bool> printlexeme = {
		{ Token::TokenType::VAR, true },		// an identifier
		{ Token::TokenType::SCONST, false },
		{ Token::TokenType::ICONST, true },		// an integer constant
		{ Token::TokenType::PLUSOP, false },		// the + operator
		{ Token::TokenType::MINUSOP, false },	// the - operator
		{ Token::TokenType::STAROP, false },		// the * operator
		{ Token::TokenType::EQOP, false },		// the assignment op
		{ Token::TokenType::PRINTKW, false },		// print
		{ Token::TokenType::INTKW, false },			// int
		{ Token::TokenType::STRKW, false },			// string
		{ Token::TokenType::LPAREN, false },		// left parenthesis
		{ Token::TokenType::RPAREN, false },		// right parenthesis
		{ Token::TokenType::SC, false },		// the semicolon
		{ Token::TokenType::ERR, true },		// some error condition was reached
		{ Token::TokenType::DONE, false},	// end of file
};

ostream&
operator<<(ostream& out, const Token& t)
{
	out << TokenNames[t.getType()];
	if( printlexeme[t.getType()] )
		out << "(" << t.getLexeme() << ")";
	return out;
}
