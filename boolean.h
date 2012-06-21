/**
 * File: boolean.h
 * ---------------
 * Helps model and evaluate pure Boolean expressions.
 * Note that *all* expression are interpretable as Booleans, 
 * although only the BooleanExpression of false is 
 * interpreted to be false.  All others are taken
 * to be synonyms for true.
 */

#ifndef __scheme_boolean__
#define __scheme_boolean__

#include "genlib.h"
#include "expression.h"
#include "scanner.h"

class BooleanExpression : public Expression {

public:
	BooleanExpression(Scanner& scanner);
	BooleanExpression(bool value);
	bool isTrue() { return value; }
	string toString();
	
protected:
	bool value;
};

#endif // __scheme_boolean__