#include "GameManager.hpp"
#include "incallobj.hpp"
#include "Position.hpp"
#include "config.hpp"
#include "ProgressBar.hpp"
#include "InitFormFunc.hpp"
#include "Form/FormNames.hpp"

#include <execution>
#include <algorithm>
#include <memory>
#include <thread>



void MyAPP::GameManager::init() noexcept {

	//auto& _ = MyAPP::Form::Object::PositionReference::GetPositionReference();
	//auto __ = std::make_unique<Util::Text>(MyAPP::MyResourcesFilePath::MyFontPath, 50, "test", Util::Color::FromName(Util::Colors::WHITE));
	//
	//auto idontknow = [](MyAPP::GameManager*) { 
	//	auto __ = std::make_shared<Util::Image>(MyAPP::MyResourcesFilePath::EmptyBlockDarkImagePath);
	//	auto ___ = std::make_unique<Util::Text>(MyAPP::MyResourcesFilePath::MyFontPath, 50, "test", Util::Color::FromName(Util::Colors::WHITE)); };
	//
	//std::thread t0(idontknow, this);
	//t0.join();

	puts("init GameManager");
	std::vector<std::function<void(MyAPP::GameManager*)>> initfuncs = {
		initFormTitle, initForm_1_1, initFormOptions, initFormSetting
	};
	std::for_each(std::execution::seq, initfuncs.begin(), initfuncs.end(), [&](auto& func) {
		(func)(this);
	});
	MyFM.changeForm(MyAPP::Form::FormNames::FormTitel);
	
}

void MyAPP::GameManager::Update(std::shared_ptr<Core::Context>& context) noexcept {
	if (Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
		if (MyFM.GetNowForm() == MyAPP::Form::FormNames::FormOptions)
			MyFM.changeForm(MyFM.GetPrevForm());
		else
		MyFM.changeForm(MyAPP::Form::FormNames::FormOptions);

	}
	else if (Util::Input::IsKeyDown(Util::Keycode::H)) {
		IncHP();
		Points::UpdatePoint(MyFM, Points::Point::pts1up);
	}
	MyFM.UpdateForm(this);
}

void MyAPP::GameManager::End() noexcept {
	endstate = true;
}

void MyAPP::GameManager::LostALife() noexcept {
	DecHP();
	bgm->Pause();
	sfx->LoadMedia(MyAPP::MyResourcesFilePath::Lost_a_Life);
	sfx->Play(0);
	(MyFM.GetFormObject<EventObject>(MyFM.GetNowForm(), "UpdateHPText"))->Enable = true;
	if (GetHP() == 0) {
		bgm->LoadMedia(MyAPP::MyResourcesFilePath::Game_Over);
		auto sleepevent = (MyFM.GetFormObject<EventObject>(MyFM.GetNowForm(), "SleepAllevent"));
		sleepevent->Enable = true;
		sleepevent->userdata.reset();
		sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP * 3, std::vector<bool>());
		(MyFM.GetFormObject<EventObject>(MyFM.GetNowForm(), "FinifhEvent"))->Enable = true;
	}
	else {
		(MyFM.GetFormObject<EventObject>(MyFM.GetNowForm(), "GoBackCheckPoint"))->Enable = true;
		auto sleepevent = (MyFM.GetFormObject<EventObject>(MyFM.GetNowForm(), "SleepAllevent"));
		sleepevent->Enable = true;
		sleepevent->userdata.reset();
		sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP, std::vector<bool>());
	}
}
