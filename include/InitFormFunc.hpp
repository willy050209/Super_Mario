#define INITFORM_FUNC(func_name) void func_name(GameManager* self) noexcept

/// <summary>
/// 初始化1-2地圖
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_2);

/// <summary>
/// 初始化1-1水管
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_1_Pip);

/// <summary>
/// 初始化1-1到1-2過場
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_1_to_1_2);
INITFORM_FUNC(winForm);

#ifndef INITFORMFUNC_HPP
#define INITFORMFUNC_HPP

#include "ButtonCallBackFunc.hpp"
#include "EventCallBackFunc.hpp"
#include "incallobj.hpp"
#include "Position.hpp"
#include "config.hpp"
#include "ProgressBar.hpp"

#include <memory>
#include <tuple>
#include <fstream>


INITFORM_FUNC(initFormBackground) {

	auto& MyFM = self->GetFormManger();

	std::thread initenent([&]() {
		auto event = std::make_shared<EventObject>("SystemTime", GetSystemTimeFunc, true);
		event->userdata = std::make_shared<int>(0);
		MyFM.addObject(FormBackground, event);
	});

	/*add images to FormBackground*/
	auto tmpImage = std::make_shared<ImageObject>("cat0", BackgroundImagePath, -10);
	tmpImage->SetPosition({ GetX0(tmpImage), GetY0(tmpImage) - (WINDOW_HEIGHT - tmpImage->GetSize().y) });
	MyFM.addObject(FormBackground, tmpImage);

	auto tmptest = std::make_shared<ImageObject>("mario_walk", MY_RESOURCE_DIR "\\super mario\\Mario\\frame0.png", 100);
	tmptest->SetPosition({ 100, 100 });
	MyFM.addObject(FormBackground, tmptest);

	tmpImage = (std::make_shared<ImageObject>("cat1", BackgroundImagePath, -10));
	MyFM.addObject(FormBackground, tmpImage);

	tmpImage = (std::make_shared<ImageObject>("phase0", MY_RESOURCE_DIR "/super mario/Maps/SuperMarioBrosMap1-1BG.png", 1));
	tmpImage->SetPosition({ GetX0(tmpImage), 0 });
	MyFM.addObject(FormBackground, tmpImage);

	/*add characters to FormBackground*/
	auto mario = (std::make_shared<Mario>("Mario", marioImagePath, 10));
	mario->SetPosition({ 0, 300 });
	mario->userdata = std::static_pointer_cast<void>(tmpImage);
	MyFM.addObject(FormBackground, mario);


	/*add Texts to FormBackground*/
	auto text(std::make_shared<TextObject>("Text0", ArialFontPath, 20, "Text Output Example(Font = Arial)", Util::Color::FromName(Util::Colors::YELLOW), 10));
	text->SetPosition({ -400, 300 });
	text->SetPosition({ GetX0(text), GetY0(text) });
	MyFM.addObject(FormBackground, text);

	MyFM.addObject(FormBackground, std::make_shared<TextObject>("HelloWorld", ArialFontPath, 50, "Hello world!!", Util::Color::FromRGB(255, 255, 255), 10));


	/*add buttons to FormBackground*/
	for (int i = 0; i < 10; ++i) {
		auto buttonptr = std::make_shared<Button>("button" + std::to_string(i), ArialFontPath, 20, "This is a button" + std::to_string(i), Util::Color::FromName(Util::Colors::YELLOW_GREEN), 20);
		buttonptr->SetPosition({ GetX0(buttonptr) + 100, GetY0(buttonptr) - 50 * (i + 1) });
		buttonptr->userdata = std::make_shared<int>(0);
		buttonptr->SetCallBackFunc(callBackTest);
		MyFM.addObject(FormBackground, buttonptr);
	}
	///*give BGM to FormBackground*/
	// auto tmp = std::make_shared<Util::BGM>(MY_RESOURCE_DIR"/BGM/wakeup music.mp3");
	////tmp->LoadMedia(MY_RESOURCE_DIR"/BGM/wakeup music.mp3");
	// tmp->Play(-1);
	// auto tmpdouble = std::make_shared<Util::BGM>(MY_RESOURCE_DIR"/BGM/01. Ground Theme.mp3");
	////tmpdouble->LoadMedia(MY_RESOURCE_DIR"/BGM/01. Ground Theme.mp3");
	// tmpdouble->Play(-1);

	/////*time_try*/
	// time_t now = time(0);
	// std::string tm = ctime(&now);
	////std::cout << tm << '\n';
	// auto texttime = std::make_shared<TextObject>("Timetext", ArialFontPath, 20, tm, Util::Color::FromName(Util::Colors::WHITE), 100);
	// texttime->SetPosition({100,100 });
	// texttime->SetPosition({ GetX0(texttime),GetY0(texttime) });
	// MyFM.addObject(Form_1_1, texttime);

	initenent.join();
}

/*init Titel Form*/
INITFORM_FUNC(initFormTitle) {

	constexpr auto textSize = 50;
	auto&& textColor = Util::Color::FromName(Util::Colors::YELLOW);

	auto& MyFM = self->GetFormManger();

	auto button = std::make_shared<Button>("Start", MyFontPath, textSize, "Start", textColor, 10);
	button->SetPosition({ 0, 2 * button->GetSize().y });
	button->SetCallBackFunc(StartButtonEvent);

	MyFM.addObject(FormTitel, button);
	button = std::make_shared<Button>("Options", MyFontPath, textSize, "Options", textColor, 10);
	button->SetCallBackFunc(CallOptionForm);
	MyFM.addObject(FormTitel, button);

	button = std::make_shared<Button>("ExitButton", MyFontPath, textSize, "Exit", textColor, 10);
	button->SetPosition({ 0, -(2 * button->GetSize().y) });
	button->SetCallBackFunc(exitCallBack);
	MyFM.addObject(FormTitel, button);

	auto image = std::make_shared<ImageObject>("QRcode", MY_RESOURCE_DIR "/Image/Background/qrcode.png", -10);
	MyFM.addObject("help", image);
	MyFM.changeForm(FormTitel);
}

/*init Options Form*/
INITFORM_FUNC(initFormOptions) {
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("ExitButton", MyFontPath, 50, "Exit", Util::Color::FromName(Util::Colors::SLATE_BLUE), 100);
	tmpbutton->SetPosition({ 0,
		GetY0(tmpbutton) - (WINDOW_HEIGHT - tmpbutton->GetSize().y) + 50 });
	tmpbutton->SetCallBackFunc(exitCallBack);
	MyFM.addObject(FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("SettingButton", MyFontPath, 50, "Setting", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0, tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(CallSettingForm);
	MyFM.addObject(FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("HelpButton", MyFontPath, 50, "Help", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0, 0 });
	tmpbutton->SetCallBackFunc(HelpButtonEvent);
	tmpbutton->userdata = std::make_shared<std::string>("start https://ntut-open-source-club.github.io/practical-tools-for-simple-design/");
	MyFM.addObject(FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("BackButton", MyFontPath, 50, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton), GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(FormOptions, tmpbutton);
}

INITFORM_FUNC(initFormSetting) {
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("BackButton", MyFontPath, 40, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton), GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(FormSetting, tmpbutton);

	auto text = std::make_shared<TextObject>("VolumeValueText", MyFontPath, 30, std::to_string(MyBGM::GetVolume()), Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ 2 * text->GetSize().x, 0 });
	MyFM.addObject(FormSetting, text);

	tmpbutton = std::make_shared<Button>("Volume-Button", MyFontPath, 30, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, (tmpbutton->GetSize().y * -2) });
	tmpbutton->SetCallBackFunc(VolumeDownClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);

	tmpbutton = std::make_shared<Button>("Volume+Button", MyFontPath, 30, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, text->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(VolumeUpClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);

	text = std::make_shared<TextObject>("VolumeText", MyFontPath, 30, "Volume", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ tmpbutton->GetPosition().x, (text->GetSize().y * 2) + text->GetSize().y });
	MyFM.addObject(FormSetting, text);


	text = std::make_shared<TextObject>("ScreenSizeText", MyFontPath, 30, std::to_string(WINDOW_WIDTH) + "\n" + std::to_string(WINDOW_HEIGHT), Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ -2 * text->GetSize().x, 0 });
	MyFM.addObject(FormSetting, text);

	tmpbutton = std::make_shared<Button>("ScreenSize-Button", MyFontPath, 30, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, -(tmpbutton->GetSize().y * 2) });
	tmpbutton->SetCallBackFunc(ScreenSizeDownClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);

	tmpbutton = std::make_shared<Button>("ScreenSize+Button", MyFontPath, 30, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x, tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(ScreenSizeUpClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);

	text = std::make_shared<TextObject>("ScreenSizeText", MyFontPath, 30, "ScreenSize", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ tmpbutton->GetPosition().x, (text->GetSize().y * 2) + text->GetSize().y });
	MyFM.addObject(FormSetting, text);

	text = std::make_shared<TextObject>("", ArialFontPath, 20, "Restart to apply screen settings", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ GetX0(text), -GetY0(text) });
	MyFM.addObject(FormSetting, text);

	tmpbutton = std::make_shared<Button>("RestartButton", MyFontPath, 20, "Restart", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ -GetX0(tmpbutton), -GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(RestaetButtonEvent);
	MyFM.addObject(FormSetting, tmpbutton);
}

INITFORM_FUNC(winForm) {
	auto& MyFM = self->GetFormManger();
	MyFM.addObject("Win", std::make_shared<TextObject>("", MyFontPath, 20, "Win", Util::Color::FromName(Util::Colors::WHITE), 10));
}

/*init 1-1*/
INITFORM_FUNC(initForm_1_1) {
	auto& MyFM = self->GetFormManger();
	std::shared_ptr<Brick> Block = std::make_shared<Brick>("brick", BlockImagePath, 1);
	std::vector<std::shared_ptr<Brick>> Blocks;

	auto img = std::make_shared<ImageObject>("Background", Background_1_1_ImagePath, 1);
	img->SetPosition({ GetX0(img), 0 });
	MyFM.addObject(Form_1_1, img);

	auto mario = std::make_shared<Mario>("Mario", marioImagePath, 100);
	mario->SetPosition({ 0, 100 });
	// mario->SetPosition({ GetX0(Block) + Block->GetSize().x * 10, 100 });
	MyFM.addObject(Form_1_1, mario);

	std::vector<std::shared_ptr<CheckPoint>> checkPointArray;
	checkPointArray.push_back(std::make_shared<CheckPoint>("checkpoint"));
	checkPointArray[0]->collisionable = false;
	checkPointArray[0]->SetVisible(false);
	checkPointArray[0]->SetPosition({ 0, 0 });


	for (auto& it : checkPointArray) {
		Blocks.push_back(it);
	}
	// std::ofstream outfile("map.txt");

	/*init door*/
	std::ifstream inp(MY_RESOURCE_DIR "/MAP/map1_1_door.txt");
	float posx = 0, posy = 0;
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_door.txt";
		exit(-1);
	}
	std::array<std::shared_ptr<Brick>, 2> doorarr{ std::make_shared<Brick>("door", StairsBrickImagePath, -10), std::make_shared<Brick>("door", StairsBrickImagePath, -10) };
	for (int k = 0; k < 2; ++k) {
		doorarr[k]->collisionable = false;
		doorarr[k]->SetVisible(false);
		inp >> posx >> posy;
		doorarr[k]->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
		Blocks.push_back(doorarr[k]);
	}
	inp.close();

	/*init pipe*/
	std::vector<std::shared_ptr<Brick>> pieps;
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_pipe.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_pipe.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		pieps.push_back(std::make_shared<Brick>("pipe", StairsBrickImagePath, 10));
		pieps.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
		pieps.back()->collisionable = false;
	}
	inp.close();
	for (auto& it : pieps) {
		Blocks.push_back(it);
	}

	/*Flagpole collision box*/
	std::vector<std::shared_ptr<Brick>> flagpole;
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_Flagpole.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_Flagpole.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		flagpole.push_back(std::make_shared<Brick>("Flagpole", StairsBrickImagePath, 10));
		flagpole.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
		flagpole.back()->collisionable = false;
	}
	inp.close();
	for (auto& it : flagpole) {
		Blocks.push_back(it);
	}

	/*init floor*/
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_floor.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_floor.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		Blocks.push_back(std::make_shared<Brick>("Brick", StairsBrickImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
	}
	inp.close();

	for (int i = 0; i < 15; ++i) {
		Blocks.push_back(std::make_shared<Brick>("Brick", StairsBrickImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) - Block->GetSize().x , GetY0(Block) - Block->GetSize().y * (i) });
	}

	for (auto& it : Blocks) {
		it->SetVisible(false);
	}

	/*init QuestionBlock*/
	std::vector<std::shared_ptr<QuestionBlock>> QuestionBlocks;

	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_QuestionBlock.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_QuestionBlock.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		QuestionBlocks.push_back(std::make_shared<QuestionBlock>("QuestionBlock", StairsBrickImagePath, 10));
		QuestionBlocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
	}
	inp.close();

	for (auto& it : QuestionBlocks) {
		Blocks.push_back(it);
	}

	/*init Brick*/
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_Brick.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_Brick.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		Blocks.push_back(std::make_shared<Brick>("Brick", BlockImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
	}
	inp.close();

	/*init Stairs*/
	inp.open(MY_RESOURCE_DIR "/MAP/map1_1_StairsBrick.txt");
	if (!inp.is_open()) {
		std::cerr << "can't open" MY_RESOURCE_DIR "/MAP/map1_1_StairsBrick.txt";
		exit(-1);
	}
	while (inp >> posx >> posy) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", StairsBrickImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (posx), GetY0(Block) - Block->GetSize().y * (posy) });
	}
	inp.close();

	/*init Coin*/
	std::vector<std::shared_ptr<Coin>> coins;
	for (int i = 0; i < 10; ++i) {
		coins.push_back(std::make_shared<Coin>("coin", Coin::imgs[1], 10));
		coins.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (12 + i), GetY0(Block) - Block->GetSize().x * 11 });
		coins.push_back(std::make_shared<Coin>("coin", Coin::imgs[1], 10));
		coins.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (12 + i), GetY0(Block) - Block->GetSize().x * 10 });
	}
	for (auto& it : coins) {
		//std::cout << &it->imgs << '\n';
		Blocks.push_back(it);
	}

	for (auto& it : Blocks) {
		MyFM.addObject(Form_1_1, it);
		/*char tmpstr[512];
		std::snprintf(tmpstr, sizeof(tmpstr), "%d %d ", (int)((it->GetPosition().x - GetX0(Block)) / Block->GetSize().x), (int)(-(it->GetPosition().y - GetY0(Block)) / Block->GetSize().y));
		outfile << tmpstr;*/
	}
	// outfile.close();

	mario->userdata = img->userdata = std::make_shared<std::vector<std::shared_ptr<Brick>>>(Blocks);

	auto texttime = std::make_shared<TextObject>("Timetext", MyFontPath, 20, "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetX0(texttime), GetY0(texttime) });
	MyFM.addObject(Form_1_1, texttime);

	std::vector<std::shared_ptr<Character>> enemys;

	enemys.push_back(std::make_shared<Goomba>("Goomba", Goomba::imgs[0], 50));
	enemys[0]->SetPosition({ -GetX0(enemys[0]), 0 });
	/*for (int i = 0; i < 2; ++i) {
		enemys.push_back(std::make_shared<Goomba>("Goomba", Goomba::imgs[0], 50));
		enemys.back()->SetPosition({ GetX0(enemys[0]) + enemys[0]->GetSize().x * i, 0 });
	}*/

	std::vector<std::shared_ptr<Turtle>> turtles;
	turtles.push_back(std::make_shared<Turtle>("Turtle", Turtle::imgs[0], 50));
	turtles.back()->SetPosition({ -GetX0(enemys[0]) + 64 , 0 });
	for (auto& it : turtles) {
		enemys.push_back(it);
	}

	for (auto& it : enemys) {
		it->userdata = mario->userdata;
		MyFM.addObject(Form_1_1, it);
	}

	auto& bgm = self->bgm = std::make_shared<Util::BGM>(Ground_Theme);
	bgm->Play(-1);

	auto text = std::make_shared<TextObject>("HPText", MyFontPath, 20, "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetX0(text), GetY0(text) });
	MyFM.addObject(Form_1_1, text);

	auto pointtext = std::make_shared<TextObject>("PointText", MyFontPath, 20, "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetY0(pointtext) });
	MyFM.addObject(Form_1_1, pointtext);

	auto eventobj = std::make_shared<EventObject>("freeForm_1_1_pipe", freeForm, false);
	eventobj->userdata = std::make_shared<std::string>(Form_1_1_Pipe);
	MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<std::tuple<std::vector<std::shared_ptr<Character>>, std::vector<std::shared_ptr<Brick>>>>(enemys, pieps);
	MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int, std::shared_ptr<TextObject>>>(0, 300, texttime);
	MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(Form_1_1, eventobj);

	// eventobj = std::make_shared<EventObject>("QuestionBlockPlayGIF", QuestionBlockPlayGIF);
	// eventobj->userdata = std::make_shared<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<ImageObject>>>>(std::make_shared<int>(0), std::make_shared<int>(0), QuestionBlocks);
	// MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("CheckEneyCollision", CheckEneyCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Character>>>(enemys);
	MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("CheckFlagpoleCollision", CheckFlagpoleCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Brick>>>(flagpole);
	MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("CheckCoinsCollision", CheckCoinsCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Coin>>>(coins);
	MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor, false);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("CheckPointCollision", CheckPointCollision, true);
	auto& ptr = eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<CheckPoint>>>(checkPointArray);
	MyFM.addObject(Form_1_1, eventobj);

	MyFM.addObject(Form_1_1, std::make_shared<EventObject>("CheckMArioPosition", CheckMArioPosition));

	eventobj = std::make_shared<EventObject>("CheckTortoiseShellCollision", CheckTortoiseShellCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Turtle>>>(turtles);
	MyFM.addObject(Form_1_1, eventobj);

	MyFM.addObject(Form_1_1, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(Form_1_1, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(Form_1_1, eventobj);

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = ptr;
	MyFM.addObject(Form_1_1, eventobj);

	MyFM.addObject(Form_1_1, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(Form_1_1, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
}

INITFORM_FUNC(initForm_1_1_Pip) {
	auto& MyFM = self->GetFormManger();
	std::shared_ptr<Brick> Block = std::make_shared<Brick>("brick", BlockImagePath, 1);
	std::vector<std::shared_ptr<Brick>> Blocks;
	std::vector<std::shared_ptr<Character>> enemys;
	std::vector<std::shared_ptr<Brick>> pipes;
	std::vector<std::shared_ptr<Coin>> coins;
	std::array<std::shared_ptr<Brick>, 2> doorarr = { std::make_shared<Brick>("door", StairsBrickImagePath, 10) };

	auto mario = std::make_shared<Mario>("Mario", marioImagePath, 100);
	mario->SetPosition({ GetX0(Block) + Block->GetSize().x * 3, 100 });
	// mario->SetPosition({ GetX0(Block) + Block->GetSize().x * 10, 100 });
	MyFM.addObject(Form_1_1_Pipe, mario);

	auto img = std::make_shared<ImageObject>("Background", Background_1_1_Pipe_ImagePath, 1);
	img->SetPosition({ GetX0(img), 0 });
	MyFM.addObject(Form_1_1_Pipe, img);

	doorarr[1] = doorarr[0];
	doorarr[0]->SetPosition({ GetX0(Block) + Block->GetSize().x * 14, GetY0(Block) - Block->GetSize().y * (12) });
	doorarr[0]->collisionable = false;
	for (auto& it : doorarr) {
		Blocks.push_back(it);
	}


	for (int i = 0; i < 17; ++i) {
		Blocks.push_back(std::make_shared<Brick>("floor", FloorImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i + 1), GetY0(Block) - Block->GetSize().y * (13) });
	}
	for (int i = 0; i < 11; ++i) {
		Blocks.push_back(std::make_shared<Brick>("brick", BlockImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x, GetY0(Block) - Block->GetSize().y * (2 + i) });
	}
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("brick", BlockImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (5 + i), GetY0(Block) - Block->GetSize().y * (10 + j) });
		}
	}
	for (int i = 0; i < 7; ++i) {
		Blocks.push_back(std::make_shared<Brick>("brick", BlockImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (5 + i), GetY0(Block) - Block->GetSize().y * (2) });
	}
	for (int i = 0; i < 11; ++i) {
		Blocks.push_back(std::make_shared<Brick>("brick", BlockImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 16, GetY0(Block) - Block->GetSize().y * (2 + i) });
	}
	Blocks.push_back(std::make_shared<Brick>("brick", BlockImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 15, GetY0(Block) - Block->GetSize().y * (11) });
	Blocks.push_back(std::make_shared<Brick>("brick", BlockImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 14, GetY0(Block) - Block->GetSize().y * (11) });

	for (auto& it : Blocks) {
		it->SetVisible(false);
		//MyFM.addObject(Form_1_1_Pipe, it);
	}

	img->userdata = mario->userdata = std::make_shared<std::vector<std::shared_ptr<Brick>>>(Blocks);
	auto text = std::make_shared<TextObject>("HPText", MyFontPath, 20, "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetX0(text), GetY0(text) });
	MyFM.addObject(Form_1_1_Pipe, text);

	auto pointtext = std::make_shared<TextObject>("PointText", MyFontPath, 20, "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetY0(pointtext) });
	MyFM.addObject(Form_1_1_Pipe, pointtext);

	auto texttime = std::make_shared<TextObject>("Timetext", MyFontPath, 20, "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetX0(texttime), GetY0(texttime) });
	MyFM.addObject(Form_1_1_Pipe, texttime);

	auto eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<std::tuple<std::vector<std::shared_ptr<Character>>, std::vector<std::shared_ptr<Brick>>>>(enemys, pipes);
	MyFM.addObject(Form_1_1_Pipe, eventobj);

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int, std::shared_ptr<TextObject>>>(0, 300, texttime);
	MyFM.addObject(Form_1_1_Pipe, eventobj);

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(Form_1_1_Pipe, eventobj);

	//eventobj = std::make_shared<EventObject>("CheckEneyCollision", CheckEneyCollision);
	//eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Character>>>(enemys);
	//MyFM.addObject(Form_1_1_Pipe, eventobj);

	eventobj = std::make_shared<EventObject>("CheckCoinsCollision", CheckCoinsCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Coin>>>(coins);
	MyFM.addObject(Form_1_1_Pipe, eventobj);

	MyFM.addObject(Form_1_1_Pipe, std::make_shared<EventObject>("CheckMArioPosition", CheckMArioPosition));

	MyFM.addObject(Form_1_1_Pipe, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(Form_1_1_Pipe, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(Form_1_1_Pipe, eventobj);

	MyFM.addObject(Form_1_1_Pipe, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(Form_1_1_Pipe, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
}

INITFORM_FUNC(initForm_1_1_to_1_2) {
	auto& MyFM = self->GetFormManger();
	std::shared_ptr<Brick> Block = std::make_shared<Brick>("brick", BlockImagePath, 1);
	std::vector<std::shared_ptr<Brick>> Blocks;
	std::array<std::shared_ptr<Brick>, 2> doorarr = { std::make_shared<Brick>("door", StairsBrickImagePath, 10) };

	auto mario = std::make_shared<Mario>("Mario", marioImagePath, 100);
	mario->SetPosition({ GetX0(Block) + Block->GetSize().x * 2, GetY0(Block) - Block->GetSize().y * (12) });
	MyFM.addObject(Form_1_1_to_1_2, mario);

	auto img = std::make_shared<ImageObject>("Background", Background_1_1_to_1_2_ImagePath, 1);
	img->SetPosition({ GetX0(img), 0 });
	MyFM.addObject(Form_1_1_to_1_2, img);

	doorarr[1] = doorarr[0];
	doorarr[0]->SetPosition({ GetX0(Block) + Block->GetSize().x * 11, GetY0(Block) - Block->GetSize().y * (12) });
	doorarr[0]->collisionable = false;
	for (auto& it : doorarr) {
		Blocks.push_back(it);
	}

	for (int i = 0; i < 20; ++i) {
		Blocks.push_back(std::make_shared<Brick>("floor", FloorImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i + 1), GetY0(Block) - Block->GetSize().y * (13) });
	}

	img->userdata = mario->userdata = std::make_shared<std::vector<std::shared_ptr<Brick>>>(Blocks);

	auto eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(Form_1_1_to_1_2, eventobj);

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(Form_1_1_to_1_2, eventobj);

	MyFM.addObject(Form_1_1_to_1_2, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
}

INITFORM_FUNC(initForm_1_2) {
	auto& MyFM = self->GetFormManger();
	std::shared_ptr<Brick> Block = std::make_shared<Brick>("brick", BlockImagePath, 1);
	std::vector<std::shared_ptr<Brick>> Blocks;
	std::vector<std::shared_ptr<Character>> enemys;
	std::vector<std::shared_ptr<Brick>> pipes;
	std::vector<std::shared_ptr<Coin>> coins;
	std::array<std::shared_ptr<Brick>, 2> doorarr = { std::make_shared<Brick>("door", StairsBrickImagePath, -10)};
	std::vector<std::shared_ptr<CheckPoint>> checkPointArray;

	auto img = std::make_shared<ImageObject>("Background", Background_1_2_ImagePath, 1);
	img->SetPosition({ GetX0(img), 0 });
	MyFM.addObject(Form_1_2, img);

	auto mario = std::make_shared<Mario>("Mario", marioImagePath, 100);
	mario->SetPosition({ GetX0(Block) + Block->GetSize().x * 5, 100 });
	// mario->SetPosition({ GetX0(Block) + Block->GetSize().x * 10, 100 });
	MyFM.addObject(Form_1_2, mario);

	doorarr[0]->SetPosition({ Block->GetSize().x * 167 + GetX0(Block), GetY0(Block) - 9 * Block->GetSize().y });
	doorarr[0]->collisionable = false;
	doorarr[0]->SetVisible(false);
	doorarr[1] = doorarr[0];
	Blocks.push_back(doorarr[0]);

	checkPointArray.push_back(std::make_shared<CheckPoint>("checkpoint"));
	checkPointArray[0]->collisionable = false;
	checkPointArray[0]->SetVisible(false);
	checkPointArray[0]->SetPosition({ 0, 0 });


	for (auto& it : checkPointArray) {
		Blocks.push_back(it);
	}

	for (int i = 0; i < 2; ++i) {
		coins.push_back(std::make_shared<Coin>("coin", Coin::imgs[1], 10));
		coins.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (12 + i), GetY0(Block) - Block->GetSize().x * 11 });
		coins.push_back(std::make_shared<Coin>("coin", Coin::imgs[1], 10));
		coins.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (12 + i), GetY0(Block) - Block->GetSize().x * 10 });
	}
	for (auto& it : coins) {
		//std::cout << &it->imgs << '\n';
		Blocks.push_back(it);
	}

	for (int i = 0; i < 193; i++) {
		if (i > 80 && i < 84 || i > 120 && i < 123 || i > 124 && i < 127 || i > 138 && i < 146 || i > 153 && i < 161) {
			continue;
		}
		Blocks.push_back(std::make_shared<Brick>("Floor", FloorDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + i * Block->GetSize().x, GetY0(Block) - 13 * Block->GetSize().y });
		Blocks.push_back(std::make_shared<Brick>("Floor", FloorDarkImagePath, 10));
		Blocks.back()->SetPosition({ i * Block->GetSize().x + GetX0(Block), GetY0(Block) - 14 * Block->GetSize().y });
	}

	for (int i = 2; i < 13; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block), GetY0(Block) - i * Block->GetSize().y });
	}
	for (int i = 6; i < 139; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * i, GetY0(Block) - 2 * Block->GetSize().y });
	}
	for (int i = 162; i < 169; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * i, GetY0(Block) - 2 * Block->GetSize().y });
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j <= i; ++j) {
			Blocks.push_back(std::make_shared<Brick>("StairsBrick", StairsBrickDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (i * 2 + 17), GetY0(Block) - (12 - j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 4; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (25), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	for (int i = 0; i < 3; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (27), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	for (int i = 0; i < 3; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (31), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	for (int i = 0; i < 2; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (33), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * 29, GetY0(Block) - 8 * Block->GetSize().y });
	for (int j = 0; j <= 2; j += 2) {
		for (int i = 0; i < 3; ++i) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (39 + j), GetY0(Block) - (7 + i) * Block->GetSize().y });
		}
	}
	for (int j = 0; j <= 2; j += 2) {
		for (int i = 0; i < 3; ++i) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (44 + j), GetY0(Block) - (7 + i) * Block->GetSize().y });
		}
	}
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (40), GetY0(Block) - (9) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (45), GetY0(Block) - (9) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (42), GetY0(Block) - (7) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (43), GetY0(Block) - (7) * Block->GetSize().y });
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (54 + i), GetY0(Block) - (3 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (54 + i), GetY0(Block) - (9 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 6; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (52 + i), GetY0(Block) - (5 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (i < 4 && j >= 2 && j < 6) {
				continue;
			}
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (58 + i), GetY0(Block) - (3 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (66 + i), GetY0(Block) - (3 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 5; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (67), GetY0(Block) - (5 + i) * Block->GetSize().y });
	}
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (68), GetY0(Block) - (9) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (69), GetY0(Block) - (9) * Block->GetSize().y });
	Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (69), GetY0(Block) - (8) * Block->GetSize().y });
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 5; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (72 + i), GetY0(Block) - (5 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (76 + i), GetY0(Block) - (3 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 5; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (76 + i), GetY0(Block) - (9) * Block->GetSize().y });
	}
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (85 + i), GetY0(Block) - (7 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (123 + i), GetY0(Block) - (10 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 6; ++i) {
		Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (146 + i), GetY0(Block) - (8) * Block->GetSize().y });
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j <= i; ++j) {
			Blocks.push_back(std::make_shared<Brick>("StairsBrick", StairsBrickDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (134 + i), GetY0(Block) - (12 - j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 4; ++i) {
		Blocks.push_back(std::make_shared<Brick>("StairsBrick", StairsBrickDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (138), GetY0(Block) - (12 - i) * Block->GetSize().y });
	}
	for (int i = 0; i < 17; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (161 + i), GetY0(Block) - (10 + j) * Block->GetSize().y });
		}
	}
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 8; ++j) {
			Blocks.push_back(std::make_shared<Brick>("BlockBrick", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (171 + i), GetY0(Block) - (2 + j) * Block->GetSize().y });
		}
	}

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			Blocks.push_back(std::make_shared<Brick>("pipe", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (104 + i), GetY0(Block) - (12 - j) * Block->GetSize().y });
			Blocks.back()->SetVisible(false);
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			Blocks.push_back(std::make_shared<Brick>("pipe", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (110 + i), GetY0(Block) - (12 - j) * Block->GetSize().y });
			Blocks.back()->SetVisible(false);
		}
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			Blocks.push_back(std::make_shared<Brick>("pipe", BlockDarkImagePath, 10));
			Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (116 + i), GetY0(Block) - (12 - j) * Block->GetSize().y });
			Blocks.back()->SetVisible(false);
		}
	}
	for (int j = 0; j < 8; ++j) {
		Blocks.push_back(std::make_shared<Brick>("pipe", BlockDarkImagePath, 10));
		Blocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * (170), GetY0(Block) - (12 - j) * Block->GetSize().y });
		Blocks.back()->SetVisible(false);
	}
	Blocks.push_back(std::make_shared<Brick>("pipe", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ Block->GetSize().x * 168 + GetX0(Block), GetY0(Block) - 8 * Block->GetSize().y });
	Blocks.back()->SetVisible(false);
	Blocks.push_back(std::make_shared<Brick>("pipe", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ Block->GetSize().x * 169 + GetX0(Block), GetY0(Block) - 8 * Block->GetSize().y });
	Blocks.back()->SetVisible(false);
	Blocks.push_back(std::make_shared<Brick>("pipe", BlockDarkImagePath, 10));
	Blocks.back()->SetPosition({ Block->GetSize().x * 167 + GetX0(Block), GetY0(Block) - 8 * Block->GetSize().y });
	Blocks.back()->SetVisible(false);

	std::vector<std::shared_ptr<QuestionBlock>> QuestionBlocks;
	for (int i = 10; i < 15; ++i) {
		QuestionBlocks.push_back(std::make_shared<QuestionBlock>("QuestionBlock", StairsBrickImagePath, 10));
		QuestionBlocks.back()->SetPosition({ GetX0(Block) + Block->GetSize().x * i, GetY0(Block) - 9 * Block->GetSize().y });
	}
	for (auto& it : QuestionBlocks) {
		it->setDark();
		Blocks.push_back(it);
	}

	for (auto& it : Blocks) {
		MyFM.addObject(Form_1_2, it);
	}

	mario->userdata = img->userdata = std::make_shared<std::vector<std::shared_ptr<Brick>>>(Blocks);

	/*enemys.push_back(std::make_shared<Goomba>("Goomba", Goomba::imgs[0], 50));
	enemys[0]->SetPosition({ GetX0(enemys[0]) + enemys[0]->GetSize().x, 0 });*/

	for (auto& it : enemys) {
		it->userdata = mario->userdata;
		MyFM.addObject(Form_1_2, it);
	}

	auto text = std::make_shared<TextObject>("HPText", MyFontPath, 20, "HP:3", Util::Color::FromName(Util::Colors::WHITE), 100);
	text->SetPosition({ -GetX0(text), GetY0(text) });
	MyFM.addObject(Form_1_2, text);

	auto pointtext = std::make_shared<TextObject>("PointText", MyFontPath, 20, "Point:0", Util::Color::FromName(Util::Colors::WHITE), 100);
	pointtext->SetPosition({ 0, GetY0(pointtext) });
	MyFM.addObject(Form_1_2, pointtext);

	auto texttime = std::make_shared<TextObject>("Timetext", MyFontPath, 20, "300", Util::Color::FromName(Util::Colors::WHITE), 100);
	texttime->SetPosition({ GetX0(texttime), GetY0(texttime) });
	MyFM.addObject(Form_1_2, texttime);

	auto eventobj = std::make_shared<EventObject>("freeForm_1_1", freeForm);
	eventobj->userdata = std::make_shared<std::string>(Form_1_1);
	MyFM.addObject(Form_1_2, eventobj);

	eventobj = std::make_shared<EventObject>("moveEvent", moveEvent);
	eventobj->userdata = std::make_shared<std::tuple<std::vector<std::shared_ptr<Character>>, std::vector<std::shared_ptr<Brick>>>>(enemys, pipes);
	MyFM.addObject(Form_1_2, eventobj);

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int, std::shared_ptr<TextObject>>>(0, 300, texttime);
	MyFM.addObject(Form_1_2, eventobj);

	eventobj = std::make_shared<EventObject>("CheckDoor", CheckDoors);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(Form_1_2, eventobj);

	eventobj = std::make_shared<EventObject>("CheckEneyCollision", CheckEneyCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Character>>>(enemys);
	MyFM.addObject(Form_1_2, eventobj);

	/*eventobj = std::make_shared<EventObject>("CheckFlagpoleCollision", CheckFlagpoleCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Brick>>>(flagpole);
	MyFM.addObject(Form_1_2, eventobj);*/

	eventobj = std::make_shared<EventObject>("CheckCoinsCollision", CheckCoinsCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Coin>>>(coins);
	MyFM.addObject(Form_1_2, eventobj);

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor, false);
	eventobj->userdata = std::make_shared<std::array<std::shared_ptr<Brick>, 2>>(doorarr);
	MyFM.addObject(Form_1_2, eventobj);

	eventobj = std::make_shared<EventObject>("CheckPointCollision", CheckPointCollision, true);
	auto& ptr = eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<CheckPoint>>>(checkPointArray);
	MyFM.addObject(Form_1_2, eventobj);

	MyFM.addObject(Form_1_2, std::make_shared<EventObject>("CheckMArioPosition", CheckMArioPosition));

	/*eventobj = std::make_shared<EventObject>("CheckTortoiseShellCollision", CheckTortoiseShellCollision);
	eventobj->userdata = std::make_shared<std::vector<std::shared_ptr<Turtle>>>(turtles);
	MyFM.addObject(Form_1_2, eventobj);*/

	MyFM.addObject(Form_1_2, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, false));
	MyFM.addObject(Form_1_2, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(Form_1_2, eventobj);

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = ptr;
	MyFM.addObject(Form_1_2, eventobj);

	MyFM.addObject(Form_1_2, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(Form_1_2, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
}


#endif // !INITFORMFUNC_HPP
