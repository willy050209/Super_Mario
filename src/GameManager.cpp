#include "GameManager.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "ButtonCallBackFunc.hpp"
#include "incallobj.hpp"

#include <memory>

inline static int GetX0(std::shared_ptr<Object> obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

inline static int GetY0(std::shared_ptr<Object> obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

inline static void initFormBackground(GameManager& self) noexcept {

	auto& MyFM = self.GetFormManger();

	/*add images to FormBackground*/
	auto tmpImage = std::make_shared<ImageObject>("cat0", BackgroundImagePath, -10);
	tmpImage->SetPosition({ GetX0(tmpImage), GetY0(tmpImage) - (WINDOW_HEIGHT - tmpImage->GetSize().y) });
	MyFM.addObject(FormBackground, tmpImage);

	//auto tmptest = std::make_shared<ImageObject>("mario_walk", "C:/Users/paula/Downloads/Mario_run.gif", 20);
	////tmptest->SetPosition();
	//MyFM.addObject(FormBackground, tmptest);

	tmpImage = (std::make_shared<ImageObject>("phase0", MY_RESOURCE_DIR"/Image/Background/phase0.png", -10));
	tmpImage->SetPosition({ GetX0(tmpImage),GetY0(tmpImage) - (WINDOW_HEIGHT - tmpImage->GetSize().y) });
	MyFM.addObject(FormBackground, tmpImage);

	tmpImage = (std::make_shared<ImageObject>("cat1", BackgroundImagePath, -10));
	MyFM.addObject(FormBackground, tmpImage);

	/*add characters to FormBackground*/
	auto mario = (std::make_shared<Mario>("Mario", marioImagePath, 10));
	mario->SetPosition({ 0,300 });
	MyFM.addObject(FormBackground, mario);

	/*add Texts to FormBackground*/
	auto text(std::make_shared<TextObject>("Text0", ArialFontPath, 20, "Text Output Example(Font = Arial)", Util::Color::FromName(Util::Colors::YELLOW), 10));
	text->SetPosition({ -400,300 });
	text->SetPosition({ GetX0(text),GetY0(text) });
	MyFM.addObject(FormBackground, text);

	MyFM.addObject(FormBackground, std::make_shared<TextObject>("HelloWorld", ArialFontPath, 50, "Hello world!!", Util::Color::FromRGB(255, 255, 255), 10));


	/*add buttons to FormBackground*/
	for (int i = 0; i < 10; ++i) {
		auto buttonptr = std::make_shared<Button>("button" + std::to_string(i), ArialFontPath, 20, "This is a button" + std::to_string(i), Util::Color::FromName(Util::Colors::YELLOW_GREEN), 20);
		buttonptr->SetPosition({ GetX0(buttonptr) + 100,GetY0(buttonptr) - 50 * (i + 1) });
		buttonptr->SetCallBackFunc(callBackTest);
		MyFM.addObject(FormBackground, buttonptr);
	}
}

void GameManager::init() noexcept
{

	bgm = std::make_shared<Util::BGM>(BGMPath);
	bgm->SetVolume(0);// 0~128
	bgm->Play();
	
	initFormBackground(*this);

	/*add FormOptions Object*/
	auto tmpbutton = std::make_shared<Button>("ExitButton", ArialFontPath, 50, "Exit", Util::Color::FromName(Util::Colors::SLATE_BLUE), 100);
	tmpbutton->SetPosition({
		0,
		GetY0(tmpbutton) - (WINDOW_HEIGHT - tmpbutton->GetSize().y) + 50
	});
	tmpbutton->SetCallBackFunc(exitCallBack);
	MyFM.addObject(FormOptions, tmpbutton);
	
	tmpbutton = std::make_shared<Button>("OptionsButton", ArialFontPath, 50, "Options", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0,tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(CallSettingForm);
	MyFM.addObject(FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("HelpButton", ArialFontPath, 50, "Help", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0,-(tmpbutton->GetSize().y * 2) });
	tmpbutton->SetCallBackFunc(callBackTest);
	MyFM.addObject(FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("BackButton", ArialFontPath, 50, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton),GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(FormOptions, tmpbutton);
	MyFM.addObject(FormSetting, tmpbutton);

	auto text = std::make_shared<TextObject>("VolumeValueText", ArialFontPath, 100, std::to_string(bgm->GetVolume()), Util::Color::FromName(Util::Colors::WHITE), 10);
	MyFM.addObject(FormSetting, text);
	tmpbutton = std::make_shared<Button>("Volume-Button", ArialFontPath, 100, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ 0,-(text->GetSize().y *2) });
	tmpbutton->SetCallBackFunc(VolumeDownClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);
	tmpbutton = std::make_shared<Button>("Volume+Button", ArialFontPath, 100, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ 0,text->GetSize().y *2 });
	tmpbutton->SetCallBackFunc(VolumeUpClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);
	text = std::make_shared<TextObject>("VolumeText", ArialFontPath, 100, "Volume", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ 0,(tmpbutton->GetSize().y *2) + tmpbutton->GetSize().y });
	MyFM.addObject(FormSetting, text);


	MyFM.changeForm(FormBackground);
}

void GameManager::Update(std::shared_ptr<Core::Context>& context) noexcept
{
	if (Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
		if (MyFM.GetPrevForm() == "") {
			End();
		}
		else if (MyFM.GetNowForm() == FormBackground) {
			MyFM.changeForm(FormOptions);
		}
		else
		{
			MyFM.returnPrevForm();
		}
		
	}
	MyFM.UpdateForm(this);
	
}

void GameManager::End() noexcept
{
	endstate = true;
}
