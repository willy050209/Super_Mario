#pragma once
#ifndef INITFORM_FUNC
#define INITFORM_FUNC(func_name) static void func_name(MyAPP::GameManager* self) noexcept
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

void writeForm(MyAPP::Form::FormManger& FM,std::string&& formName) {
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



//INITFORM_FUNC(initFormBackground) {
//
//	auto& MyFM = self->GetFormManger();
//
//	std::thread initenent([&]() {
//		auto event = std::make_shared<EventObject>("SystemTime", GetSystemTimeFunc, true);
//		event->userdata = std::make_shared<int>(0);
//		MyFM.addObject(MyAPP::Form::FormNames::FormBackground, event);
//	});
//
//	/*add images to FormBackground*/
//	auto tmpImage = std::make_shared<ImageObject>("cat0", MyAPP::MyResourcesFilePath::BackgroundImagePath, -10);
//	tmpImage->SetPosition({ GetX0(tmpImage), GetY0(tmpImage) - (WINDOW_HEIGHT - tmpImage->GetSize().y) });
//	MyFM.addObject(MyAPP::Form::FormNames::FormBackground, tmpImage);
//
//	auto tmptest = std::make_shared<ImageObject>("mario_walk", MY_RESOURCE_DIR "\\super mario\\Mario\\frame0.png", 100);
//	tmptest->SetPosition({ 100, 100 });
//	MyFM.addObject(MyAPP::Form::FormNames::FormBackground, tmptest);
//
//	tmpImage = (std::make_shared<ImageObject>("cat1", MyAPP::MyResourcesFilePath::BackgroundImagePath, -10));
//	MyFM.addObject(MyAPP::Form::FormNames::FormBackground, tmpImage);
//
//	tmpImage = (std::make_shared<ImageObject>("phase0", MY_RESOURCE_DIR "/super mario/Maps/SuperMarioBrosMap1-1BG.png", 1));
//	tmpImage->SetPosition({ GetX0(tmpImage), 0 });
//	MyFM.addObject(MyAPP::Form::FormNames::FormBackground, tmpImage);
//
//	/*add characters to FormBackground*/
//	auto mario = (std::make_shared<Mario>("Mario", 10));
//	mario->SetPosition({ 0, 300 });
//	mario->userdata = std::static_pointer_cast<void>(tmpImage);
//	MyFM.addObject(MyAPP::Form::FormNames::FormBackground, mario);
//
//
//	/*add Texts to FormBackground*/
//	auto text(std::make_shared<TextObject>("Text0", MyAPP::MyResourcesFilePath::ArialFontPath, 20, "Text Output Example(Font = Arial)", Util::Color::FromName(Util::Colors::YELLOW), 10));
//	text->SetPosition({ -400, 300 });
//	text->SetPosition({ GetX0(text), GetY0(text) });
//	MyFM.addObject(MyAPP::Form::FormNames::FormBackground, text);
//
//	MyFM.addObject(MyAPP::Form::FormNames::FormBackground, std::make_shared<TextObject>("HelloWorld", MyAPP::MyResourcesFilePath::ArialFontPath, 50, "Hello world!!", Util::Color::FromRGB(255, 255, 255), 10));
//
//
//	/*add buttons to FormBackground*/
//	for (int i = 0; i < 10; ++i) {
//		auto buttonptr = std::make_shared<Button>("button" + std::to_string(i), MyAPP::MyResourcesFilePath::ArialFontPath, 20, "This is a button" + std::to_string(i), Util::Color::FromName(Util::Colors::YELLOW_GREEN), 20);
//		buttonptr->SetPosition({ GetX0(buttonptr) + 100, GetY0(buttonptr) - 50 * (i + 1) });
//		buttonptr->userdata = std::make_shared<int>(0);
//		buttonptr->SetCallBackFunc(callBackTest);
//		MyFM.addObject(MyAPP::Form::FormNames::FormBackground, buttonptr);
//	}
//	///*give BGM to FormBackground*/
//	// auto tmp = std::make_shared<Util::BGM>(MY_RESOURCE_DIR"/BGM/wakeup music.mp3");
//	////tmp->LoadMedia(MY_RESOURCE_DIR"/BGM/wakeup music.mp3");
//	// tmp->Play(-1);
//	// auto tmpdouble = std::make_shared<Util::BGM>(MY_RESOURCE_DIR"/BGM/01. Ground Theme.mp3");
//	////tmpdouble->LoadMedia(MY_RESOURCE_DIR"/BGM/01. Ground Theme.mp3");
//	// tmpdouble->Play(-1);
//
//	/////*time_try*/
//	// time_t now = time(0);
//	// std::string tm = ctime(&now);
//	////std::cout << tm << '\n';
//	// auto texttime = std::make_shared<TextObject>("Timetext", ArialFontPath, 20, tm, Util::Color::FromName(Util::Colors::WHITE), 100);
//	// texttime->SetPosition({100,100 });
//	// texttime->SetPosition({ GetX0(texttime),GetY0(texttime) });
//	// MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, texttime);
//
//	initenent.join();
//}

/*init Titel Form*/
INITFORM_FUNC(initFormTitle) {
	constexpr auto textSize = 50;
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
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("ExitButton", MyAPP::MyResourcesFilePath::MyFontPath, 50, "Exit", Util::Color::FromName(Util::Colors::SLATE_BLUE), 100);
	tmpbutton->SetPosition({ 0,
		GetY0(tmpbutton) - (WINDOW_HEIGHT - tmpbutton->GetSize().y) + 50 });
	tmpbutton->SetCallBackFunc(exitCallBack);
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("SettingButton", MyAPP::MyResourcesFilePath::MyFontPath, 50, "Setting", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0, tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(CallSettingForm);
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("HelpButton", MyAPP::MyResourcesFilePath::MyFontPath, 50, "Help", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0, 0 });
	tmpbutton->SetCallBackFunc(HelpButtonEvent);
	tmpbutton->userdata = std::make_shared<std::string>("start https://ntut-open-source-club.github.io/practical-tools-for-simple-design/");
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("BackButton", MyAPP::MyResourcesFilePath::MyFontPath, 50, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton), GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);
}

INITFORM_FUNC(initFormSetting) {
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("BackButton", MyAPP::MyResourcesFilePath::MyFontPath, 40, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton), GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	auto text = std::make_shared<TextObject>("VolumeValueText", MyAPP::MyResourcesFilePath::MyFontPath, 30, std::to_string(MyBGM::GetVolume()), Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ 2 * text->GetSize().x, 0 });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	tmpbutton = std::make_shared<Button>("Volume-Button", MyAPP::MyResourcesFilePath::MyFontPath, 30, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, (tmpbutton->GetSize().y * -2) });
	tmpbutton->SetCallBackFunc(VolumeDownClickedEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	tmpbutton = std::make_shared<Button>("Volume+Button", MyAPP::MyResourcesFilePath::MyFontPath, 30, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, text->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(VolumeUpClickedEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	text = std::make_shared<TextObject>("VolumeText", MyAPP::MyResourcesFilePath::MyFontPath, 30, "Volume", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ tmpbutton->GetPosition().x, (text->GetSize().y * 2) + text->GetSize().y });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);


	text = std::make_shared<TextObject>("ScreenSizeText", MyAPP::MyResourcesFilePath::MyFontPath, 30, std::to_string(WINDOW_WIDTH) + "\n" + std::to_string(WINDOW_HEIGHT), Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ -2 * text->GetSize().x, 0 });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	tmpbutton = std::make_shared<Button>("ScreenSize-Button", MyAPP::MyResourcesFilePath::MyFontPath, 30, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, -(tmpbutton->GetSize().y * 2) });
	tmpbutton->SetCallBackFunc(ScreenSizeDownClickedEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	tmpbutton = std::make_shared<Button>("ScreenSize+Button", MyAPP::MyResourcesFilePath::MyFontPath, 30, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(ScreenSizeUpClickedEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	text = std::make_shared<TextObject>("ScreenSizeText", MyAPP::MyResourcesFilePath::MyFontPath, 30, "ScreenSize", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ tmpbutton->GetPosition().x, (text->GetSize().y * 2) + text->GetSize().y });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	text = std::make_shared<TextObject>("", MyAPP::MyResourcesFilePath::ArialFontPath, 20, "Restart to apply screen settings", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ GetX0(text), -GetY0(text) });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	tmpbutton = std::make_shared<Button>("RestartButton", MyAPP::MyResourcesFilePath::MyFontPath, 20, "Restart", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ -GetX0(tmpbutton), -GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(RestaetButtonEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);
}

INITFORM_FUNC(winForm) {
	auto& MyFM = self->GetFormManger();
	MyFM.addObject("Win", std::make_shared<TextObject>("", MyAPP::MyResourcesFilePath::MyFontPath, 20, "Win", Util::Color::FromName(Util::Colors::WHITE), 10));
}

/*init 1-1*/
INITFORM_FUNC(initForm_1_1) {
	auto& MyFM = self->GetFormManger();

	auto enemys = MakeObject::make_Characters();
	auto pipes = MakeObject::make_Bricks();

	std::unique_ptr<Brick> Block = std::make_unique<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 1);

	auto Blocks = MakeObject::make_Bricks(); //(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Images,false);
	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_1_ImagePath,Blocks);
	auto& img = BMptr.first;
	auto& mario = BMptr.second;
	//auto& Blocks = *(std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(img->userdata));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(img));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, mario);

	//std::for_each(Blocks->begin(), Blocks->end(), [&](auto& it) { MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, it); });

	std::vector<std::shared_ptr<CheckPoint>> checkPointArray;
	checkPointArray.push_back(std::make_shared<CheckPoint>("checkpoint"));
	checkPointArray[0]->collisionable = false;
	checkPointArray[0]->SetVisible(false);
	checkPointArray[0]->SetPosition({ 0, 0 });

	std::copy(checkPointArray.begin(), checkPointArray.end(), std::back_inserter(*Blocks));
	/*for (auto& it : checkPointArray) {
		Blocks.push_back(it);
	}*/
	// std::ofstream outfile("map.txt");

	/*init door*/
	std::ifstream inp(MY_RESOURCE_DIR "/MAP/map1_1_door.txt");
	float posx = 0, posy = 0;
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_door.txt";
		exit(-1);
	}
	std::array<std::shared_ptr<Brick>, 2> doorarr{ std::make_shared<Brick>("door", MyAPP::MyResourcesFilePath::StairsBrickImagePath, -10), std::make_shared<Brick>("door", MyAPP::MyResourcesFilePath::StairsBrickImagePath, -10) };
	for (int k = 0; k < 2; ++k) {
		doorarr[k]->collisionable = false;
		doorarr[k]->SetVisible(false);
		inp >> posx >> posy;
		doorarr[k]->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
		Blocks->push_back(doorarr[k]);
	}
	inp.close();

	/*init pipe*/
	//std::vector<std::shared_ptr<Brick>> pieps;
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_pipe.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_pipe.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		pipes->push_back(std::make_shared<PipeBrick>("pipe", 10));
		pipes->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
		//pipes->back()->collisionable = false;
	}
	inp.close();
	std::copy(pipes->begin(), pipes->end(), std::back_inserter(*Blocks));
	/*for (auto& it : pieps) {
		Blocks.push_back(it);
	}*/

	/*Flagpole collision box*/
	std::vector<std::shared_ptr<Brick>> flagpole;
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_Flagpole.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_Flagpole.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		flagpole.push_back(std::make_shared<Brick>("Flagpole", MyAPP::MyResourcesFilePath::StairsBrickImagePath, 10));
		flagpole.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
		flagpole.back()->collisionable = false;
	}
	inp.close();
	std::copy(flagpole.begin(), flagpole.end(), std::back_inserter(*Blocks));
	/*for (auto& it : flagpole) {
		Blocks.push_back(it);
	}*/

	/*init floor*/
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_floor.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_floor.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		Blocks->push_back(std::make_shared<Brick>("Brick", MyAPP::MyResourcesFilePath::StairsBrickImagePath, 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
	}
	inp.close();

	for (int i = 0; i < 15; ++i) {
		Blocks->push_back(std::make_shared<Brick>("Brick", MyAPP::MyResourcesFilePath::StairsBrickImagePath, 10));
		Blocks->back()->SetPosition({ GetX0(Block) - Block->GetSize().x, GetY0(Block) - Block->GetSize().y * (i) });
	}
	std::for_each(Blocks->begin(), Blocks->end(), [](auto& it) { it->SetVisible(false); });
	/*for (auto& it : Blocks) {
		it->SetVisible(false);
	}*/

	/*init QuestionBlock*/
	std::vector<std::shared_ptr<QuestionBlock>> QuestionBlocks;

	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_QuestionBlock.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_QuestionBlock.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		QuestionBlocks.push_back(std::make_shared<QuestionBlock>("QuestionBlock", "imgs/super mario/QuestionBlock/frame0.png", 10));
		QuestionBlocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
	}
	inp.close();
	std::copy(QuestionBlocks.begin(), QuestionBlocks.end(), std::back_inserter(*Blocks));
	/*for (auto& it : QuestionBlocks) {
		Blocks.push_back(it);
	}*/

	/*init Brick*/
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_Brick.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_Brick.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		Blocks->push_back(std::make_shared<Brick>("Brick", MyAPP::MyResourcesFilePath::BlockImagePath, 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
	}
	inp.close();

	/*init Stairs*/
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_StairsBrick.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_StairsBrick.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		Blocks->push_back(std::make_shared<Brick>("StairsBrick", MyAPP::MyResourcesFilePath::StairsBrickImagePath, 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
	}
	inp.close();

	///*init Coin*/
	for (int i = 0; i < 10; ++i) {
		Blocks->push_back(std::make_shared<Coin>("coin", 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (12 + i), GetY0(Block) - Block->GetSize().x * 11 });
		Blocks->push_back(std::make_shared<Coin>("coin", 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (12 + i), GetY0(Block) - Block->GetSize().x * 10 });
	}


	Blocks->push_back(std::make_shared<HiddenBrick>("HiddenBrick", HiddenBrick::GetDefultImagePath(), 10));
	Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (64), GetY0(Block) - Block->GetSize().x * 8 });


	Blocks->push_back(std::move(MakeObject::make_SpinningFireBalls("", { -200, -200 })));


	std::for_each(Blocks->begin(), Blocks->end(), [&](auto& it) { MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, it); });
	//for (auto& it : Blocks) {
	//	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, it);
	//	/*char tmpstr[512];
	//	std::snprintf(tmpstr, sizeof(tmpstr), "%d %d ", (int)((it->GetPosition().x - GetX0(Block)) / Block->GetSize().x), (int)(-(it->GetPosition().y - GetY0(Block)) / Block->GetSize().y));
	//	outfile << tmpstr;*/
	//}
	// outfile.close();

	//mario->userdata = img->userdata = std::move(std::make_shared<std::vector<std::shared_ptr<Brick>>>(Blocks));

	auto texttime = std::make_shared<TextObject>("Timetext", MyAPP::MyResourcesFilePath::MyFontPath, 20, "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetX0(texttime), GetY0(texttime) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, texttime);

	//std::vector<std::shared_ptr<Character>> enemys;

	enemys->push_back(std::make_shared<Goomba>("Goomba", 50));
	(*enemys)[0]->SetPosition({ -GetX0((*enemys)[0]), 0 });
	/*for (int i = 0; i < 2; ++i) {
		enemys.push_back(std::make_shared<Goomba>("Goomba", Goomba::imgs[0], 50));
		enemys.back()->SetPosition({ GetX0(enemys[0]) + enemys[0]->GetSize().x * i, 0 });
	}*/

	std::vector<std::shared_ptr<Turtle>> turtles;
	turtles.push_back(std::make_shared<Turtle>("Turtle", 50));
	turtles.back()->SetPosition({ -GetX0((*enemys)[0]) + 64, 0 });
	std::copy(turtles.begin(), turtles.end(), std::back_inserter(*enemys));
	/*for (auto& it : turtles) {
		enemys.push_back(it);
	}*/

	std::for_each(enemys->begin(), enemys->end(),
		[&](auto& it) {
			it->userdata = mario->userdata;
			MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, it); 
		});
	/*for (auto& it : enemys) {
		it->userdata = mario->userdata;
		MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, it);
	}*/

	std::vector<std::shared_ptr<Props::Props>> props;
	props.push_back(std::make_shared<Props::FireFlower>("FireFlower", 10));
	props.back()->SetPosition({ GetX0(Block), 0 });
	props.push_back(std::make_shared<Props::Mushroom>("Mushroom", Props::Mushroom::GetImages<Props::Mushroom::Category::Mushroom>(), Props::Mushroom::Category::Mushroom, 10));
	props.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 2, 0 });
	props.push_back(std::make_shared<Props::Mushroom>("Mushroom", Props::Mushroom::GetImages<Props::Mushroom::Category::MushroomDark>(), Props::Mushroom::Category::MushroomDark, 10));
	props.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 3, 0 });
	props.push_back(std::make_shared<Props::Mushroom>("Mushroom", Props::Mushroom::GetImages<Props::Mushroom::Category::BigMushroom>(), Props::Mushroom::Category::BigMushroom, 10));
	props.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 4, 0 });
	props.push_back(std::make_shared<Props::Starman>("Starman", 10));
	props.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 6, 0 });
	std::for_each(std::execution::seq, props.begin(), props.end(), [&](auto& it) { MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, it); });

	self->sfx = std::make_shared<Util::SFX>(MyAPP::MyResourcesFilePath::Game_Over);
	self->bgm = std::make_shared<Util::BGM>(MyAPP::MyResourcesFilePath::Ground_Theme);
	auto& sfx = self->sfx;
	auto& bgm = self->bgm;
	bgm->Play(-1);

	auto text = std::make_shared<TextObject>("HPText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetX0(text), GetY0(text) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, text);

	auto pointtext = std::make_shared<TextObject>("PointText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetY0(pointtext) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, pointtext);

	auto eventobj = std::make_shared<EventObject>("freeForm_1_1_pipe", freeForm, false);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1_Pipe);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<std::tuple<std::vector<std::shared_ptr<Character>>, std::vector<std::shared_ptr<Brick>>, std::vector<std::shared_ptr<Props::Props>>>>(*enemys, *pipes, props);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int, std::shared_ptr<TextObject>>>(0, 300, texttime);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	// eventobj = std::make_shared<EventObject>("QuestionBlockPlayGIF", QuestionBlockPlayGIF);
	// eventobj->userdata = std::make_shared<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<Object::ImageObject>>>>(std::make_shared<int>(0), std::make_shared<int>(0), QuestionBlocks);
	// MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckEneyCollision", CheckEneyCollision);
	eventobj->userdata = std::move(enemys);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckFlagpoleCollision", CheckFlagpoleCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Brick>>>(flagpole);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	//eventobj = std::make_shared<EventObject>("CheckCoinsCollision", CheckCoinsCollision);
	//eventobj->userdata = std::move(coins);
	//MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor, false);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckPointCollision", CheckPointCollision, true);
	auto& ptr = eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<CheckPoint>>>(checkPointArray);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	eventobj = std::make_shared<EventObject>("CheckTortoiseShellCollision", CheckTortoiseShellCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Turtle>>>(turtles);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = ptr;
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));

	writeForm(MyFM, MyAPP::Form::FormNames::Form_1_1);
}

/// <summary>
/// ��l��1-1����
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_1_Pip) {
	auto& MyFM = self->GetFormManger();

	auto enemys = MakeObject::make_Characters();
	auto pipes = MakeObject::make_Bricks();

	std::array<std::shared_ptr<Brick>, 2> doorarr = { std::make_shared<Brick>("door", MyAPP::MyResourcesFilePath::StairsBrickImagePath, 10) };
	std::unique_ptr<Brick> Block = std::make_unique<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 1);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_1_Pipe_ImagePath, MakeObject::make_Bricks(), { GetX0(Block) + Block->GetSize().x * 3, 100 });
	auto& img = BMptr.first;
	auto& mario = BMptr.second;
	auto Blocks = (std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(img->userdata));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::move(img));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, mario);

	doorarr[1] = doorarr[0];
	doorarr[0]->SetPosition({ GetX0(Block) + Block->GetSize().x * 14, GetY0(Block) - Block->GetSize().y * (12) });
	doorarr[0]->collisionable = false;
	std::copy(doorarr.begin(), doorarr.end(), std::back_inserter(*Blocks));
	/*for (auto& it : doorarr) {
		Blocks.push_back(it);
	}*/


	for (int i = 0; i < 17; ++i) {
		Blocks->push_back(std::make_shared<Brick>("floor", MyAPP::MyResourcesFilePath::FloorImagePath, 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i + 1), GetY0(Block) - Block->GetSize().y * (13) });
	}
	for (int i = 0; i < 11; ++i) {
		Blocks->push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x, GetY0(Block) - Block->GetSize().y * (2 + i) });
	}
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks->push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 10));
			Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (5 + i), GetY0(Block) - Block->GetSize().y * (10 + j) });
		}
	}
	for (int i = 0; i < 7; ++i) {
		Blocks->push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (5 + i), GetY0(Block) - Block->GetSize().y * (2) });
	}
	for (int i = 0; i < 11; ++i) {
		Blocks->push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 10));
		Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 16, GetY0(Block) - Block->GetSize().y * (2 + i) });
	}
	Blocks->push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 10));
	Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 15, GetY0(Block) - Block->GetSize().y * (11) });
	Blocks->push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 10));
	Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 14, GetY0(Block) - Block->GetSize().y * (11) });

	std::for_each(Blocks->begin(), Blocks->end(),
		[&](auto& it) {
			it->SetVisible(false);
		});

	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 3; ++j) {
			if ((i == 0 || i == 6) && j == 0)
				continue;
			Blocks->push_back(std::make_shared<Coin>("Coin", 10));
			Blocks->back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (5 + i), GetY0(Block) - Block->GetSize().y * (5 + j * 2) });
		}
	}

	//std::for_each(Blocks.begin(), Blocks.end(),
	//	[&](auto& it) {
	//		MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, it);
	//	});
	/*for (auto& it : coins) {
		MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, it);
	}*/

	std::for_each(Blocks->begin(), Blocks->end(),
		[&](auto& it) {
			//it->SetVisible(false);
			MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, it);
		});
	//for (auto& it : Blocks) {
	//	it->SetVisible(false);
	//	// MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, it);
	//}


	/* auto& bgm = self->bgm = std::make_shared<Util::BGM>(Underground_Theme);
	bgm->Play(-1);*/

	auto text = std::make_shared<TextObject>("HPText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetX0(text), GetY0(text) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, text);

	auto pointtext = std::make_shared<TextObject>("PointText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetY0(pointtext) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, pointtext);

	auto texttime = std::make_shared<TextObject>("Timetext", MyAPP::MyResourcesFilePath::MyFontPath, 20, "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetX0(texttime), GetY0(texttime) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, texttime);

	auto eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<std::tuple<std::vector<std::shared_ptr<Character>>, std::vector<std::shared_ptr<Brick>>, std::vector<std::shared_ptr<Props::Props>>>>(*enemys, *pipes, std::vector<std::shared_ptr<Props::Props>>());
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int, std::shared_ptr<TextObject>>>(0, 300, texttime);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::move(eventobj));

	// eventobj = std::make_shared<EventObject>("CheckEneyCollision", CheckEneyCollision);
	// eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Object::Character>>>(enemys);
	// MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::move(eventobj));

	//eventobj = std::make_shared<EventObject>("CheckCoinsCollision", CheckCoinsCollision);
	//eventobj->userdata = std::move(coins);
	//MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_Pipe, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
}

/// <summary>
/// ��l��1-1��1-2�L��
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_1_to_1_2) {
	auto& MyFM = self->GetFormManger();

	std::array<std::shared_ptr<Brick>, 2> doorarr = { std::make_shared<Brick>("door", MyAPP::MyResourcesFilePath::StairsBrickImagePath, 10) };
	std::unique_ptr<Brick> Block = std::make_unique<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 1);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_1_to_1_2_ImagePath, MakeObject::make_Bricks(), { GetX0(Block) + Block->GetSize().x * 2, GetY0(Block) - Block->GetSize().y * (12) });
	auto& img = BMptr.first;
	auto& mario = BMptr.second;
	auto& Blocks = *(std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(img->userdata));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_to_1_2, std::move(img));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_to_1_2, mario);

	doorarr[1] = doorarr[0];
	doorarr[0]->SetPosition({ GetX0(Block) + Block->GetSize().x * 11, GetY0(Block) - Block->GetSize().y * (12) });
	doorarr[0]->collisionable = false;
	std::copy(doorarr.begin(), doorarr.end(), std::back_inserter(Blocks));
	/*for (auto& it : doorarr) {
		Blocks.push_back(it);
	}*/

	for (int i = 0; i < 20; ++i) {
		Blocks.push_back(std::make_shared<Brick>("floor", MyAPP::MyResourcesFilePath::FloorImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i + 1), GetY0(Block) - Block->GetSize().y * (13) });
	}

	auto eventobj = std::make_shared<EventObject>("freeForm_1_1", freeForm);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_to_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent);
	eventobj->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(30, std::vector<bool>());
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_to_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_to_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_to_1_2, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_1_to_1_2, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
}

/// <summary>
/// ��l��1-2�a��
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_2) {
	auto& MyFM = self->GetFormManger();

	auto enemys = MakeObject::make_Characters();
	auto pipes = MakeObject::make_Bricks();
	std::array<std::shared_ptr<Brick>, 2> doorarr = { std::make_shared<Brick>("door", MyAPP::MyResourcesFilePath::StairsBrickImagePath, -10) };
	std::vector<std::shared_ptr<CheckPoint>> checkPointArray;

	std::unique_ptr<Brick> Block = std::make_unique<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 1);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_2_ImagePath, MakeObject::make_Bricks(), { GetX0(Block) + Block->GetSize().x * 5, 100 });
	auto& img = BMptr.first;
	auto& mario = BMptr.second;
	auto& Blocks = *(std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(img->userdata));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(img));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, mario);

	doorarr[0]->SetPosition({ Block->GetSize().x * 167 + GetX0(Block), GetY0(Block) - 9 * Block->GetSize().y });
	doorarr[0]->collisionable = false;
	doorarr[0]->SetVisible(false);
	doorarr[1] = doorarr[0];
	Blocks.push_back(doorarr[0]);

	checkPointArray.push_back(std::make_shared<CheckPoint>("checkpoint"));
	checkPointArray[0]->collisionable = false;
	checkPointArray[0]->SetVisible(false);
	checkPointArray[0]->SetPosition({ 0, 0 });

	std::copy(checkPointArray.begin(), checkPointArray.end(), std::back_inserter(Blocks));
	/*for (auto& it : checkPointArray) {
		Blocks.push_back(it);
	}*/

	for (int i = 0; i < 2; ++i) {
		Blocks.push_back(std::make_shared<Coin>("coin", 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (12 + i), GetY0(Block) - Block->GetSize().x * 11 });
		Blocks.push_back(std::make_shared<Coin>("coin", 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (12 + i), GetY0(Block) - Block->GetSize().x * 10 });
	}
	//std::copy(coins->begin(), coins->end(), std::back_inserter(Blocks));
	//for (auto& it : coins) {
	//	// std::cout << &it->imgs << '\n';
	//	Blocks.push_back(it);
	//	// MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, it);
	//}

	pipes->push_back(std::make_shared<Brick>("Pipe", MyAPP::MyResourcesFilePath::BlockImagePath, 10));
	(*pipes)[0]->SetPosition({ GetX0(Block) + 104.5 * Block->GetSize().x, GetY0(Block) - 9 * Block->GetSize().y });
	(*pipes)[0]->collisionable = false;
	(*pipes)[0]->SetVisible(false);
	Blocks.push_back((*pipes)[0]);

	for (int i = 0; i < 193; i++) {
		if (i > 80 && i < 84 || i > 120 && i < 123 || i > 124 && i < 127 || i > 138 && i < 146 || i > 153 && i < 161) {
			continue;
		}
		Blocks.push_back(std::make_shared<Brick>("Floor", MyAPP::MyResourcesFilePath::FloorDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + i * Block->GetSize().x, GetY0(Block) - 13 * Block->GetSize().y });
		Blocks.push_back(std::make_shared<Brick>("Floor", MyAPP::MyResourcesFilePath::FloorDarkImagePath, 10));
		Blocks.back()->SetPosition({ i * Block->GetSize().x + GetX0(Block), GetY0(Block) - 14 * Block->GetSize().y });
	}

	for (int i = 2; i < 13; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block), GetY0(Block) - i * Block->GetSize().y });
	}
	for (int i = 6; i < 139; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * i, GetY0(Block) - 2 * Block->GetSize().y });
	}
	for (int i = 162; i < 169; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * i, GetY0(Block) - 2 * Block->GetSize().y });
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j <= i; ++j) {
			Blocks.push_back(std::make_shared<Brick>("StairsBrick", MyAPP::MyResourcesFilePath::StairsBrickDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i * 2 + 17), GetY0(Block) - (12 - j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 4; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", MyAPP::MyResourcesFilePath::StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (25), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	for (int i = 0; i < 3; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", MyAPP::MyResourcesFilePath::StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (27), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	for (int i = 0; i < 3; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", MyAPP::MyResourcesFilePath::StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (31), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	for (int i = 0; i < 2; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", MyAPP::MyResourcesFilePath::StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (33), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 29, GetY0(Block) - 8 * Block->GetSize().y });
	for (int j = 0; j <= 2; j += 2) {
		for (int i = 0; i < 3; ++i) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (39 + j), GetY0(Block) - (7 + i) * Block->GetSize().y });
		}
	}
	for (int j = 0; j <= 2; j += 2) {
		for (int i = 0; i < 3; ++i) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (44 + j), GetY0(Block) - (7 + i) * Block->GetSize().y });
		}
	}
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (40), GetY0(Block) - (9) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (45), GetY0(Block) - (9) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (42), GetY0(Block) - (7) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (43), GetY0(Block) - (7) * Block->GetSize().y });
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (54 + i), GetY0(Block) - (3 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (54 + i), GetY0(Block) - (9 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 6; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (52 + i), GetY0(Block) - (5 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (i < 4 && j >= 2 && j < 6) {
				continue;
			}
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (58 + i), GetY0(Block) - (3 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (66 + i), GetY0(Block) - (3 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 5; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (67), GetY0(Block) - (5 + i) * Block->GetSize().y });
	}
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (68), GetY0(Block) - (9) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (69), GetY0(Block) - (9) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (69), GetY0(Block) - (8) * Block->GetSize().y });
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 5; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (72 + i), GetY0(Block) - (5 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (76 + i), GetY0(Block) - (3 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 5; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (76 + i), GetY0(Block) - (9) * Block->GetSize().y });
	}
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (85 + i), GetY0(Block) - (7 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (123 + i), GetY0(Block) - (10 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 6; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (146 + i), GetY0(Block) - (8) * Block->GetSize().y });
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j <= i; ++j) {
			Blocks.push_back(std::make_shared<Brick>("StairsBrick", MyAPP::MyResourcesFilePath::StairsBrickDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (134 + i), GetY0(Block) - (12 - j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 4; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", MyAPP::MyResourcesFilePath::StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (138), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	for (int i = 0; i < 17; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (161 + i), GetY0(Block) - (10 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 8; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (171 + i), GetY0(Block) - (2 + j) * Block->GetSize().y });
		}
	}

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("pipe", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (104 + i), GetY0(Block) - (12 - j) * Block->GetSize().y });
			Blocks.back()->SetVisible(false);
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			Blocks.push_back(std::make_shared<Brick>("pipe", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (110 + i), GetY0(Block) - (12 - j) * Block->GetSize().y });
			Blocks.back()->SetVisible(false);
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("pipe", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (116 + i), GetY0(Block) - (12 - j) * Block->GetSize().y });
			Blocks.back()->SetVisible(false);
		}
	}
	for (int j = 0; j < 8; ++j) {
		Blocks.push_back(std::make_shared<Brick>("pipe", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (170), GetY0(Block) - (12 - j) * Block->GetSize().y });
		Blocks.back()->SetVisible(false);
	}
	Blocks.push_back(std::make_shared<Brick>("pipe", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ Block->GetSize().x * 168 + GetX0(Block), GetY0(Block) - 8 * Block->GetSize().y });
	Blocks.back()->SetVisible(false);
	Blocks.push_back(std::make_shared<Brick>("pipe", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ Block->GetSize().x * 169 + GetX0(Block), GetY0(Block) - 8 * Block->GetSize().y });
	Blocks.back()->SetVisible(false);
	Blocks.push_back(std::make_shared<Brick>("pipe", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ Block->GetSize().x * 167 + GetX0(Block), GetY0(Block) - 8 * Block->GetSize().y });
	Blocks.back()->SetVisible(false);

	std::vector<std::shared_ptr<QuestionBlock>> QuestionBlocks;
	for (int i = 10; i < 15; ++i) {
		QuestionBlocks.push_back(std::make_shared<QuestionBlock>("QuestionBlock", MyAPP::MyResourcesFilePath::StairsBrickImagePath, 10));
		QuestionBlocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * i, GetY0(Block) - 9 * Block->GetSize().y });
	}

	std::transform(QuestionBlocks.begin(), QuestionBlocks.end(), std::back_inserter(Blocks),
		[](auto& it) {
			it->setDark();
			return it;
		});
	//std::copy(QuestionBlocks.begin(), QuestionBlocks.end(), std::back_inserter(Blocks));
	//for (auto& it : QuestionBlocks) {
	//	//it->setDark();
	//	Blocks.push_back(it);
	//}

	std::for_each(Blocks.begin(), Blocks.end(),
		[&](auto& it) {
			MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, it);
		});
	/*for (auto& it : Blocks) {
		MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, it);
	}*/


	/*enemys.push_back(std::make_shared<Goomba>("Goomba", Goomba::imgs[0], 50));
	enemys[0]->SetPosition({ GetX0(enemys[0]) + enemys[0]->GetSize().x, 0 });*/

	std::for_each(enemys->begin(), enemys->end(),
		[&](auto& it) {
			it->userdata = mario->userdata;
			MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, it);
		});
	/*for (auto& it : enemys) {
		it->userdata = mario->userdata;
		MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, it);
	}*/

	auto text = std::make_shared<TextObject>("HPText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetX0(text), GetY0(text) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, text);

	auto pointtext = std::make_shared<TextObject>("PointText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetY0(pointtext) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, pointtext);

	auto texttime = std::make_shared<TextObject>("Timetext", MyAPP::MyResourcesFilePath::MyFontPath, 20, "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetX0(texttime), GetY0(texttime) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, texttime);

	auto eventobj = std::make_shared<EventObject>("freeForm_1_2_Pipe", freeForm, false);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2_Pipe);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<std::tuple<std::vector<std::shared_ptr<Character>>, std::vector<std::shared_ptr<Brick>>, std::vector<std::shared_ptr<Props::Props>>>>(*enemys, *pipes, std::vector<std::shared_ptr<Props::Props>>());
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int, std::shared_ptr<TextObject>>>(0, 300, texttime);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckEneyCollision", CheckEneyCollision);
	eventobj->userdata = std::move(enemys);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	/*eventobj = std::make_shared<EventObject>("CheckFlagpoleCollision", CheckFlagpoleCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Brick>>>(flagpole);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));*/

	//eventobj = std::make_shared<EventObject>("CheckCoinsCollision", CheckCoinsCollision);
	//eventobj->userdata = std::move(coins);
	//MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor, false);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckPointCollision", CheckPointCollision, true);
	auto& ptr = eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<CheckPoint>>>(checkPointArray);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	/*eventobj = std::make_shared<EventObject>("CheckTortoiseShellCollision", CheckTortoiseShellCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Turtle>>>(turtles);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));*/

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = ptr;
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
}

/// <summary>
/// ��l��1-2����
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_2_Pipe) {
	auto& MyFM = self->GetFormManger();

	auto enemys = MakeObject::make_Characters();
	auto pipes = MakeObject::make_Bricks();
	std::array<std::shared_ptr<Brick>, 2> doorarr = { std::make_shared<Brick>("door", MyAPP::MyResourcesFilePath::StairsBrickImagePath, 10) };

	std::unique_ptr<Brick> Block = std::make_unique<Brick>("brick", MyAPP::MyResourcesFilePath::BlockImagePath, 1);

	auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::Background_1_2_Pipe_ImagePath, MakeObject::make_Bricks(), { GetX0(Block) + Block->GetSize().x * 3, 100 });
	auto& img = BMptr.first;
	auto& mario = BMptr.second;
	auto& Blocks = *(std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(img->userdata));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::move(img));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, mario);

	doorarr[0]->SetPosition({ GetX0(Block) + Block->GetSize().x * 14, GetY0(Block) - Block->GetSize().y * (12) });
	doorarr[0]->collisionable = false;
	doorarr[0]->SetVisible(false);
	doorarr[1] = doorarr[0];
	std::copy(doorarr.begin(), doorarr.end(), std::back_inserter(Blocks));
	/*for (auto& it : doorarr) {
		Blocks.push_back(it);
	}*/


	for (int i = 0; i < 17; ++i) {
		Blocks.push_back(std::make_shared<Brick>("floor", MyAPP::MyResourcesFilePath::FloorDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i + 1), GetY0(Block) - Block->GetSize().y * (13) });
	}
	std::for_each(Blocks.begin(), Blocks.end(),
		[](auto& it) {
			it->SetVisible(false);
		});
	for (int i = 0; i < 11; ++i) {
		Blocks.push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x, GetY0(Block) - Block->GetSize().y * (2 + i) });
	}
	for (int i = 0; i < 10; ++i) {
		Blocks.push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (4 + i), GetY0(Block) - Block->GetSize().y * (9) });
	}
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 4; ++j) {
			Blocks.push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (4 + i), GetY0(Block) - Block->GetSize().y * (2 + j) });
		}
	}
	for (int i = 0; i < 9; ++i) {
		Blocks.push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (14), GetY0(Block) - Block->GetSize().y * (2 + i) });
		Blocks.push_back(std::make_shared<Brick>("brick", MyAPP::MyResourcesFilePath::BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (15), GetY0(Block) - Block->GetSize().y * (2 + i) });
	}

	for (int i = 0; i < 9; ++i) {
		Blocks.push_back(std::make_shared<Coin>("Coin", 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i + 4), GetY0(Block) - Block->GetSize().y * (12) });
	}
	for (int i = 0; i < 8; ++i) {
		Blocks.push_back(std::make_shared<Coin>("Coin", 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i + 5), GetY0(Block) - Block->GetSize().y * (8) });
	}

	for (auto& it : Blocks) {
		MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, it);
	}

	auto text = std::make_shared<TextObject>("HPText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetX0(text), GetY0(text) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, text);

	auto pointtext = std::make_shared<TextObject>("PointText", MyAPP::MyResourcesFilePath::MyFontPath, 20, "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetY0(pointtext) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, pointtext);

	auto texttime = std::make_shared<TextObject>("Timetext", MyAPP::MyResourcesFilePath::MyFontPath, 20, "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetX0(texttime), GetY0(texttime) });
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, texttime);

	auto eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<std::tuple<std::vector<std::shared_ptr<Character>>, std::vector<std::shared_ptr<Brick>>, std::vector<std::shared_ptr<Props::Props>>>>(*enemys, *pipes, std::vector<std::shared_ptr<Props::Props>>());
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int, std::shared_ptr<TextObject>>>(0, 300, texttime);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::move(eventobj));

	//eventobj = std::make_shared<EventObject>("CheckCoinsCollision", CheckCoinsCollision);
	//eventobj->userdata = std::move(coins);
	//MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::move(eventobj));

	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(MyAPP::Form::FormNames::Form_1_2_Pipe, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
}


#endif // !INITFORMFUNC_HPP
