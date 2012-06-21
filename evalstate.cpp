/**
 * File: evalstate.cpp
 * -------------------
 */

#include "evalstate.h"
#include "specialforms.h"

void EvalState::addBuiltins() {
	setExpression("car", new CarSpecialForm());
	setExpression("cdr", new CdrSpecialForm());
	setExpression("list", new ListSpecialForm());
	setExpression("cons", new ConsSpecialForm());
	setExpression("if", new IfSpecialForm());
	setExpression("quit", new QuitSpecialForm());
	setExpression("define", new DefineSpecialForm());
	setExpression("null", new NullSpecialForm());
	setExpression("lambda", new LambdaSpecialForm());
	setExpression("add", new AddSpecialForm());
	setExpression("subtract", new SubtractSpecialForm());
	setExpression("multiply", new MultiplySpecialForm());
	setExpression("equal", new EqualSpecialForm());
	setExpression("less", new LessSpecialForm());
	setExpression("and", new AndSpecialForm());
	setExpression("or", new OrSpecialForm());
	setExpression("not", new NotSpecialForm());
	setExpression("apply", new ApplySpecialForm());
	setExpression("load", new LoadSpecialForm());
}

bool EvalState::containsSymbol(string symbol) {
	return entries.containsKey(symbol);
}

Expression *EvalState::getExpression(string symbol) {
	if (!containsSymbol(symbol)) {
		Error(symbol + " is not defined.");
	}
	
	return entries[symbol];
}

void EvalState::setExpression(string symbol, Expression *value) {
	entries[symbol] = value;
}

void EvalState::add(EvalState *other) {
	Map<Expression *>::Iterator iter = other->entries.iterator();
	while (iter.hasNext()) {
		string symbol = iter.next();
		this->entries[symbol] = other->entries[symbol];
	}
}
