#ifndef BUTTONCALLBACKFUNC
#define BUTTONCALLBACKFUNC

#include "Button.hpp"
#include "GameManager.hpp"

#include <iostream>

#define BUTTON_CALLBACK_FUNCTION(FUNC_name) static void FUNC_name(Button* const self, void* data)

BUTTON_CALLBACK_FUNCTION(callBackTest){
	std::cout << self->GetText() << " is clicked!\n";
}

BUTTON_CALLBACK_FUNCTION(exitCallBack) {
	auto gm = (GameManager*)data;
	std::cout << "Exit APP! \n";
	gm->End();
}

BUTTON_CALLBACK_FUNCTION(Back_Button_func) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	auto now = fm.GetNowForm();
	auto prev = fm.GetPrevForm();
	std::cout << "now Form is " << now << '\n';
	std::cout << "prev Form is " << prev << '\n';
	fm.changeForm(prev);
	std::cout << "change Form to " << fm.GetNowForm() << '\n';
}

#endif // !BUTTONCALLBACKFUNC
