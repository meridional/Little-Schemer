/**
 * File: symbol.h
 * --------------
 * Manages the class of Expressions that operate more
 * or less as variable that identify (or at least should 
 * identify) general Expressions.  This is the simplest
 * class that actually needs to override the eval() method,
 * because eval needs to consult that EvalState and return
 * whatever the symbol is attached to.
 */

#ifndef __scheme_symbol__
#define __scheme_symbol__

#include "genlib.h"
#include "expression.h"
#include "evalstate.h"
#include <string>

class SymbolExpression : public Expression {

public:
	SymbolExpression(string symbol);
	SymbolExpression(Scanner& s);
	
	Expression *eval(EvalState& state);
	string toString();
	
protected:
	string symbol;
};

#endif // __scheme_symbol__

