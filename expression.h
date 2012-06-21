/**
 * File: expression.h
 * ------------------
 * Sits as the parent abstract class that all concrete 
 * expression classes extend and implement.  All Expressions—-
 * both lists and primitives—-need to be able to self-serialize 
 * and self-evaluate.  
 * 
 * Note that all expression values
 * (except for a BooleanExpression surrounding a false)
 * are synonymous with Boolean true.  We reflect that
 * by inlining the implementation of an isTrue method
 * to return true and assume that most subclasses will
 * prefer to inherit that implementation without overriding
 * it.
 */

#ifndef __scheme_expression__
#define __scheme_expression__

#include "genlib.h"
#include "scanner.h"
#include "evalstate.h"
#include "map.h"

class Expression {
	
public:
	virtual ~Expression() {}
	virtual Expression *eval(EvalState& state) { return this; }
	virtual bool isTrue() { return true; }
	virtual string toString() = 0;
	
	static Expression *readExpression(Scanner& scanner);
	
protected:
	Expression() {}
	enum ExpressionType {
		Boolean,
		Rational,
		String,
		Symbol,
		List
	};
	
	static ExpressionType getExpressionType(string lookahead);
	static void assertToken(string actual, string expected);
	static bool isNumeric(string token);
};

#endif // __scheme_expression__
