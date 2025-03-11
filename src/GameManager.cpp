#include "GameManager.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "ButtonCallBackFunc.hpp"
#include "EventCallBackFunc.hpp"
#include "incallobj.hpp"
#include "Position.hpp"

#include <memory>
#include <tuple>
#include <thread>


#define INITFORM_FUNC(func_name) static void func_name(GameManager* self)

INITFORM_FUNC(initFormBackground) noexcept {

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

	auto tmptest = std::make_shared<ImageObject>("mario_walk", MY_RESOURCE_DIR"\\super mario\\Mario\\frame0.png", 100);
	tmptest->SetPosition({100,100});
	MyFM.addObject(FormBackground, tmptest);

	tmpImage = (std::make_shared<ImageObject>("cat1", BackgroundImagePath, -10));
	MyFM.addObject(FormBackground, tmpImage);

	tmpImage = (std::make_shared<ImageObject>("phase0", MY_RESOURCE_DIR"/super mario/Maps/SuperMarioBrosMap1-1BG.png", 1));
	tmpImage->SetPosition({ GetX0(tmpImage),0 });
	MyFM.addObject(FormBackground, tmpImage);

	/*add characters to FormBackground*/
	auto mario = (std::make_shared<Mario>("Mario", marioImagePath, 10));
	mario->SetPosition({ 0,300 });
	mario->userdata = std::static_pointer_cast<void>(tmpImage);
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
		buttonptr->userdata = std::make_shared<int>(0);
		buttonptr->SetCallBackFunc(callBackTest);
		MyFM.addObject(FormBackground, buttonptr);
	}

	initenent.join();

}

/*init Titel Form*/
INITFORM_FUNC(initFormTitle) noexcept {

	constexpr auto textSize = 50;
	auto&& textColor = Util::Color::FromName(Util::Colors::YELLOW);

	auto& MyFM = self->GetFormManger();

	auto button = std::make_shared<Button>("Start", MyFontPath, textSize, "Start", textColor, 10);
	button->SetPosition({ 0,2 * button->GetSize().y });
	button->SetCallBackFunc(StartButtonEvent);

	MyFM.addObject(FormTitel, button);
	button = std::make_shared<Button>("Options", MyFontPath, textSize, "Options", textColor, 10);
	button->SetCallBackFunc(CallOptionForm);
	MyFM.addObject(FormTitel, button);

	button = std::make_shared<Button>("ExitButton", MyFontPath, textSize, "Exit", textColor, 10);
	button->SetPosition({ 0,-(2 * button->GetSize().y) });
	button->SetCallBackFunc(exitCallBack);
	MyFM.addObject(FormTitel, button);

	auto image = std::make_shared<ImageObject>("QRcode", MY_RESOURCE_DIR"/Image/Background/qrcode.png", -10);
	MyFM.addObject("help", image);
	MyFM.changeForm(FormTitel);

}

/*init Options Form*/
INITFORM_FUNC(initFormOptions){
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("ExitButton", MyFontPath, 50, "Exit", Util::Color::FromName(Util::Colors::SLATE_BLUE), 100);
	tmpbutton->SetPosition({
		0,
		GetY0(tmpbutton) - (WINDOW_HEIGHT - tmpbutton->GetSize().y) + 50
		});
	tmpbutton->SetCallBackFunc(exitCallBack);
	MyFM.addObject(FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("SettingButton", MyFontPath, 50, "Setting", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0,tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(CallSettingForm);
	MyFM.addObject(FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("HelpButton", MyFontPath, 50, "Help", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ 0,0 });
	tmpbutton->SetCallBackFunc(HelpButtonEvent);
	tmpbutton->userdata = std::make_shared<std::string>("start https://ntut-open-source-club.github.io/practical-tools-for-simple-design/");
	MyFM.addObject(FormOptions, tmpbutton);

	tmpbutton = std::make_shared<Button>("BackButton", MyFontPath, 50, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton),GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(FormOptions, tmpbutton);
}

/*init 1-1*/
INITFORM_FUNC(initForm_1_1){
	auto& MyFM = self->GetFormManger();

	auto img = std::make_shared<ImageObject>("Background", Background_1_1_ImagePath, 1);
	img->SetPosition({ -GetX0(img),0 });
	MyFM.addObject(Form_1_1, img);

	auto mario = std::make_shared<Mario>("Mario", marioImagePath, 10);
	MyFM.addObject(Form_1_1, mario);

	auto event = std::make_shared<EventObject>("moveEvent", moveEvent);
	event->userdata = std::make_shared<std::tuple<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>>>(img, mario);
	MyFM.addObject(Form_1_1, event);
}

INITFORM_FUNC(initFormSetting) {
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("BackButton", MyFontPath, 50, "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetX0(tmpbutton),GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(FormSetting, tmpbutton);

	auto text = std::make_shared<TextObject>("VolumeValueText", MyFontPath, 30, std::to_string(self->GetBGM()->GetVolume()), Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ 2 * text->GetSize().x ,0 });
	MyFM.addObject(FormSetting, text);

	tmpbutton = std::make_shared<Button>("Volume-Button", MyFontPath, 30, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x,(tmpbutton->GetSize().y * -2) });
	tmpbutton->SetCallBackFunc(VolumeDownClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);

	tmpbutton = std::make_shared<Button>("Volume+Button", MyFontPath, 30, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x,text->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(VolumeUpClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);

	text = std::make_shared<TextObject>("VolumeText", MyFontPath, 30, "Volume", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ tmpbutton->GetPosition().x,(text->GetSize().y * 2) + text->GetSize().y });
	MyFM.addObject(FormSetting, text);


	text = std::make_shared<TextObject>("ScreenSizeText", MyFontPath, 30, std::to_string(WINDOW_WIDTH) + "\n" + std::to_string(WINDOW_HEIGHT), Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ -2 * text->GetSize().x ,0 });
	MyFM.addObject(FormSetting, text);

	tmpbutton = std::make_shared<Button>("ScreenSize-Button", MyFontPath, 30, "-", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x,-(tmpbutton->GetSize().y * 2) });
	tmpbutton->SetCallBackFunc(ScreenSizeDownClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);

	tmpbutton = std::make_shared<Button>("ScreenSize+Button", MyFontPath, 30, "+", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ text->GetPosition().x,tmpbutton->GetSize().y * 2 });
	tmpbutton->SetCallBackFunc(ScreenSizeUpClickedEvent);
	MyFM.addObject(FormSetting, tmpbutton);

	text = std::make_shared<TextObject>("ScreenSizeText", MyFontPath, 30, "ScreenSize", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ tmpbutton->GetPosition().x,(text->GetSize().y * 2) + text->GetSize().y });
	MyFM.addObject(FormSetting, text);

	text = std::make_shared<TextObject>("", ArialFontPath, 30, "Restart to apply screen settings", Util::Color::FromName(Util::Colors::WHITE), 10);
	text->SetPosition({ GetX0(text),-GetY0(text) });
	MyFM.addObject(FormSetting, text);

	tmpbutton = std::make_shared<Button>("RestartButton", MyFontPath, 30, "Restart", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ -GetX0(tmpbutton) ,-GetY0(tmpbutton) });
	tmpbutton->SetCallBackFunc(RestaetButtonEvent);
	MyFM.addObject(FormSetting, tmpbutton);
}


void GameManager::init() noexcept
{

	bgm = std::make_shared<Util::BGM>(BGMPath);
	bgm->SetVolume(0);// 0~128
	bgm->Play();
	
	initFormBackground(this);
	
	initFormTitle(this);

	initForm_1_1(this);

	initFormOptions(this);

	initFormSetting(this);

	MyFM.changeForm(FormTitel);

}

void GameManager::Update(std::shared_ptr<Core::Context>& context) noexcept
{
	if (Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
		if (MyFM.GetPrevForm() != "null") {
			MyFM.returnPrevForm();
		}
		/*else if (MyFM.GetNowForm() == FormTitel) {
			MyFM.changeForm(FormOptions);
		}*/
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
