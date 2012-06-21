/**
 * File: boolean.cpp
 * -----------------
 * Models a Boolean expression.  All code
 * is self-explanatory.
 */

#include "boolean.h"

BooleanExpression::BooleanExpression(Scanner& scanner) {
	value = (scanner.nextToken() == "true");
}

BooleanExpression::BooleanExpression(bool value) {
	this->value = value;
}

string BooleanExpression::toString() {
	return value ? "true" : "false";
}
