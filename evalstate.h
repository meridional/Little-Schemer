/**
 * File: evalstate.h
 * -----------------
 * Manages a collection of symbol-to-expression mappings.  It
 * functions as little more than a Map<Expression *> with a reduced
 * interface that's catered to the needs to our little-schemer 
 * interpreter.
 *
 * Most of the methods are self-explanatory, although two should be
 * called out:
 *
 * + The addBuiltins method populates the EvalState being
 *   constructed with all of the core procedures (like car, cdr, list,
 *   add, equal, etc.)
 * + The add method takes a second EvalState and copies all
 *   of its symbol-expression entries into the receiving EvalState.
 *   If a symbol is defined in both EvalStates, the one inside the
 *   EvalState parameter is used.
 */

#ifndef __scheme_evalstate__
#define __scheme_evalstate__

#include "genlib.h"
#include "map.h"

class EvalState {
	
public:
	void add(EvalState *other);
	void addBuiltins();
	bool containsSymbol(string symbol);
	class Expression *getExpression(string symbol);
	void setExpression(string symbol, class Expression *value);
	
protected:
	Map<class Expression *> entries;
};

#endif // __scheme_evalstate__
