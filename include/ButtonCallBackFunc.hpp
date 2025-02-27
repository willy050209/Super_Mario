#ifndef BUTTONCALLBACKFUNC
#define BUTTONCALLBACKFUNC

#include "Button.hpp"

#include <iostream>

static void callBackTest(Button* const self) {
	std::cout << self->GetText() << " is clicked!\n";
}

#endif // !BUTTONCALLBACKFUNC
