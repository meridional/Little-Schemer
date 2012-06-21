/**
 * File: schemelist.h
 * ------------------
 * Helps manage the notion of a Scheme list.
 * Recall that some lists are function calls,
 * and some lists are pure data lists.  This
 * class manages both of them.  Note that
 * when these lists are asked to evaluate themselves,
 * the car of the list is assumed to be a Callable,
 * and the cdr of the list identifies all of the
 * arguments that need to be fed to that Callable.
 * 
 * You're well aware that we need to be able to
 * support car, cdr
 */

#ifndef __scheme_list__
#define __scheme_list__

#include "genlib.h"
#include "expression.h"
#include "vector.h"

class ListExpression : public Expression {
	
public:
	ListExpression(Scanner& scanner);
	
	string toString();
	Expression *eval(EvalState& state);

	// constructors and methods in place to make the
	// implementation of car, cdr, cons, list, and null.
	Expression *car();
	ListExpression *cdr();
	ListExpression(Expression *first, ListExpression *rest);
	ListExpression(Vector<Expression *>& expressions);
	bool isEmpty() { return head == NULL; }
	
protected:
	struct ConsCell {
		Expression *car;
		ConsCell *cdr;
		ConsCell(Expression *car, ConsCell *cdr);
	};
	
	ConsCell *head;
	ListExpression(ConsCell *head);
};

#endif // __scheme_list__