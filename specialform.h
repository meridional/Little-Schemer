/**
 * File: specialform.h
 * ------------------
 * Trivial extension of the Callable class. It
 * doesn't add any new methods, but it exists
 * for no other reason that to provide a dedicated
 * type that all special forms can implement.
 */

#ifndef __scheme_special_form__
#define __scheme_special_form__

#include "callable.h"

class SpecialForm : public Callable {
	
};

#endif
