#ifndef BUTTONCALLBACKFUNC
#define BUTTONCALLBACKFUNC

#include "Button.hpp"
#include "GameManager.hpp"

#include <iostream>

#define BUTTON_CALLBACK_FUNCTION(FUNC_name) static void FUNC_name(Button* const self, void* data)

BUTTON_CALLBACK_FUNCTION(callBackTest) {
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
	fm.returnPrevForm();
}

BUTTON_CALLBACK_FUNCTION(CallSettingForm) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	fm.changeForm(FormSetting);
}

BUTTON_CALLBACK_FUNCTION(VolumeUpClickedEvent) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	int volume = gm->GetBGM()->GetVolume();
	if (volume == 100) return;
	gm->GetBGM()->SetVolume(++volume);
	auto text = fm.GetObject(FormSetting, ObjectType::TextObject, "VolumeValueText");
	std::dynamic_pointer_cast<Util::Text>(text->GetDrawable())->SetText(std::to_string(gm->GetBGM()->GetVolume()));
}


BUTTON_CALLBACK_FUNCTION(VolumeDownClickedEvent) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	int volume = gm->GetBGM()->GetVolume();
	if (volume == 0) return;
	gm->GetBGM()->SetVolume(--volume);
	auto text = fm.GetObject(FormSetting, ObjectType::TextObject, "VolumeValueText");
	std::dynamic_pointer_cast<Util::Text>(text->GetDrawable())->SetText(std::to_string(gm->GetBGM()->GetVolume()));
}


#endif // !BUTTONCALLBACKFUNC
