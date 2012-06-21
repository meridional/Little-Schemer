/**
 * File: specialforms.h
 * --------------------
 * Defines a set of classes to model each
 * of the core Callables--car, cons, list, null, etc.
 * The application of each of these callables relies
 * on implementation details that aren't and shouldn't
 * be available to a more generic call, so these are
 * all one-off'ed.  Note that some of them (define, if) 
 * don't even evaluate all of their arguments.
 *
 * All of these are called special forms because they
 * require special treatment.  Either they are so core
 * to the language that they only apply to certain 
 * Expression types (null, car, cdr, add, less), because 
 * they create new lists (cons, list, lambda), don't 
 * evaluate all of their arguments (define, if) like normal
 * functions, or can't be easily implemented in terms of
 * other directives (not).
 */

#ifndef __scheme_special_forms__
#define __scheme_special_forms__

#include <string>
#include "genlib.h"
#include "specialform.h"
#include "evalstate.h"
#include "vector.h"

// models the lambda keyword and provides
// an implementation of call that knows how
// to crawl over its arguments and build
// a LambdaExpression, which itself knows
// how to evaluate itself when applied
// to the correct number of arguments.
class LambdaSpecialForm : public SpecialForm {

public:
	LambdaSpecialForm() {}
	string toString() { return "<builtin lambda>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

// models the define keyword and provides an
// implementation of call that knows to evaluate
// the second argument and bind it to the symbol
// provided via the first argument.
class DefineSpecialForm : public SpecialForm {
	
public:
	DefineSpecialForm() {}
	string toString() { return "<macro define>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

// models the quit function, whose implementation
// of call knows to ignore its arguments (what
// could evaluating them possibly do?) and ends
// the program.
class QuitSpecialForm : public SpecialForm {

public:
	QuitSpecialForm() {}
	string toString() { return "<procedure quit>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

class CarSpecialForm : public SpecialForm {
	
public:
	CarSpecialForm() {}
	string toString() { return "<procedure car>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

class CdrSpecialForm : public SpecialForm {
	
public:
	CdrSpecialForm() {}
	string toString() { return "<procedure cdr>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

class ConsSpecialForm : public SpecialForm {
	
public:
	ConsSpecialForm() {}
	string toString() { return "<procedure cdr>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

class ListSpecialForm : public SpecialForm {
	
public:
	ListSpecialForm() {}
	string toString() { return "<procedure list>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

// Special form that when called expects three
// arguments, evaluates the first one and interprets
// it to be a boolean.  If that bool is true, it
// evaluates to whatever the second argument evalates
// to, and if false evaluates to whatever the third
// argument evaulates to.
class IfSpecialForm : public SpecialForm {
	
public:
	IfSpecialForm() {}
	string toString() { return "<macro if>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

class NullSpecialForm : public SpecialForm {

public:
	NullSpecialForm() {}
	string toString() { return "<procedure null>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);	
};

class AddSpecialForm : public SpecialForm {
	
public:
	AddSpecialForm() {}
	string toString() { return "<procedure add>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

class SubtractSpecialForm : public SpecialForm {
	
public:
	SubtractSpecialForm() {}
	string toString() { return "<procedure subtract>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

class MultiplySpecialForm : public SpecialForm {
	
public:
	MultiplySpecialForm() {}
	string toString() { return "<procedure multiply>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

// core function which knows how to compare two
// rationals for equality
class EqualSpecialForm : public SpecialForm {

public:
	EqualSpecialForm() {}
	string toString() { return "<procedure equal>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

// core function which knows how to compare two
// rationals for inequality.
class LessSpecialForm : public SpecialForm {
	
public:
	LessSpecialForm() {}
	string toString() { return "<procedure less>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

class AndSpecialForm : public SpecialForm {
	
public:
	AndSpecialForm() {}
	string toString() { return "<macro and>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);	
};

class OrSpecialForm : public SpecialForm {
	
public:
	OrSpecialForm() {}
	string toString() { return "<macro or>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);	
};

class NotSpecialForm : public SpecialForm {
	
public:
	NotSpecialForm() {}
	string toString() { return "<procedure not>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);	
};

class ApplySpecialForm : public SpecialForm {
	
public:
	ApplySpecialForm() {}
	string toString() { return "<procedure apply>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);	
};

class LoadSpecialForm : public SpecialForm {
	
public:
	LoadSpecialForm() {}
	string toString() { return "<procedure load>"; }
	Expression *call(Vector<Expression *>& arguments,
					 EvalState& memory);
};

#endif // __scheme_special_forms__
