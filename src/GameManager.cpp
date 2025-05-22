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
		MyFM.GetFormObject<EventObject>(MyFM.GetNowForm(), "UpdateHPText")->Enable = true;
	}
	MyFM.UpdateForm(this);
}

void MyAPP::GameManager::End() noexcept {
	endstate = true;
}
