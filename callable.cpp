/**
 * File: callable.cpp
 * ------------------
 * Provides the implementation of Callable's one
 * protected method.  Note that the arguments
 * Vector is passed in by reference, and it's
 * updated in place.
 */

#include "callable.h"

void Callable::evaluateAllArguments(Vector<Expression *>& arguments,
									EvalState& state)
{
	for (int i = 0; i < arguments.size(); i++) {
		arguments[i] = arguments[i]->eval(state);
	}
}
