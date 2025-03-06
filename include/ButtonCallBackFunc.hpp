#ifndef BUTTONCALLBACKFUNC_hpp
#define BUTTONCALLBACKFUNC_hpp

#include "Button.hpp"
#include "GameManager.hpp"

#include <iostream>

#define BUTTONCALLBACKFUNCTION(FUNC_name) static void FUNC_name(Button* const self, void* data)

BUTTONCALLBACKFUNCTION(callBackTest) {
	std::cout << self->GetText() << " is clicked!\n";
}

BUTTONCALLBACKFUNCTION(RestaetButtonEvent) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	gm->SetRestart(true);
	gm->End();
}

BUTTONCALLBACKFUNCTION(exitCallBack) {
	auto gm = (GameManager*)data;
	std::cout << "Exit APP! \n";
	gm->End();
}

BUTTONCALLBACKFUNCTION(Back_Button_func) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	fm.returnPrevForm();
}

BUTTONCALLBACKFUNCTION(CallOptionForm) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	fm.changeForm(FormOptions);
}

BUTTONCALLBACKFUNCTION(CallSettingForm) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	fm.changeForm(FormSetting);
}

BUTTONCALLBACKFUNCTION(VolumeUpClickedEvent) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	int volume = gm->GetBGM()->GetVolume();
	if (volume == 100) return;
	gm->GetBGM()->SetVolume(++volume);
	auto text = fm.GetObject(FormSetting, ObjectType::TextObject, "VolumeValueText");
	std::dynamic_pointer_cast<Util::Text>(text->GetDrawable())->SetText(std::to_string(gm->GetBGM()->GetVolume()));
}


BUTTONCALLBACKFUNCTION(VolumeDownClickedEvent) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	int volume = gm->GetBGM()->GetVolume();
	if (volume == 0) return;
	gm->GetBGM()->SetVolume(--volume);
	auto text = fm.GetObject(FormSetting, ObjectType::TextObject, "VolumeValueText");
	std::dynamic_pointer_cast<Util::Text>(text->GetDrawable())->SetText(std::to_string(gm->GetBGM()->GetVolume()));
}

BUTTONCALLBACKFUNCTION(ScreenSizeUpClickedEvent) {
	struct W_H
	{
		int W;
		int H;
	};
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	if (new_WINDOW_WIDTH == 960) {
		new_WINDOW_WIDTH = 1280;
		new_WINDOW_HEIGHT = 720;
		
	}else if ( new_WINDOW_WIDTH == 1280) {
		new_WINDOW_WIDTH = 1600;
		new_WINDOW_HEIGHT = 900;
	}
	else if (new_WINDOW_WIDTH == 1600) {
		new_WINDOW_WIDTH = 1920;
		new_WINDOW_HEIGHT = 1080;
	}
	else{
		return;
	}
	auto text = fm.GetObject(FormSetting, ObjectType::TextObject, "ScreenSizeText");
	std::dynamic_pointer_cast<Util::Text>(text->GetDrawable())->SetText(std::to_string(new_WINDOW_WIDTH) + "\n" + std::to_string(new_WINDOW_HEIGHT));
}


BUTTONCALLBACKFUNCTION(ScreenSizeDownClickedEvent) {
	struct W_H
	{
		int W;
		int H;
	};
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	if (new_WINDOW_WIDTH == 1280) {
		new_WINDOW_WIDTH = 960;
		new_WINDOW_HEIGHT = 540;

	}
	else if (new_WINDOW_WIDTH == 1600) {
		new_WINDOW_WIDTH = 1280;
		new_WINDOW_HEIGHT = 720;
	}
	else if (new_WINDOW_WIDTH == 1920) {
		new_WINDOW_WIDTH = 1600;
		new_WINDOW_HEIGHT = 900;
	}
	else {
		return;
	}
	auto text = fm.GetObject(FormSetting, ObjectType::TextObject, "ScreenSizeText");
	std::dynamic_pointer_cast<Util::Text>(text->GetDrawable())->SetText(std::to_string(new_WINDOW_WIDTH) + "\n" + std::to_string(new_WINDOW_HEIGHT));
}

BUTTONCALLBACKFUNCTION(StartButtonEvent) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	fm.changeForm(FormBackground);
}

BUTTONCALLBACKFUNCTION(HelpButtonEvent) {
	auto gm = (GameManager*)data;
	auto& fm = gm->GetFormManger();
	system("start https://ntut-open-source-club.github.io/practical-tools-for-simple-design/");
}

#endif // !BUTTONCALLBACKFUNC
