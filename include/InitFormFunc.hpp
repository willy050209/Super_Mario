#pragma once
#ifndef INITFORM_FUNC
#define INITFORM_FUNC(func_name) static inline void func_name(MyAPP::GameManager* self) noexcept
#endif // !INITFORM_FUNC

INITFORM_FUNC(initForm_1_2);
INITFORM_FUNC(initForm_1_1_Pip);
INITFORM_FUNC(initForm_1_1_to_1_2);
INITFORM_FUNC(initForm_1_2_Pipe);
INITFORM_FUNC(winForm);


#ifndef INITFORMFUNC_HPP
#define INITFORMFUNC_HPP

#include "ButtonCallBackFunc.hpp"
#include "EventCallBackFunc.hpp"
#include "incallobj.hpp"
#include "Position.hpp"
#include "config.hpp"
#include "ProgressBar.hpp"


#include <algorithm>
#include <execution>
#include <memory>
#include <tuple>
#include <fstream>

using namespace MyAPP::Form::Object;

/// <summary>
/// 將表單寫入文字檔
/// </summary>
/// <param name="FM"></param>
/// <param name="formName"></param>
inline void writeForm(MyAPP::Form::FormManger& FM,std::string&& formName) {
	std::unique_ptr<Brick> Block = std::make_unique<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 1);
	auto size = Block->GetSize();
	auto x0 = GetX0(Block);
	auto y0 = GetY0(Block);
	auto& allobj = FM.GetFormAndObject(formName);
	std::ofstream fout("map/" + formName + "_Images.txt");
	if (fout.bad()) {
		return;
	}
	std::for_each(allobj.m_Images.begin(), allobj.m_Images.end(), [&](auto& img) {
		if (img->name != "Background") {
			auto& tmp = img->GetPosition();
			
			fout << (tmp.x - x0) / size.x << ' ' << (tmp.y - y0) / size.y << ' ' << (int)img->MyType << ' ' 
				<< img->GetVisibility() << ' ' << img->collisionable << '\n';
		}
	});
	fout.close();

	fout.open("map/" + formName + "_Characters.txt");
	if (fout.bad()) {
		return;
	}
	std::for_each(allobj.m_Characters.begin(), allobj.m_Characters.end(), [&](auto& it) {
		if (it->name != "Mario") {
			auto& tmp = it->GetPosition();

			fout << (tmp.x - x0) / size.x << ' ' << (tmp.y - y0) / size.y << ' ' << (int)it->MyType << ' '
				 << it->GetVisibility() << ' ' << it->collisionable << '\n';
		}
	});
	fout.close();

	fout.open("map/" + formName + "_Texts.txt");
	if (fout.bad()) {
		return;
	}
	std::for_each(allobj.m_Texts.begin(), allobj.m_Texts.end(), [&](auto& it) {
		auto& tmp = it->GetPosition();

		fout << (tmp.x - x0) / size.x << ' ' << (tmp.y - y0) / size.y << ' ' << (int)it->MyType << ' '
			 << it->GetVisibility() << ' ' << it->collisionable << '\n';
	});
	fout.close();


}

/// <summary>
/// 取得 bricks 中 Type == ObjectType::CheckPoint 的所有物件
/// </summary>
/// <param name="bricks"></param>
/// <returns></returns>
inline auto GetCheckPoints(std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks) noexcept {
	auto result = std::make_shared<std::vector<std::shared_ptr<CheckPoint>>>();
	std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
		if (it->MyType == ObjectType::CheckPoint) {
			result->push_back(std::static_pointer_cast<CheckPoint>(it));
		}
	});
	return result;
}

/// <summary>
/// 取得 bricks 中 Type == ObjectType::PipeBrick 的所有物件
/// </summary>
/// <param name="bricks"></param>
/// <returns></returns>
inline auto GetPipeBricks(std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks) noexcept {
	auto result = MakeObject::make_Bricks();
	std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
		if (it->MyType == ObjectType::PipeBrick) {
			result->push_back(std::static_pointer_cast<PipeBrick>(it));
		}
	});
	return result;
}

/// <summary>
/// 取得 bricks 中 Type == ObjectType::Flagpole 的所有物件
/// </summary>
/// <param name="bricks"></param>
/// <returns></returns>
inline auto GetFlagpoles(std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks) noexcept {
	auto result = MakeObject::make_Bricks();
	std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
		if (it->MyType == ObjectType::Flagpole) {
			result->push_back(std::static_pointer_cast<Flagpole>(it));
		}
	});
	return result;
}

/// <summary>
/// 取得 bricks 中 Type == ObjectType::Door 的所有物件
/// </summary>
/// <param name="bricks"></param>
/// <returns></returns>
inline auto Getdoors(std::shared_ptr<std::vector<std::shared_ptr<Brick>>> bricks) noexcept {
	auto result = MakeObject::make_Bricks();
	std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
		if (it->MyType == ObjectType::Door) {
			result->push_back(std::static_pointer_cast<Door>(it));
		}
	});
	return result;
}

/// <summary>
/// 取得 enemys 中 Type == ObjectType::Turtle 的所有物件
/// </summary>
/// <param name="bricks"></param>
/// <returns></returns>
inline auto GetTurtless(std::shared_ptr<std::vector<std::shared_ptr<Character>>> enemys) noexcept {
	auto result = MakeObject::make_Characters();
	std::for_each(enemys->begin(), enemys->end(), [&](auto& it) {
		if (it->MyType == ObjectType::Turtle) {
			result->push_back(std::static_pointer_cast<Turtle>(it));
		}
	});
	return result;
}

/// <summary>
/// 將物件陣列放入表單
/// </summary>
/// <typeparam name="T">物件陣列的共同父類</typeparam>
/// <param name="FM"></param>
/// <param name="formname"></param>
/// <param name="objlist"></param>
template<class T>
inline void AddToFoemManger(MyAPP::Form::FormManger& FM,const std::string& formname, std::shared_ptr<std::vector<std::shared_ptr<T>>> objlist) noexcept {
	std::for_each(objlist->begin(), objlist->end(), [&](auto& it) { FM.addObject(formname, it); });
}

/// <summary>
/// 將物件陣列放入表單
/// </summary>
/// <typeparam name="T">物件陣列的共同父類</typeparam>
/// <param name="FM"></param>
/// <param name="formname"></param>
/// <param name="objlist"></param>
template <class T>
inline void AddToFoemManger(MyAPP::Form::FormManger& FM,const std::string& formname, std::vector<std::shared_ptr<T>> objlist) noexcept {
	std::for_each(objlist.begin(), objlist.end(), [&](auto& it) { FM.addObject(formname, it); });
}


/*init Titel Form*/
INITFORM_FUNC(initFormTitle) {
	const auto textSize = 50 * ((float)WINDOW_HEIGHT / 480);
	auto&& textColor = Util::Color::FromName(Util::Colors::YELLOW);

	auto& MyFM = self->GetFormManger();

	auto button = std::make_shared<Button>("Start", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Start", textColor, 10);
	button->SetPosition({ 0, 2 * button->GetSize().y });
	button->SetCallBackFunc(StartButtonEvent);

	MyFM.addObject(MyAPP::Form::FormNames::FormTitel, button);
	button = std::make_shared<Button>("Options", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Options", textColor, 10);
	button->SetCallBackFunc(CallOptionForm);
	MyFM.addObject(MyAPP::Form::FormNames::FormTitel, button);

	button = std::make_shared<Button>("ExitButton", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Exit", textColor, 10);
	button->SetPosition({ 0, -(2 * button->GetSize().y) });
	button->SetCallBackFunc(exitCallBack);
	MyFM.addObject(MyAPP::Form::FormNames::FormTitel, button);

	auto image = std::make_shared<ImageObject>("QRcode", MY_RESOURCE_DIR "/Image/Background/qrcode.png", -10);
	MyFM.addObject("help", image);
	MyFM.changeForm(MyAPP::Form::FormNames::FormTitel);
}

/*init Options Form*/
INITFORM_FUNC(initFormOptions) {
	const auto textSize = 50 * (WINDOW_HEIGHT / 480);
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("ExitButton", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Exit", Util::Color::FromName(Util::Colors::SLATE_BLUE), 100);
	tmpbutton->SetPosition({ 0,
		GetY0(tmpbutton) - (WINDOW_HEIGHT - tmpbutton->GetSize().y) + textSize });
	tmpbutton->SetCallBackFunc(exitCallBack);
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("SettingButton", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Setting", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0, tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(CallSettingForm);
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("HelpButton", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Help", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0, 0 });
	tmpbutton->SetCallBackFunc(HelpButtonEvent);
	tmpbutton->userdata = std::make_shared<std::string>("start https://ntut-open-source-club.github.io/practical-tools-for-simple-design/");
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("BackButton", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton), GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);
}

INITFORM_FUNC(initFormSetting) {
	const auto textSize = 30 * ((float)WINDOW_HEIGHT / 480);
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("BackButton", MyAPP::MyResourcesFilePath::MyFontPath, 40 * ((float)WINDOW_HEIGHT / 480), "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton), GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	auto text = std::make_shared<TextObject>("VolumeValueText", MyAPP::MyResourcesFilePath::MyFontPath, textSize, std::to_string(MyBGM::GetVolume()), Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ 2 * text->GetSize().x, 0 });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	tmpbutton = std::make_shared<Button>("Volume-Button", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, (tmpbutton->GetSize().y * -2) });
	tmpbutton->SetCallBackFunc(VolumeDownClickedEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	tmpbutton = std::make_shared<Button>("Volume+Button", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, text->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(VolumeUpClickedEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	text = std::make_shared<TextObject>("VolumeText", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Volume", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ tmpbutton->GetPosition().x, (text->GetSize().y * 2) + text->GetSize().y });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);


	text = std::make_shared<TextObject>("ScreenSizeText", MyAPP::MyResourcesFilePath::MyFontPath, textSize, std::to_string(WINDOW_WIDTH) + "\n" + std::to_string(WINDOW_HEIGHT), Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ -2 * text->GetSize().x, 0 });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	tmpbutton = std::make_shared<Button>("ScreenSize-Button", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, -(tmpbutton->GetSize().y * 2) });
	tmpbutton->SetCallBackFunc(ScreenSizeDownClickedEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	tmpbutton = std::make_shared<Button>("ScreenSize+Button", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(ScreenSizeUpClickedEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	text = std::make_shared<TextObject>("ScreenSizeText", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "ScreenSize", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ tmpbutton->GetPosition().x, (text->GetSize().y * 2) + text->GetSize().y });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	text = std::make_shared<TextObject>("", MyAPP::MyResourcesFilePath::ArialFontPath, 20 * ((float)WINDOW_HEIGHT / 480), "Restart to apply screen settings", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ GetX0(text), -GetY0(text) });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	tmpbutton = std::make_shared<Button>("RestartButton", MyAPP::MyResourcesFilePath::MyFontPath, 20 * ((float)WINDOW_HEIGHT / 480), "Restart", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ -GetX0(tmpbutton), -GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(RestaetButtonEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);
}

INITFORM_FUNC(winForm) {
	auto& MyFM = self->GetFormManger();
	MyFM.addObject("Win", std::make_shared<TextObject>("", MyAPP::MyResourcesFilePath::MyFontPath, 20 * ((float)WINDOW_HEIGHT / 480), "Win", Util::Color::FromName(Util::Colors::WHITE), 10));
}

/*init 1-1*/
INITFORM_FUNC(initForm_1_1) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_1;
	// 作為座標參考
	std::unique_ptr<Brick> Block = std::make_unique<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 1);

	// 從地圖檔取得所有方塊
	auto& Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Images);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	AddToFoemManger(MyFM, formName, Blocks);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_1_ImagePath, Blocks);
	MyFM.addObject(formName, std::move(BMptr.first));
	MyFM.addObject(formName, std::move(BMptr.second));
	
	auto texts = MakeObject::make_GameText();
	AddToFoemManger(MyFM, formName, texts);
	
	auto enemys = MakeObject::make_Enemys_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Characters, Blocks);
	AddToFoemManger(MyFM, formName, enemys);

	auto props = MakeObject::make_Props();
	props->push_back(std::make_shared<Props::FireFlower>("FireFlower", 10));
	props->back()->SetPosition({ GetX0(Block), 0 });
	props->push_back(std::make_shared<Props::Mushroom>("Mushroom", Props::Mushroom::GetImages<Props::Mushroom::Category::Mushroom>(), Props::Mushroom::Category::Mushroom, 10));
	props->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 2, 0 });
	props->push_back(std::make_shared<Props::Mushroom>("Mushroom", Props::Mushroom::GetImages<Props::Mushroom::Category::MushroomDark>(), Props::Mushroom::Category::MushroomDark, 10));
	props->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 3, 0 });
	props->push_back(std::make_shared<Props::Mushroom>("Mushroom", Props::Mushroom::GetImages<Props::Mushroom::Category::BigMushroom>(), Props::Mushroom::Category::BigMushroom, 10));
	props->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 4, 0 });
	props->push_back(std::make_shared<Props::Starman>("Starman", 10));
	props->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 6, 0 });
	std::for_each(std::execution::seq, props->begin(), props->end(), [&](auto& it) { MyFM.addObject(formName, it); });

	self->sfx = std::make_shared<Util::SFX>(MyAPP::MyResourcesFilePath::Game_Over);
	self->bgm = std::make_shared<Util::BGM>(MyAPP::MyResourcesFilePath::Ground_Theme);
	auto& sfx = self->sfx;
	auto& bgm = self->bgm;
	bgm->Play(-1);

	auto eventobj = std::make_shared<EventObject>("freeForm_1_1_pipe", freeForm, false);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1_Pipe);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<
		std::tuple<std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Character>>>,
			std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Brick>>>,
			std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Props::Props>>>>>(enemys, pipes, props);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int>>(0, 300);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckEneyCollision", CheckEneyCollision);
	eventobj->userdata = enemys;
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckFlagpoleCollision", CheckFlagpoleCollision);
	eventobj->userdata =(flagpole);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor, false);
	eventobj->userdata = Getdoors(Blocks);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	eventobj = std::make_shared<EventObject>("CheckTortoiseShellCollision", CheckTortoiseShellCollision);
	eventobj->userdata = GetTurtless(enemys);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = checkPointArray;
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));

	//writeForm(MyFM, MyAPP::Form::FormNames::Form_1_1);
}

/// <summary>
/// 初始化1-1水管
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_1_Pip) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_1_Pipe;
	auto Block = std::make_unique<Brick>("", MyAPP::MyResourcesFilePath::BlockImagePath, 0);

	auto& Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Pipe_Images, true);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	AddToFoemManger(MyFM, formName, Blocks);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_1_Pipe_ImagePath, Blocks, { GetX0(Block) + Block->GetSize().x * 3, 100 });
	MyFM.addObject(formName, std::move(BMptr.first));
	MyFM.addObject(formName, std::move(BMptr.second));

	auto texts = MakeObject::make_GameText();
	AddToFoemManger(MyFM, formName, texts);

	auto enemys = MakeObject::make_Enemys_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Pipe_Characters, Blocks);
	AddToFoemManger(MyFM, formName, enemys);

	auto eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<
			std::tuple<std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Character>>>,
			std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Brick>>>,
			std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Props::Props>>>>>(enemys, pipes, MakeObject::make_Props());
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int>>(0, 300);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));

	//writeForm(MyFM, MyAPP::Form::FormNames::Form_1_1_Pipe);
}

/// <summary>
/// 初始化1-1到1-2過場
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_1_to_1_2) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_1_to_1_2;
	auto Block = std::make_unique<Brick>("", MyAPP::MyResourcesFilePath::BlockImagePath, 0);

	auto& Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_to_1_2_Images, false);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	AddToFoemManger(MyFM, formName, Blocks);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_1_to_1_2_ImagePath, Blocks, { GetX0(Block) + Block->GetSize().x * 2, GetY0(Block) - Block->GetSize().x * 12 });
	MyFM.addObject(formName, std::move(BMptr.first));
	MyFM.addObject(formName, std::move(BMptr.second));

	auto eventobj = std::make_shared<EventObject>("freeForm_1_1", freeForm);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent);
	eventobj->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(30, std::vector<bool>());
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor);
	eventobj->userdata = Getdoors(Blocks);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
	
	//writeForm(MyFM, formName);
}

/// <summary>
/// 初始化1-2地圖
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_2) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_2;
	auto Block = std::make_unique<Brick>("", MyAPP::MyResourcesFilePath::BlockImagePath, 0);

	auto& Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_2_Images, true);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	AddToFoemManger(MyFM, formName, Blocks);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_2_ImagePath, Blocks, { GetX0(Block) + Block->GetSize().x * 5, 100 });
	auto& img = BMptr.first;
	auto& mario = BMptr.second;

	MyFM.addObject(formName, std::move(img));
	MyFM.addObject(formName, std::move(mario));

	auto texts = MakeObject::make_GameText();
	AddToFoemManger(MyFM, formName, texts);

	auto enemys = MakeObject::make_Enemys_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_2_Characters, Blocks);
	AddToFoemManger(MyFM, formName, enemys);

	auto eventobj = std::make_shared<EventObject>("freeForm_1_2_Pipe", freeForm, false);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2_Pipe);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<
			std::tuple<std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Character>>>,
			std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Brick>>>,
			std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Props::Props>>>>>(enemys, pipes, MakeObject::make_Props());
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int>>(0, 300);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckEneyCollision", CheckEneyCollision);
	eventobj->userdata = std::move(enemys);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = GetCheckPoints(Blocks);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));

	//writeForm(MyFM, formName);
}

/// <summary>
/// 初始化1-2水管
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_2_Pipe) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_2_Pipe;
	auto Block = std::make_unique<Brick>("", MyAPP::MyResourcesFilePath::BlockImagePath, 0);

	auto& Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_2_Pipe_Images, true);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	AddToFoemManger(MyFM, formName, Blocks);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_2_Pipe_ImagePath, Blocks, { GetX0(Block) + Block->GetSize().x * 3, 100 });
	MyFM.addObject(formName, std::move(BMptr.first));
	MyFM.addObject(formName, std::move(BMptr.second));

	auto texts = MakeObject::make_GameText();
	AddToFoemManger(MyFM, formName, texts);

	auto eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<
		std::tuple<std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Character>>>,
		std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Brick>>>,
		std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Props::Props>>>>>
		(MakeObject::make_Characters(), pipes, MakeObject::make_Props());
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int>>(0, 300);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
	
	//writeForm(MyFM, MyAPP::Form::FormNames::Form_1_2_Pipe);
}

#endif // !INITFORMFUNC_HPP
