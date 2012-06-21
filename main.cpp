/**
 * File: main.cpp
 * --------------
 * Manages the central read-eval-loop that 
 * interacts with the user and evaluates all
 * expressions.
 */

#include <iostream>
#include <string>
#include "genlib.h"
#include "expression.h"
#include "evalstate.h"
#include "scanner.h"

/**
 * The main function does little more than manage the
 * high level read-eval-print loop.
 */

int main() {
	EvalState state;
	state.addBuiltins();
	
	Scanner scanner;
	scanner.setSpaceOption(Scanner::IgnoreSpaces);
	scanner.setStringOption(Scanner::ScanQuotesAsStrings);
	
	int line = 1;
	while (true) {
		cout << "little-schemer " << line++ << "> ";
		string expression;
		getline(cin, expression);
		scanner.setInput(expression);
		try {
			Expression *exp = Expression::readExpression(scanner);
			if (exp != NULL) {
				Expression *result = exp->eval(state);
				cout << result->toString() << endl;
			}
		} catch (string errorMsg) {
			cout << "Error: " + errorMsg << endl;
		}
	}
	
	return 0;
}

/**
 * Throws the supplied error message as an exception, designed
 * to be caught near the bottom of the main function.  This
 * version of Error displaces the built-in version of Error,
 * which ends the program whenever it's called.
 *
 * @param string errorMsg the error message that should be
 *        printed to signal a problem before moving on and
 *        prompting the user to enter another expression.
 */

void Error(string errorMsg) {
	throw errorMsg;
}
