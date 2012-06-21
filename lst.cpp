/**
 * File: lst.cpp
 */

#include "genlib.h"
#include "lst.h"
#include "lambda.h"
//#include <iostream>
/**
 * Constructs a ListExpression out of the material
 * embedded inside the scanner.  It's assumes that the
 * opening parenthesis of the general list has already been
 * consumed, but that everything beyond that initial parenthesis
 * is still intact.
 */

ListExpression::ListExpression(Scanner& scanner) {
	assertToken(scanner.nextToken(), "(");
	Vector<Expression *> expressions;
	while (true) {
		if (!scanner.hasMoreTokens()) {
			Error("Incomplete list expression");
		}
		string lookahead = scanner.nextToken();
		if (lookahead == ")") break;
		scanner.saveToken(lookahead);
		expressions.add(readExpression(scanner));
	}
	
	head = NULL;
	for (int i = expressions.size() - 1; i >= 0; i--) {
		head = new ConsCell(expressions[i], head);
	}
}

ListExpression::ListExpression(Expression *first, ListExpression *rest) {
	head = new ConsCell(first, rest->head);
}

ListExpression::ListExpression(Vector<Expression *>& expressions) {
	head = NULL;
  //  std::cout << expressions.size() << std::endl;
	for (int i = expressions.size() - 1; i >= 0; i--) {
		head = new ConsCell(expressions[i], head);
	}
//    std::cout << (head==NULL) << std::endl;
}

/**
 * Internally managed constructor that allows us to wrap a
 * ListExpression around a list of previously constructed
 * ConsCells.  This isn't exposed to the client, and exists to
 * make the implementation of cdr very simple.
 */

ListExpression::ListExpression(ListExpression::ConsCell *head) {
	this->head = head;
}

/**
 * Self-explanatory, though note there's no evaluation done at all...
 * just recursive toString calls.
 */

string ListExpression::toString()
{
	if (head == NULL) {
		return "()";
	}
	
	string serialization;
	ConsCell *curr = head;
	while (true) {
		serialization += curr->car->toString();
		curr = curr->cdr;
		if (curr == NULL) break;
		serialization += " ";
	}
	
	return "(" + serialization + ")";
}

Expression *ListExpression::eval(EvalState& state) {
	if (head == NULL) {
		Error("Function evaluation requires a procedure " 
			  "be present in the front position.");
	}
	
	Expression *leadingExpresison = head->car->eval(state);
	Callable *callable = 
		dynamic_cast<Callable *>(leadingExpresison);
	if (callable == NULL) {
		Error("Function evaluation requires a procedure " 
			  "be present in the front position.");
	}
	
	Vector<Expression *> arguments;
	for (ConsCell *curr = head->cdr; curr != NULL; curr = curr->cdr) {
		arguments.add(curr->car);
	}
	
	return callable->call(arguments, state);
}

Expression *ListExpression::car() {
	if (head == NULL) {
		Error("The empty list has no car.");
	}
	
	return head->car;
}

ListExpression *ListExpression::cdr() {
	if (head == NULL) {
		Error("The empty list has no cdr.");
	}
	
	return new ListExpression(head->cdr);
}

/**
 * Convenience constructor that helps with the ListExpression
 * constructor and the implementation of cons.
 */

ListExpression::ConsCell::ConsCell(Expression *car,
								   ListExpression::ConsCell *cdr) {
	this->car = car;
	this->cdr = cdr;
}

