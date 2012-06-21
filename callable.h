/**
 * File: callable.h
 * ----------------
 * A Callable is an abstract class that extends Expression
 * that forces subclasses to not only implement eval and
 * toString methods, but also a call method.
 */

#ifndef __scheme_callable__
#define __scheme_callable__

#include "expression.h"
#include "map.h"
#include "vector.h"

class Callable : public Expression {
	
public:
	
/**
 * Evaluates the application of the Callable 
 * expression to the ordered set of argumments in the 
 * context of the evaluation state called memory.  In all
 * cases, the arguments are raw expressions that have 
 * yet to be evaluated.
 */
	
	virtual Expression *call(Vector<Expression *>& arguments,
							 EvalState& state) = 0;

protected:

/**
 * Convenience method available to subclasses that accepts a
 * Vector of un-evaluated arguments and updates that Vector,
 * in place, to contain all of their evaluations.
 */
	void evaluateAllArguments(Vector<Expression *>& arguments,
							  EvalState& state);
							  
};

#endif //  __scheme_callable__
