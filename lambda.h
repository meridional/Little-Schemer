/**
 * File: lambda.h
 * --------------
 * Helps us model and evaluate lambda expressions, which are
 * Scheme's way of expressing functions.
 */

#ifndef __scheme_lambda__
#define __scheme_lambda__

#include "genlib.h"
#include "expression.h"
#include "callable.h"
#include "symbol.h"
#include "vector.h"

/**
 * Helps us model and evaluate lambda expressions, which are
 * Scheme's way of expressing functions.  For example:
 *
 *   (lambda (x y) (+ x y))
 *
 * is the function that presumably returns the sum of whatever
 * two numbers are supplied as parameters.
 *
 *   (lambda () "hello, world!")
 *
 * is the zero-argument function that always evaluates to the
 * "hello, world!" string.  And:
 *
 *   (lambda (x y) (lambda (z) (+ x y z)))
 *
 * is a two-argument function that evaluates to a one-argument function
 * whose implementation involves whatever the x and y evaluated to.  Deep.
 */

class LambdaExpression : public Callable {

public:
	
	string toString() { return "<lambda>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& state);
    LambdaExpression(Expression *parameterList,
                                       Expression *parameterizedExpression);

protected:
//	Expression * create(Vector<Expression *> & arguments, EvalState& state);
//    Expression * calculate(Vector<Expression *> & arguments, EvalState& localstate);
    Vector<SymbolExpression *> locals;
    Expression * exp;
  //  bool defined = false;
};



#endif
