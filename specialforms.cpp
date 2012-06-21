/**
 * File: specialforms.cpp
 * ----------------------
 */

#include "specialforms.h"
#include "expression.h"
#include "lst.h"
#include "symbol.h"
#include "boolean.h"
#include "set.h"
#include "lambda.h"
#include "rational.h"
#include "str.h"
#include "scanner.h"
#include <iostream>
using namespace std;
Expression *DefineSpecialForm::call(Vector<Expression *>& arguments,
									EvalState& state) {
	if (arguments.size() != 2) {
		Error("define expects exactly two arguments");
	}
	
	SymbolExpression *symbol = dynamic_cast<SymbolExpression *>(arguments[0]);
	if (symbol == NULL) {
		Error("The first argument to define by be a symbol");
	}
	Expression *value = arguments[1];
	
	state.setExpression(symbol->toString(), 
						value->eval(state));
	return symbol;
}

Expression *QuitSpecialForm::call(Vector<Expression *>& arguments,
								  EvalState& state) {
	cout << endl;
	cout << "[Press <return> to close]";
	string dummy;
	getline(cin, dummy);
	exit(0);
	return this; // hush the compiler
}

Expression *CarSpecialForm::call(Vector<Expression *>& arguments,
								 EvalState& state) {
	if (arguments.size() != 1) {
		Error("car expects exactly one argument");
	}
	
	evaluateAllArguments(arguments, state);
	ListExpression *listArgument = 
		dynamic_cast<ListExpression *>(arguments[0]);
	if (listArgument == NULL) {
		Error("car expects its one argument to be a list");
	}
	
	return listArgument->car();
}

Expression *CdrSpecialForm::call(Vector<Expression *>& arguments,
								 EvalState& state) {
	if (arguments.size() != 1) {
		Error("cdr expects exactly one argument.");
	}
	
	evaluateAllArguments(arguments, state);
	ListExpression *listArgument = 
		dynamic_cast<ListExpression *>(arguments[0]);
	if (listArgument == NULL) {
		Error("cdr expects its one argument to be a list.");
	}
	
	return listArgument->cdr();
}

Expression *ConsSpecialForm::call(Vector<Expression *>& arguments,
								  EvalState& state) {	
	if (arguments.size() != 2) {
		Error("cons expects precisely two arguments.");
	}
	
	evaluateAllArguments(arguments, state);
	Expression *newCar = arguments[0];
	ListExpression *newCdr = dynamic_cast<ListExpression *>(arguments[1]);
	if (newCdr == NULL) {
		Error("Second argument passed to cons must be a list.");
	}
	
	return new ListExpression(newCar, newCdr);
}

Expression *ListSpecialForm::call(Vector<Expression *>& arguments,
								  EvalState& state) {	
	evaluateAllArguments(arguments, state);
	return new ListExpression(arguments);
}

Expression *IfSpecialForm::call(Vector<Expression *>& arguments,
								EvalState& state) {	
	if (arguments.size() != 3) {
		Error("if expressions expect precisely three arguments.");
	}
	
	if (arguments[0]->eval(state)->isTrue())
		return arguments[1]->eval(state);
	else
		return arguments[2]->eval(state);
}

Expression *NullSpecialForm::call(Vector<Expression *>& arguments,
								  EvalState& state)
{	
	if (arguments.size() != 1) {
		Error("null expressions take just one argument.");
	}
	
	evaluateAllArguments(arguments, state);
	ListExpression *list = 
		dynamic_cast<ListExpression *>(arguments[0]);
	if (list == NULL) {
		Error("null expects a list and only a list");
	}
	
	return new BooleanExpression(list->isEmpty());
}

Expression *AddSpecialForm::call(Vector<Expression *>& arguments,
								EvalState& state)
{		
	evaluateAllArguments(arguments, state);
	RationalExpression *sum = new RationalExpression(0);
	for (int i = 0; i < arguments.size(); i++) {
		RationalExpression *addend = 
			dynamic_cast<RationalExpression *>(arguments[i]);
		if (addend == NULL) {
			Error("add expects all arguments to be rational numbers.");
		}
		sum = sum->add(addend);
	}
	return sum;
}

Expression *SubtractSpecialForm::call(Vector<Expression *>& arguments,
								      EvalState& state)
{		
	if (arguments.size() != 2) {
		Error("subtract takes precisely two arguments.");
	}
	evaluateAllArguments(arguments, state);
	RationalExpression *minuend = 
		dynamic_cast<RationalExpression *>(arguments[0]);
	RationalExpression *subtrahend =
		dynamic_cast<RationalExpression *>(arguments[1]);
	if (minuend == NULL || subtrahend == NULL) {
		Error("subtract only takes rational numbers as arguments.");
	}
	
	return minuend->subtract(subtrahend);
}

Expression *MultiplySpecialForm::call(Vector<Expression *>& arguments,
								      EvalState& state)
{		
	evaluateAllArguments(arguments, state);
	RationalExpression *product = new RationalExpression(1);
	for (int i = 0; i < arguments.size(); i++) {
		RationalExpression *factor = 
			dynamic_cast<RationalExpression *>(arguments[i]);
		if (factor == NULL) {
			Error("multiply expects all arguments to be rational numbers.");
		}
		product = product->multiply(factor);
	}
	return product;
}

Expression *EqualSpecialForm::call(Vector<Expression *>& arguments,
								   EvalState& state)
{		
	if (arguments.size() != 2) {
		Error("equal takes precisely two rational arguments.");
	}
	
	evaluateAllArguments(arguments, state);
	RationalExpression *first = 
		dynamic_cast<RationalExpression *>(arguments[0]);
	RationalExpression *second =
		dynamic_cast<RationalExpression *>(arguments[1]);
	if (first == NULL || second == NULL) {
		Error("equal only takes rational numbers as arguments.");
	}
	
	return new BooleanExpression(first->equals(second));
}

Expression *LessSpecialForm::call(Vector<Expression *>& arguments,
								  EvalState& state)
{		
	if (arguments.size() != 2) {
		Error("less takes precisely two rational arguments.");
	}
	
	evaluateAllArguments(arguments, state);
	RationalExpression *first = 
		dynamic_cast<RationalExpression *>(arguments[0]);
	RationalExpression *second =
		dynamic_cast<RationalExpression *>(arguments[1]);
	if (first == NULL || second == NULL) {
		Error("less only takes rational numbers as arguments.");
	}
	
	return new BooleanExpression(first->lessThan(second));
}

Expression *LoadSpecialForm::call(Vector<Expression *>& arguments,
								  EvalState &state) {
	if (arguments.size() != 1) {
		Error("load requires precisely one argument.");
	}
	
	evaluateAllArguments(arguments, state);
	
	StringExpression *fileExp = dynamic_cast<StringExpression *>(arguments[0]);
	if (fileExp == NULL) {
		Error("load's argument must be a string.");
	}
	string filename = fileExp->getStr();
	
	ifstream fs;
	fs.open(filename.c_str());
	if (fs.fail()) {
		Error("file does not exist.");
	}
	
	// remove all newlines - the scanner treats them as tokens
	string input = "";
	while (fs.peek() != EOF) {
		string line;
		getline (fs, line);
		if (line.size() > 0 && line[0] == ';') {
			continue;
		}
		input += " " + line;
	}
	
	Scanner scanner;
	scanner.setSpaceOption(Scanner::IgnoreSpaces);
	scanner.setStringOption(Scanner::ScanQuotesAsStrings);	
	scanner.setInput(input);
	
	Expression *res = NULL;
	Expression *exp = NULL;		
	do {
		exp = Expression::readExpression(scanner);
		if (exp != NULL) {
			res = exp->eval(state);		
		}
	} while (exp != NULL);
	return res;
}

Expression *LambdaSpecialForm::call(Vector<Expression *>& arguments,
									EvalState& state) {
	if (arguments.size() < 2) {
        Error("Lambda expects at least 2 arguments");
    }
    LambdaExpression * newLambda = new LambdaExpression(arguments[0], arguments[1]);
    
    if (arguments.size() == 2) {
        return newLambda;
    }
    else {
        
        arguments.removeAt(0);
        arguments.removeAt(0);
   //     cout << arguments.size() << endl;
        return newLambda->call(arguments, state);
    }
}

Expression *AndSpecialForm::call(Vector<Expression *>& arguments,
								EvalState& state) {		
	//Error("AndSpecialForm::call not supported yet");
    if (arguments.size() == 0) {
        return new BooleanExpression(true);
    }
    Expression * evaled;
    for (int i = 0; i <= arguments.size() - 1; ++i) {
        evaled = arguments[i]->eval(state);
        if (!evaled->isTrue()) {
            return new BooleanExpression(false);
        }
    }
	return evaled;
}

Expression *OrSpecialForm::call(Vector<Expression *>& arguments,
								EvalState& state) {		
	//Error("OrSpecialForm::call not supported yet");
    if (arguments.size() == 0) {
        return  new BooleanExpression(false);
    }
    Expression * eval;
    for (int i = 0; i <= arguments.size() - 1; ++i) {
        eval = arguments[i]->eval(state);
        if (eval->isTrue()) {
            return eval;
        }
    }
	return new BooleanExpression(false);
}

Expression *NotSpecialForm::call(Vector<Expression *>& arguments,
								 EvalState& state) {		
	//Error("NotSpecialForm::call not supported yet");
    if (arguments.size() != 1) {
        Error("not takes exactly one argument!");
    }
    Expression * eval = arguments[0]->eval(state);
    if (eval->isTrue()) {
        return new BooleanExpression(false);
    }
    
	return new BooleanExpression(true);
}

Expression *ApplySpecialForm::call(Vector<Expression *>& arguments,
								   EvalState& state) {
    if (arguments.size() != 2) {
        Error("apply should take exactly 2 arguments.");
    }
    Callable * called = dynamic_cast<Callable *>(arguments[0]->eval(state));
    if (called == NULL) {
        Error("The first argument of apply should be a callable");
    }
    ListExpression * list = dynamic_cast<ListExpression *>(arguments[1]->eval(state));
    if (list == NULL) {
        Error("The 2nd argument of apply procedure should be evaluated to a list");
    }
    Vector<Expression *> args;
    while (!list->isEmpty()) {
        args.add(list->car());
        list = list->cdr();
    }
    
	return called->call(args, state);
}
