/**
 * File: lambda.cpp
 * ----------------
 */

#include "genlib.h"
#include "lambda.h"
#include "symbol.h"
#include "strutils.h"
#include "lst.h"
#include <iostream>
using namespace std;
LambdaExpression::LambdaExpression(Expression *parameterList,
								   Expression *parameterizedExpression){
  //  cout << "New lambda" << endl;
    ListExpression * paraList = dynamic_cast<ListExpression *>(parameterList);
    if (paraList == NULL) {
        Error("Lambda expression expects its 1st argument to be a list");
    }
    while (!paraList->isEmpty()) {
        SymbolExpression * tmpSymb = dynamic_cast<SymbolExpression *>(paraList->car());
        paraList = paraList->cdr();
        if (tmpSymb == NULL) {
            Error("Lambda expression expects its 1st argument to be a list of symbolic expressions");
        }
        locals.add(tmpSymb);
    }
    exp = parameterizedExpression;
}

/**
 * Rather than return the full stringification of the full lambda,
 * we elect to return an abbreviated string that just makes it clear
 * the expression is some sort of a lambda.
 */

Expression *LambdaExpression::call(Vector<Expression *>& arguments,
								   EvalState& state) {
    if (arguments.size() != locals.size()) {
        Error("Wrong number of arguments supplied");
    }
    EvalState localState(state);
    for (int i = 0; i <= locals.size() - 1; ++i) {
        localState.setExpression(locals[i]->toString(), arguments[i]->eval(state));
    }
   // cout << locals[0]->toString() << endl;
    //cout << exp->toString() << endl;
    return exp->eval(localState);
}
    
    
    


