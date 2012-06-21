/**
 * File: str.h
 * -----------
 * Manages the notion of a string constant.  This
 * class does the mimimal amount of work needed to
 * model a string constant while implementing the
 * interface imposed by its parent.
 *
 * By the way, this file is named str.h because string.h
 * is already taken.
 */

#ifndef __scheme_string__
#define __scheme_string__

#include "expression.h"

class StringExpression : public Expression {
	
public:
	StringExpression(string str);
	StringExpression(Scanner& s);
	string getStr();
	
	string toString();

protected:
	string str;
};

#endif // __scheme_string__
