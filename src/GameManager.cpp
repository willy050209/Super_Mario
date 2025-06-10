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

static std::string GetWorld(std::string formname) {
	using MyAPP::Form::FormNames;
	if (formname == FormNames::Form_1_1 || formname == FormNames::Form_1_1_Pipe || formname == FormNames::Form_1_1_to_1_2) {
		return "1-1";
	}
	else if (formname == FormNames::Form_1_2 || formname == FormNames::Form_1_2_Pipe || formname == FormNames::Form_1_2_to_1_4) {
		return "1-2";
	}
	else if (formname == FormNames::Form_1_4) {
		return "1-4";
	}
	return "???";
}

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
	auto initfuncs = {
		initFormTitle, initForm_1_1, initFormOptions, initFormSetting, diedForm 
		//,initForm_1_2
		//,initForm_1_4
		,initForm1
	};
	std::for_each(std::execution::seq, initfuncs.begin(), initfuncs.end(), [&](auto& func) {
		(func)(this);
	});

	MyFM.changeForm(MyAPP::Form::FormNames::FormTitel);
	MyFM.changeForm("Form1");
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
		Points::UpdatePoint(MyFM, Points::PointType::pts1up);
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
	{
		auto changeFormEvent = MyFM.GetFormObject<EventObject>(MyFM.GetNowForm(), "ChangeFormEvent");
		changeFormEvent->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::DiedForm);
		changeFormEvent->Enable = true;
	}
	{
		auto changeFormEvent = MyFM.GetFormObject<EventObject>(MyAPP::Form::FormNames::DiedForm, "ChangeFormEvent");
		changeFormEvent->userdata = std::make_shared<std::string>(MyFM.GetNowForm());
		changeFormEvent->Enable = false;
	}
	{
		auto UpdateInfo = MyFM.GetFormObject<EventObject>(MyAPP::Form::FormNames::DiedForm, "UpdateInfo");
		UpdateInfo->userdata = std::make_shared<std::string>(GetWorld(MyFM.GetNowForm()));
		UpdateInfo->Enable = true;
	}
	{
		auto DelayEvent = MyFM.GetFormObject<EventObject>(MyAPP::Form::FormNames::DiedForm, "DelayEvent");
		DelayEvent->userdata = std::make_shared<int>(FPS_CAP * 2);
		DelayEvent->Enable = true;
	}
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
