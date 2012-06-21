/**
 * File: rational.h
 * ----------------
 * Class designed to manage, manipulate, and evaluate
 * the class of numbers supported by our Little Scheme
 * interpreter.  RationalExressions know how to 
 * stringify and evaluate themselves as all expressions
 * do, but they also respond to some methods that only
 * RationalExpressions understand (add, multiply, 
 * equals, etc.)
 *
 * Fractions are always maintained in reduced form.
 */

#ifndef __scheme_rational__
#define __scheme_rational__

#include "expression.h"

class RationalExpression : public Expression {

public:
	RationalExpression(int numerator = 0, int denominotor = 1);
	RationalExpression(Scanner& s);
	
	string toString();
	
	RationalExpression *add(RationalExpression *other);
	RationalExpression *subtract(RationalExpression *other);
	RationalExpression *multiply(RationalExpression *other);
	
	bool equals(RationalExpression *other);
	bool lessThan(RationalExpression *other);
	
protected:
	int numerator;
	int denominator;
			
private:
	void reduce();
	static int gcd(int a, int b);
};

#endif // __scheme_rational__