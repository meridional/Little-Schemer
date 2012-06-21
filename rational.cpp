/**
 * File: rational.cpp
 * ------------------
 * Created by Jerry Cain on 5/9/09.
 */

#include "genlib.h"
#include "rational.h"
#include "strutils.h"

RationalExpression::RationalExpression(int numerator, int denominator) {
	this->numerator = numerator;
	this->denominator = denominator;
	reduce();
}

RationalExpression::RationalExpression(Scanner& s) {
	this->numerator = StringToInteger(s.nextToken());
	string lookahead = s.nextToken();
	if (lookahead == "/") {
		this->denominator = StringToInteger(s.nextToken());
	} else {
		s.saveToken(lookahead);
		this->denominator = 1;
	}
	
	reduce();
}

string RationalExpression::toString() {
	string stringRep = IntegerToString(numerator);
	if (denominator > 1) {
		stringRep += '/';
		stringRep += IntegerToString(denominator);
	}
	return stringRep;
}

RationalExpression *RationalExpression::add(RationalExpression *other) {
	int numerator = 
		this->numerator * other->denominator +
		this->denominator * other->numerator;
	int denominator = 
		this->denominator * other->denominator;
	
	return new RationalExpression(numerator, denominator); 
}

RationalExpression *RationalExpression::subtract(RationalExpression *other) {
	int numerator = 
		this->numerator * other->denominator -
		this->denominator * other->numerator;
	int denominator = 
		this->denominator * other->denominator;
	
	return new RationalExpression(numerator, denominator); 
}

RationalExpression *RationalExpression::multiply(RationalExpression *other) {
	return new RationalExpression(this->numerator * other->numerator,
							      this->denominator * other->denominator);
}

bool RationalExpression::equals(RationalExpression *other) {
	return 
		this->numerator * other->denominator ==
		this->denominator * other->numerator;
}

bool RationalExpression::lessThan(RationalExpression *other) {
	return 
		this->numerator * other->denominator <
		this->denominator * other->numerator;
}

void RationalExpression::reduce() {
	int divisor = gcd(abs(numerator),
					  abs(denominator));
	numerator /= divisor;
	denominator /= divisor;
	if (denominator < 0) {
		numerator *= -1;
		denominator *= -1;
	}
}

int RationalExpression::gcd(int a, int b) {
	if (a < b) swap(a, b);
	while (b > 0) {
		// gcd(a, b) == gcd(b, a % b);
		int old = a;
		a = b;
		b = old % b;
	}
	
	return a;
}

