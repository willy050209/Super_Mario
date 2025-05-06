#include "GameManager.hpp"
#include "incallobj.hpp"
#include "Position.hpp"
#include "config.hpp"
#include "ProgressBar.hpp"
#include "InitFormFunc.hpp"
#include "Form/FormNames.hpp"



void MyAPP::GameManager::init() noexcept {
	//auto gobj = std::make_shared<Util::GameObject>(std::make_shared<Util::Image>(StairsBrickDarkImagePath), 10);
	//std::unique_ptr<Util::Image> _;
	/*std::thread t1([&gobj]() { auto _ = std::make_shared<Util::Image>(StairsBrickDarkImagePath); });
	t1.join();*/
	//auto _ = std::make_shared<Util::GameObject>(std::make_shared<Util::Image>(StairsBrickDarkImagePath), 0);

	/*test BGM*/
	/*bgms.push_back(std::make_shared<MyBGM::BGM>("Bgm", "D:\\program\\C++\\Super_Mario\\Resources\\BGM\\12. Ground Theme (Hurry!).wav"));
	bgms.push_back(std::make_shared<MyBGM::BGM>("Bgm1", "D:/program/C++/Super_Mario/Resources/BGM/wakeup music.wav"));*/
	int total = 7, current = 0;
	puts("init GameManager");
	/*bgms.push_back(std::make_shared<MyBGM::BGM>("Bgm1", MY_RESOURCE_DIR"/BGM/Ring08.wav"));
	for (auto& it : bgms) {
		it->Play();
	}*/
	/*auto button = std::make_shared<Button>("test", MyFontPath, 50, "pause", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	button->SetPosition({ -GetX0(button), GetY0(button) });
	button->userdata = bgms.back();
	button->SetCallBackFunc([](Button* self, void* data) {
		auto bgm = std::static_pointer_cast<MyBGM::BGM>(self->userdata);
		if (bgm->isPlay()) {
			bgm->Pause();
		}
		else {
			bgm->Resum();
		}
	});
	MyFM.addObject(Form_1_1, button);*/

	//initFormBackground(this);
	//showProgressBar(total, current++);
	initFormTitle(this);
	showProgressBar(total, current++);

	initForm_1_1(this);
	showProgressBar(total, current++);

	//initForm_1_1_Pip(this);
	showProgressBar(total, current++);

	//initForm_1_2(this);
	showProgressBar(total, current++);

	initFormOptions(this);
	showProgressBar(total, current++);

	initFormSetting(this);
	showProgressBar(total, current++);

	//winForm(this);
	showProgressBar(total, current++);

	//initForm_1_1_to_1_2(this);
	//initForm_1_2_Pipe(this);

	MyFM.changeForm(MyAPP::Form::FormNames::FormTitel /*FormBackground*/);
	//MyFM.changeForm(Form_1_2_Pipe);
	showProgressBar(total, current);
	puts("");
	/*system("pause");
	for (auto& it : bgms) {
		it->SetLoop(false);
	}*/



}

void MyAPP::GameManager::Update(std::shared_ptr<Core::Context>& context) noexcept {
	/*time_try*/
	// MyFM.
	// time_t now = time(0);
	// std::string tm = ctime(&now);
	////std::cout << tm << '\n';
	// auto texttime = std::make_shared<TextObject>("Timetext", ArialFontPath, 20, tm, Util::Color::FromName(Util::Colors::WHITE), 100);
	// texttime->SetPosition({ 100,100 });
	// texttime->SetPosition({ GetX0(texttime),GetY0(texttime) });
	// MyFM.removeObject(Form_1_1, ObjectType::TextObject, "Timetext");
	// MyFM.addObject(Form_1_1, texttime);

	if (Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
		MyFM.changeForm(MyAPP::Form::FormNames::FormOptions);
		//if (MyFM.GetPrevForm() != "null") {
		//	MyFM.returnPrevForm();
		//}
		///*else if (MyFM.GetNowForm() == FormTitel) {
		//	MyFM.changeForm(FormOptions);
		//}*/
		//else {
		//	MyFM.changeForm(FormOptions);
		//}
	}
	MyFM.UpdateForm(this);
}

void MyAPP::GameManager::End() noexcept {
	endstate = true;
	/*for (auto& bgm : bgms) {
		bgm->Stop();
	}*/
}
