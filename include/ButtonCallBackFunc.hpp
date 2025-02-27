#ifndef BUTTONCALLBACKFUNC
#define BUTTONCALLBACKFUNC

#include "Button.hpp"
#include "GameManager.hpp"

#include <iostream>


static void callBackTest(Button* const self, void* data) {
	std::cout << self->GetText() << " is clicked!\n";
}

static void exitCallBack(Button* const self, void* data) {
	auto gm = (GameManager*)data;
	std::cout << " Exit APP! \n";
	gm->End();
}

#endif // !BUTTONCALLBACKFUNC
