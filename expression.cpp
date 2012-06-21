/**
 * File: expression.cpp
 * --------------------
 * Provides the implementation of the readExpression factory
 * method, along with its few private helper methods.
 */

#include "expression.h"
#include "scanner.h"
#include "genlib.h"
#include "rational.h"
#include "str.h"
#include "symbol.h"
#include "boolean.h"
#include "lst.h"
#include <iostream>
#include <cctype>

Expression *Expression::readExpression(Scanner& scanner) {
	if (!scanner.hasMoreTokens()) return NULL;
	string lookahead = scanner.nextToken();
	scanner.saveToken(lookahead);
	ExpressionType type = getExpressionType(lookahead);

	switch (type) {
		case Boolean:
			return new BooleanExpression(scanner);
		case Rational:
			return new RationalExpression(scanner); 
		case String:
			return new StringExpression(scanner); 
		case Symbol:
			return new SymbolExpression(scanner);
		case List:
			return new ListExpression(scanner);
		default: 
			Error("Expression type not supported.");
	}
	
	// never gets here, but compilers aren't always smart enough to figure that out
	return NULL;
}

bool Expression::isNumeric(string token) {
	for (int i = 0; i < token.size(); i++) {
		if (!isdigit(token[i])) {
			return false;
		}
	}
	
	return true;
}

Expression::ExpressionType Expression::getExpressionType(string token) {
	if (token == "true" || token == "false")
		return Boolean;
	if (isNumeric(token)) 
		return Rational;
	if (token[0] == '"')
		return String;
	if (token[0] == '(')
		return List;
	return Symbol;
}

void Expression::assertToken(string actual, string expected) {
	if (actual != expected) {
		Error("Got the token \"" + actual + "\" when \"" + 
			  expected + "\" was expected.");
	}
}
