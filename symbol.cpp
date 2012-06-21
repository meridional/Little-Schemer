/**
 * File: symbol.cpp
 * ----------------
 */

#include "genlib.h"
#include "symbol.h"

SymbolExpression::SymbolExpression(string symbol) {
	this->symbol = symbol;
}

SymbolExpression::SymbolExpression(Scanner& scanner) {
	symbol = scanner.nextToken();
}

Expression *SymbolExpression::eval(EvalState& state) {
	return state.getExpression(symbol);
}

string SymbolExpression::toString() {
	return symbol;
}
