/**
 * File: str.cpp
 * -------------
 */

#include "str.h"
#include <iostream>

StringExpression::StringExpression(string str) {
	this->str = str;
}

StringExpression::StringExpression(Scanner& s) {
	string token = s.nextToken();
	if ((token.size() == 0) || 
		(token[0] != '"') || 
		(token[token.size() - 1] != '"')) {
		Error("A string constant was expected.");
	}
	
	str = token.substr(1, token.size() - 2);
}

string StringExpression::getStr() {
	return str;
}

string StringExpression::toString() {
	return '"' + str + '"';
}

