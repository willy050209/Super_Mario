#include "GameManager.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "ButtonCallBackFunc.hpp"
#include "incallobj.hpp"

#include <memory>

constexpr auto BGMPath = MY_RESOURCE_DIR"/BGM/Ring08.wav";
constexpr auto ArialFontPath = MY_RESOURCE_DIR"/Font/arial.ttf";
constexpr auto BackgroundImagePath = MY_RESOURCE_DIR"/Image/Background/cat.jpg";
constexpr auto marioImagePath = MY_RESOURCE_DIR"/Image/Character/bee_1.png";
constexpr auto FormBackground = "Background";
constexpr auto FormOptions = "Options";

inline static float GetX0(std::shared_ptr<Object> obj) noexcept {
	return -(WINDOW_WIDTH / 2 - obj->GetSize().x / 2);
}

inline static float GetY0(std::shared_ptr<Object> obj) noexcept {
	return (WINDOW_HEIGHT / 2 - obj->GetSize().y / 2);
}

void GameManager::init() noexcept
{

	bgm = std::make_shared<Util::BGM>(BGMPath);
	bgm->SetVolume(0);// 0~128
	bgm->Play();
	
	/*add images*/
	auto tmpImage = std::make_shared<ImageObject>("cat0", BackgroundImagePath, 10);
	tmpImage->SetPosition({ GetX0(tmpImage), GetY0(tmpImage) - (WINDOW_HEIGHT - tmpImage->GetSize().y) });
	MyFM.addObject(FormBackground, tmpImage);

	tmpImage = (std::make_shared<ImageObject>("phase0", MY_RESOURCE_DIR"/Image/Background/phase0.png", -10));
	tmpImage->SetPosition({ GetX0(tmpImage),GetY0(tmpImage) - (WINDOW_HEIGHT - tmpImage->GetSize().y) });
	MyFM.addObject(FormBackground, tmpImage);

	tmpImage = (std::make_shared<ImageObject>("cat1", BackgroundImagePath, 10));
	MyFM.addObject(FormBackground, tmpImage);
	

	
	/*add characters*/
	auto mario = (std::make_shared<Mario>("Mario",marioImagePath, 10));
	mario->SetPosition({0,300});
	MyFM.addObject(FormBackground, mario);
	
	/*add Texts*/
	auto text(std::make_shared<TextObject>("Text0",ArialFontPath, 20, "Text Output Example(Font = Arial)", Util::Color::FromName(Util::Colors::YELLOW), 10));
	text->SetPosition({-400,300});
	text->SetPosition({ GetX0(text),GetY0(text) });
	MyFM.addObject(FormBackground, text);

	MyFM.addObject(FormBackground, std::make_shared<TextObject>("HelloWorld", ArialFontPath, 50, "Hello world!!", Util::Color::FromRGB(255, 255, 255), 10));


	/*add buttons*/
	for (int i = 0; i < 10; ++i) {
		auto buttonptr = std::make_shared<Button>("button" + std::to_string(i), ArialFontPath, 20, "This is a button" + std::to_string(i), Util::Color::FromName(Util::Colors::YELLOW_GREEN), 20);
		buttonptr->SetPosition({ GetX0(buttonptr) + 100,GetY0(buttonptr) - 50 * (i + 1) });
		buttonptr->SetCallBackFunc(callBackTest);
		MyFM.addObject(FormBackground, buttonptr);
	}

	auto tmp = std::make_shared<Button>("ExitButton", ArialFontPath, 50, "Exit", Util::Color::FromName(Util::Colors::SLATE_BLUE), 100);
	tmp->SetPosition({
		0,
		GetY0(tmp) - (WINDOW_HEIGHT - tmp->GetSize().y) + 50
	});
	tmp->SetCallBackFunc(exitCallBack);
	MyFM.addObject(FormOptions, tmp);
	
	tmp = std::make_shared<Button>("OptionsButton", ArialFontPath, 50, "Options", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmp->SetPosition({ 0,tmp->GetSize().y * 2 });
	tmp->SetCallBackFunc(callBackTest);
	MyFM.addObject(FormOptions, tmp);

	tmp = std::make_shared<Button>("HelpButton", ArialFontPath, 50, "Help", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmp->SetPosition({ 0,-(tmp->GetSize().y * 2) });
	tmp->SetCallBackFunc(callBackTest);
	MyFM.addObject(FormOptions, tmp);

	tmp = std::make_shared<Button>("BackButton", ArialFontPath, 50, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmp->SetPosition({ GetX0(tmp),GetY0(tmp) });
	tmp->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(FormOptions, tmp);

	MyFM.changeForm(FormBackground);
}

void GameManager::Update(std::shared_ptr<Core::Context>& context) noexcept
{
	if (Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
		if (MyFM.GetNowForm() == FormOptions) {
			MyFM.changeForm(MyFM.GetPrevForm());
		}
		else
		{
			MyFM.changeForm(FormOptions);
		}
		
	}
	MyFM.UpdateForm(this);
	
}

void GameManager::End() noexcept
{
	endstate = true;
}
