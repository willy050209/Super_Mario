#pragma once
#ifndef INITFORM_FUNC
#define INITFORM_FUNC(func_name) static inline void func_name(MyAPP::GameManager* self) noexcept
#endif // !INITFORM_FUNC

INITFORM_FUNC(initForm_1_2);
INITFORM_FUNC(initForm_1_1_Pip);
INITFORM_FUNC(initForm_1_1_to_1_2);
INITFORM_FUNC(initForm_1_2_Pipe);
INITFORM_FUNC(initForm_1_2_to_1_4);
INITFORM_FUNC(initForm_1_4);
INITFORM_FUNC(winForm);
INITFORM_FUNC(diedForm);

INITFORM_FUNC(initForm1);


#ifndef INITFORMFUNC_HPP
#define INITFORMFUNC_HPP

#include "ButtonCallBackFunc.hpp"
#include "EventCallBackFunc.hpp"
#include "incallobj.hpp"
#include "Position.hpp"
#include "config.hpp"
#include "ProgressBar.hpp"
#include "userType.hpp"
#include "GameManager.hpp"

#include <algorithm>
#include <execution>
#include <memory>
#include <tuple>
#include <fstream>

//namespace MyAPP {
//	class GameManager;
//}

using namespace MyAPP::Form::Object;

namespace MyAPP::Form {

	/// <summary>
	/// �N���g�J��r��
	/// </summary>
	/// <param name="FM"></param>
	/// <param name="formName"></param>
	inline void writeForm(MyAPP::Form::FormManger& FM,const std::string& formName) {
		auto& Block = PositionReference::GetPositionReference();
		auto size = Block->GetSize();
		auto x0 = GetLeftEdge(Block);
		auto y0 = GetTopEdge(Block);
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
	/// ���o bricks �� Type == ObjectType::CheckPoint ���Ҧ�����
	/// </summary>
	/// <param name="bricks"></param>
	/// <returns></returns>
	inline auto GetCheckPoints(std::shared_ptr<BrickPtrVec>& bricks) noexcept {
		auto result = std::make_shared<CheckPointPtrVec>();
		std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
			if (it->MyType == ObjectType::CheckPoint) {
				result->push_back(std::static_pointer_cast<CheckPoint>(it));
			}
		});
		return result;
	}

	/// <summary>
	/// ���o bricks �� Type == ObjectType::PipeBrick ���Ҧ�����
	/// </summary>
	/// <param name="bricks"></param>
	/// <returns></returns>
	inline auto GetPipeBricks(std::shared_ptr<BrickPtrVec>& bricks) noexcept {
		auto result = MakeObject::make_Bricks();
		std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
			if (it->MyType == ObjectType::PipeBrick) {
				result->push_back(std::static_pointer_cast<PipeBrick>(it));
			}
		});
		return result;
	}

	/// <summary>
	/// ���o bricks �� Type == ObjectType::Flagpole ���Ҧ�����
	/// </summary>
	/// <param name="bricks"></param>
	/// <returns></returns>
	inline auto GetFlagpoles(std::shared_ptr<BrickPtrVec>& bricks) noexcept {
		auto result = MakeObject::make_Bricks();
		std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
			if (it->MyType == ObjectType::Flagpole) {
				result->push_back(std::static_pointer_cast<Flagpole>(it));
			}
		});
		return result;
	}

	/// <summary>
	/// ���o bricks �� Type == ObjectType::Door ���Ҧ�����
	/// </summary>
	/// <param name="bricks"></param>
	/// <returns></returns>
	inline auto Getdoors(std::shared_ptr<BrickPtrVec>& bricks) noexcept {
		auto result = MakeObject::make_Bricks();
		std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
			if (it->MyType == ObjectType::Door) {
				result->push_back(std::static_pointer_cast<Door>(it));
			}
		});
		return result;
	}

	inline auto GetQuestionBlocks(std::shared_ptr<BrickPtrVec>& bricks) noexcept {
		auto result = MakeObject::make_Bricks();
		std::for_each(bricks->begin(), bricks->end(), [&](auto& it) {
			if (it->MyType == ObjectType::QuestionBlock) {
				result->push_back(std::static_pointer_cast<QuestionBlock>(it));
			}
		});
		return result;
	}

	/// <summary>
	/// ���o enemys �� Type == ObjectType::Turtle ���Ҧ�����
	/// </summary>
	/// <param name="bricks"></param>
	/// <returns></returns>
	inline auto GetTurtless(std::shared_ptr<CharacterPtrVec>& enemys) noexcept {
		auto result = MakeObject::make_Characters();
		std::for_each(enemys->begin(), enemys->end(), [&](auto& it) {
			if (it->MyType == ObjectType::Turtle) {
				result->push_back(std::static_pointer_cast<Turtle>(it));
			}
		});
		return result;
	}

	/// <summary>
	/// �N����}�C��J���
	/// </summary>
	/// <typeparam name="T">����}�C���@�P����</typeparam>
	/// <param name="FM"></param>
	/// <param name="formname"></param>
	/// <param name="objlist"></param>
	template <class T>
	inline void AddToFormManager(MyAPP::Form::FormManger& FM, const std::string& formname, std::shared_ptr<std::vector<std::shared_ptr<T>>>& objlist) noexcept {
		std::for_each(objlist->begin(), objlist->end(), [&](auto& it) { FM.addObject(formname, it); });
	}

	/// <summary>
	/// �N����}�C��J���
	/// </summary>
	/// <typeparam name="T">����}�C���@�P����</typeparam>
	/// <param name="FM"></param>
	/// <param name="formname"></param>
	/// <param name="objlist"></param>
	template <class T>
	inline void AddToFormManager(MyAPP::Form::FormManger& FM, const std::string& formname, std::vector<std::shared_ptr<T>>& objlist) noexcept {
		std::for_each(objlist.begin(), objlist.end(), [&](auto& it) { FM.addObject(formname, it); });
	}
}

using namespace MyAPP::Form;

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
	const auto textSize = 50 * ((float)WINDOW_HEIGHT / 480);
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("ExitButton", MyAPP::MyResourcesFilePath::MyFontPath, textSize, "Exit", Util::Color::FromName(Util::Colors::SLATE_BLUE), 100);
	tmpbutton->SetPosition({ 0,
		GetTopEdge(tmpbutton) - (WINDOW_HEIGHT - tmpbutton->GetSize().y) + textSize });
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
	tmpbutton->SetPosition({ GetLeftEdge(tmpbutton), GetTopEdge(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(MyAPP::Form::FormNames::FormOptions, tmpbutton);
}

INITFORM_FUNC(initFormSetting) {
	const auto textSize = 30 * ((float)WINDOW_HEIGHT / 480);
	auto& MyFM = self->GetFormManger();
	auto tmpbutton = std::make_shared<Button>("BackButton", MyAPP::MyResourcesFilePath::MyFontPath, 40 * ((float)WINDOW_HEIGHT / 480), "Back", Util::Color::FromName(Util::Colors::SLATE_BLUE), 10);
	tmpbutton->SetPosition({ GetLeftEdge(tmpbutton), GetTopEdge(tmpbutton) });
	tmpbutton->SetCallBackFunc(Back_Button_func);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);

	auto text = std::make_shared<TextObject>("VolumeValueText", MyAPP::MyResourcesFilePath::MyFontPath, textSize, std::to_string(self->bgm->GetVolume()), Util::Color::FromName(Util::Colors::WHITE), 10);
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
	text->SetPosition({ GetLeftEdge(text), -GetTopEdge(text) });
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, text);

	tmpbutton = std::make_shared<Button>("RestartButton", MyAPP::MyResourcesFilePath::MyFontPath, 20 * ((float)WINDOW_HEIGHT / 480), "Restart", Util::Color::FromName(Util::Colors::WHITE), 10);
	tmpbutton->SetPosition({ -GetLeftEdge(tmpbutton), -GetTopEdge(tmpbutton) });
	tmpbutton->SetCallBackFunc(RestaetButtonEvent);
	MyFM.addObject(MyAPP::Form::FormNames::FormSetting, tmpbutton);
}

INITFORM_FUNC(winForm) {
	auto& MyFM = self->GetFormManger();
	constexpr auto formName = MyAPP::Form::FormNames::Win_Form;


	if (auto Capoo_smile = std::make_shared<ImageObject>("Capoo_smile", MyAPP::MyResourcesFilePath::Kapoo::getCapoo_smileFrames().front(), 5)) {
		//Capoo_smile->SetPosition({ GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 182, GetTopEdge(Capoo_smile) - PositionReference->GetSize().x * 2 });
		MyFM.addObject(formName, Capoo_smile);
	}
	if (auto updateframe = std::make_shared<EventObject>("Update_Capoo_Giphy_Frame", [](EventObject* const self, void* data) {
			static size_t index = 0;
			auto fpscount = std::static_pointer_cast<size_t>(self->userdata);
			if (((*fpscount)++) >= 1) {
				index = (index + 1) % MyAPP::MyResourcesFilePath::Kapoo::getCapoo_smileFrames().size();
				auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
				if (auto img = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "Capoo_smile")) {
					std::static_pointer_cast<Util::Image>(img->GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::Kapoo::getCapoo_smileFrames().at(index));
					if (index == 0) {
						auto testEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "test");
						testEvent->Enable = true;
						img->SetVisible(false);
						self->Enable = false;
						FM.GetFormObject<ImageObject>(FM.GetNowForm(), "background")->SetVisible(true);
					}
				}
				(*fpscount) = 0;
			}
		})) {
		updateframe->userdata = std::make_shared<size_t>(0);
		MyFM.addObject(formName, std::move(updateframe));
	}
	{
		using MyAPP::Form::Object::ImageObject;
		using MyAPP::MyResourcesFilePath;
		auto background = std::make_shared<ImageObject>("background", MyResourcesFilePath::endImagePath, 10);
		background->SetPosition({ GetLeftEdge(background), GetTopEdge(background) });
		background->SetVisible(false);
		MyFM.addObject(formName, std::move(background));
	}
	{
		using MyAPP::Form::Object::EventObject;
		using MyAPP::Form::Object::ImageObject;
		using MyAPP::GameManager;
		auto eventobj = std::make_shared<EventObject>("test", [](EventObject* const self, void* data) {
			auto& FM = static_cast<GameManager*>(data)->GetFormManger();
			auto background = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "background");
			if (background->GetPosition().y < -GetTopEdge(background)) {
				background->m_Transform.translation.y++;
			}
		},false);
		MyFM.addObject(formName, std::move(eventobj));
	}

	//MyFM.addObject("Win", std::make_shared<TextObject>("", MyAPP::MyResourcesFilePath::MyFontPath, 20 * ((float)WINDOW_HEIGHT / 480), "Win", Util::Color::FromName(Util::Colors::WHITE), 10));
}

/*init 1-1*/
INITFORM_FUNC(initForm_1_1) {
	using namespace MyAPP::Form::Object;
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_1;
	// �@���y�аѦ�
	auto& Block = PositionReference::GetPositionReference();
	
	// �q�a���ɨ��o�Ҧ����
	auto Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Images);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	auto leftedge = std::make_shared<LeftEdge>("LeftEdge");
	Blocks->push_back(leftedge);
	AddToFormManager(MyFM, formName, Blocks);

	// ���o�a�ϻP���O��
	{
		auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::MAP::Background_1_1_ImagePath, Blocks);
		MyFM.addObject(formName, std::move(BMptr.first));
		MyFM.addObject(formName, std::move(BMptr.second));
	}
	
	// ���o�ɶ��B���ơB�ͩR��r���
	auto texts = MakeObject::make_GameText();
	AddToFormManager(MyFM, formName, texts);
	auto cointext = std::find_if(texts->begin(), texts->end(), [](auto& it) {
		return it->name == "CoinnumText";
	});
	
	// ���o�Ҧ��ĤH
	auto enemys = MakeObject::make_Enemys_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Characters, Blocks);
	
	/*{
		auto aaa = std::make_shared<PiranaPlant>("PiranaPlant", 100);
		aaa->setResetPosition({ 0, 0 });
		aaa->SetPos({ 0, 0 });
		enemys->push_back(std::move(aaa));
	}*/
	AddToFormManager(MyFM, formName, enemys);

	auto props = MakeObject::make_Props();

	auto flagformpole = std::make_shared<FlagFromPole>("FlagFromPole", 100);
	flagformpole->SetPosition({ GetLeftEdge(Block) + Block->GetSize().x * 197.5f, GetTopEdge(Block) - Block->GetSize().y * 2 });
	MyFM.addObject(formName, (flagformpole));


	auto objs = MakeObject::make_Objs();
	objs->push_back(std::move(flagformpole));

	auto coinimg = std::make_shared<ImageObject>("coinimg", *Coin::GetFrames(), 10);
	coinimg->SetPosition((*cointext)->GetPosition() - glm::vec2{ coinimg->GetSize().x + (*cointext)->GetSize().x/2, 0 });
	MyFM.addObject(formName, std::move(coinimg));


	self->sfx = std::make_shared<Util::SFX>(MyAPP::MyResourcesFilePath::Game_Over);
	self->bgm = std::make_shared<Util::BGM>(MyAPP::MyResourcesFilePath::Ground_Theme);
	auto& sfx = self->sfx;
	auto& bgm = self->bgm;
	//bgm->Play(-1);

	// �]�w���ƥ�
	auto eventobj = std::make_shared<EventObject>("freeForm_1_1_pipe", freeForm, false);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1_Pipe);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("MoveEvent", moveEvent);
	eventobj->userdata = std::make_shared<GameObjectTuple>(enemys, pipes, props, objs);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateFrameCount",UpdateFrameCount));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateCoinCountText", UpdateCoinCountText, true));
	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int>>(0, 300);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateleftedgePosEvent", [](EventObject* const self, void* data) {
		auto leftedge = std::static_pointer_cast<LeftEdge>(self->userdata);
		leftedge->m_Transform.translation = { GetLeftEdge(leftedge), 0 };
		});
	eventobj->userdata = std::move(leftedge);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckFlagpoleCollision", CheckFlagpoleCollision);
	eventobj->userdata =(flagpole);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FlagpoleAddPoint", FlagpoleAddPoint, false));

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor, false);
	eventobj->userdata = Getdoors(Blocks);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	//eventobj = std::make_shared<EventObject>("CheckTortoiseShellCollision", CheckTortoiseShellCollision);
	//eventobj->userdata = GetTurtless(enemys);
	//MyFM.addObject(formName, std::move(eventobj));

	//MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, true));
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
/// ��l��1-1����
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_1_Pip) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_1_Pipe;
	// ���o�y�аѦ�
	auto& PositionReference = PositionReference::GetPositionReference();

	// �إߦa�Ϥ��
	auto Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Pipe_Images, BrickColor::dark);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	AddToFormManager(MyFM, formName, Blocks);

	// �إߦa�ϻP���O��
	{
		auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::MAP::Background_1_1_Pipe_ImagePath, Blocks, { GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 3, 100 });
		MyFM.addObject(formName, std::move(BMptr.first));
		auto mario = std::move(BMptr.second);
		mario->changeType(self->mariotype);
		MyFM.addObject(formName, std::move(mario));
	}

	// ���o�ɶ��B���ơB�ͩR��r���
	auto texts = MakeObject::make_GameText();
	AddToFormManager(MyFM, formName, texts);
	auto cointext = std::find_if(texts->begin(), texts->end(), [](auto& it) {
		return it->name == "CoinnumText";
	});

	if (auto pipeimg = std::make_shared<ImageObject>("pipeimg", MyAPP::MyResourcesFilePath::PipeDarkImagePath, 100)) {
		MakeObject::Fileinfo finfo;
		finfo.XY = { 14, -11.5 };
		finfo.ChangeXY();
		pipeimg->SetPosition(finfo.XY);
		MyFM.addObject(formName, pipeimg);
	}

	// �إߩҦ��ĤH
	auto enemys = MakeObject::make_Enemys_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_Pipe_Characters, Blocks);
	AddToFormManager(MyFM, formName, enemys);

	auto objs = MakeObject::make_Objs();
	auto coinimg = std::make_shared<ImageObject>("coinimg", *Coin::GetFrames(), 10);
	coinimg->SetPosition((*cointext)->GetPosition() - glm::vec2{ coinimg->GetSize().x + (*cointext)->GetSize().x / 2, 0 });
	MyFM.addObject(formName, std::move(coinimg));

	auto eventobj = std::make_shared<EventObject>("MoveEvent", moveEvent);
	eventobj->userdata = std::make_shared<GameObjectTuple>(enemys, pipes, MakeObject::make_Props(),objs);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = MyFM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "UpdateTimeTextEvent")->userdata;
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	//MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateCoinCountText", UpdateCoinCountText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateFrameCount", UpdateFrameCount));

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = checkPointArray;
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));

	//writeForm(MyFM, MyAPP::Form::FormNames::Form_1_1_Pipe);
}

/// <summary>
/// ��l��1-1��1-2�L��
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_1_to_1_2) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_1_to_1_2;
	auto& PositionReference = PositionReference::GetPositionReference();

	auto Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_1_to_1_2_Images, BrickColor::normal);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	AddToFormManager(MyFM, formName, Blocks);
	
	{
		auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::MAP::Background_1_1_to_1_2_ImagePath, Blocks, { GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 2, GetTopEdge(PositionReference) - PositionReference->GetSize().x * 12 });
		MyFM.addObject(formName, std::move(BMptr.first));
		auto mario = std::move(BMptr.second);
		mario->changeType(self->mariotype);
		MyFM.addObject(formName, std::move(mario));
	}

	if (auto pipeimg = std::make_shared<ImageObject>("pipeimg", MyAPP::MyResourcesFilePath::PipeImagePath, 100)) {
		MakeObject::Fileinfo finfo;
		finfo.XY = { 10, -11.5 };
		finfo.ChangeXY();
		pipeimg->SetPosition(finfo.XY);
		MyFM.addObject(formName, pipeimg);
	}

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
/// ��l��1-2�a��
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_2) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_2;
	auto& PositionReference = PositionReference::GetPositionReference();

	auto Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_2_Images, BrickColor::dark);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	auto leftedge = std::make_shared<LeftEdge>("LeftEdge");
	Blocks->push_back(leftedge);
	AddToFormManager(MyFM, formName, Blocks);

	{
		auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::MAP::Background_1_2_ImagePath, Blocks, { GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 5, 100 });
		MyFM.addObject(formName, std::move(BMptr.first));
		auto mario = std::move(BMptr.second);
		mario->changeType(self->mariotype);
		MyFM.addObject(formName, std::move(mario));
	}

	auto texts = MakeObject::make_GameText("1-2");
	AddToFormManager(MyFM, formName, texts);
	auto cointext = std::find_if(texts->begin(), texts->end(), [](auto& it) {
		return it->name == "CoinnumText";
	});

	auto enemys = MakeObject::make_Enemys_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_2_Characters, Blocks);
	std::for_each(enemys->begin(), enemys->end(), [&](auto& it) {
		if (it->MyType == ObjectType::Goomba) {
			std::static_pointer_cast<Goomba>(it)->SetDark(true);
		}
		if (it->MyType == ObjectType::PiranaPlant) {
			std::static_pointer_cast<PiranaPlant>(it)->SetDark(true);
		}
	});
	AddToFormManager(MyFM, formName, enemys);

	auto objs = MakeObject::make_Objs();
	auto coinimg = std::make_shared<ImageObject>("coinimg", *Coin::GetFrames(), 10);
	coinimg->SetPosition((*cointext)->GetPosition() - glm::vec2{ coinimg->GetSize().x + (*cointext)->GetSize().x / 2, 0 });
	MyFM.addObject(formName, std::move(coinimg));

	{
		if (auto capoo_giphy = std::make_shared<ImageObject>("capoo_giphy", MyAPP::MyResourcesFilePath::Kapoo::getCapoo_giphyFrames().front(), 20)) {
			capoo_giphy->SetPosition({ GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 189.5, GetTopEdge(capoo_giphy) - PositionReference->GetSize().x * 2 });
			MyFM.addObject(formName, capoo_giphy);
			objs->push_back(std::move(capoo_giphy));
		}
		if (auto Kapoo_100 = std::make_shared<ImageObject>("Kapoo_100", MyAPP::MyResourcesFilePath::Kapoo::getKapoo_100Frames().front(), 20)) {
			Kapoo_100->SetPosition({ GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 188.5, GetTopEdge(Kapoo_100) - PositionReference->GetSize().x * 7 });
			MyFM.addObject(formName, Kapoo_100);
			objs->push_back(std::move(Kapoo_100));
		}
		if (auto Kapoo_Knowledge = std::make_shared<ImageObject>("Kapoo_Knowledge", MyAPP::MyResourcesFilePath::Kapoo::getKapoo_KnowledgeFrames().front(), 20)) {
			Kapoo_Knowledge->SetPosition({ GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 178, GetTopEdge(Kapoo_Knowledge) - PositionReference->GetSize().x * 7 });
			MyFM.addObject(formName, Kapoo_Knowledge);
			objs->push_back(std::move(Kapoo_Knowledge));
		}
		if (auto updateframe = std::make_shared<EventObject>("Update_Capoo_Giphy_Frame", [](EventObject* const self, void* data) {
				static size_t index = 0;
				static size_t index1 = 0;
				static size_t index2 = 0;
				auto fpscount = std::static_pointer_cast<size_t>(self->userdata);
				if (((*fpscount)++) >= 10) {
					index = (index + 1) % MyAPP::MyResourcesFilePath::Kapoo::getCapoo_giphyFrames().size();
					index1 = (index1 + 1) % MyAPP::MyResourcesFilePath::Kapoo::getKapoo_100Frames().size();
					index2 = (index2 + 1) % MyAPP::MyResourcesFilePath::Kapoo::getKapoo_KnowledgeFrames().size();
					auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
					if (auto img = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "capoo_giphy")) {
						std::static_pointer_cast<Util::Image>(img->GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::Kapoo::getCapoo_giphyFrames().at(index));
					}
					if (auto img = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "Kapoo_100")) {
						std::static_pointer_cast<Util::Image>(img->GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::Kapoo::getKapoo_100Frames().at(index1));
					}
					if (auto img = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "Kapoo_Knowledge")) {
						std::static_pointer_cast<Util::Image>(img->GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::Kapoo::getKapoo_KnowledgeFrames().at(index2));
					}
					(*fpscount) = 0;
				}
			})) {
			updateframe->userdata = std::make_shared<size_t>(0);
			MyFM.addObject(formName, std::move(updateframe));
		}
	}

	auto eventobj = std::make_shared<EventObject>("freeForm_1_2_Pipe", freeForm, false);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2_Pipe);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("MoveEvent", moveEvent);
	eventobj->userdata = std::make_shared<GameObjectTuple>(enemys, pipes, MakeObject::make_Props(),objs);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int>>(0, 300);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateleftedgePosEvent", [](EventObject* const self, void* data) {
		auto leftedge = std::static_pointer_cast<LeftEdge>(self->userdata);
		leftedge->m_Transform.translation = { GetLeftEdge(leftedge), 0 };
	});
	eventobj->userdata = std::move(leftedge);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	//MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateCoinCountText", UpdateCoinCountText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateFrameCount", UpdateFrameCount));

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
/// ��l��1-2����
/// </summary>
/// <param name=""></param>
INITFORM_FUNC(initForm_1_2_Pipe) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_2_Pipe;
	auto& Block = PositionReference::GetPositionReference();

	auto Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_2_Pipe_Images, BrickColor::dark);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	AddToFormManager(MyFM, formName, Blocks);

	{
		auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::MAP::Background_1_2_Pipe_ImagePath, Blocks, { GetLeftEdge(Block) + Block->GetSize().x * 3, 100 });
		MyFM.addObject(formName, std::move(BMptr.first));
		auto mario = std::move(BMptr.second);
		mario->changeType(self->mariotype);
		MyFM.addObject(formName, std::move(mario));
	}

	auto texts = MakeObject::make_GameText("1-2");
	AddToFormManager(MyFM, formName, texts);
	auto cointext = std::find_if(texts->begin(), texts->end(), [](auto& it) {
		return it->name == "CoinnumText";
	});

	if (auto pipeimg = std::make_shared<ImageObject>("pipeimg", MyAPP::MyResourcesFilePath::PipeDarkImagePath, 100)) {
		MakeObject::Fileinfo finfo;
		finfo.XY = { 14, -11.5 };
		finfo.ChangeXY();
		pipeimg->SetPosition(finfo.XY);
		MyFM.addObject(formName, pipeimg);
	}

	auto objs = MakeObject::make_Objs();
	auto coinimg = std::make_shared<ImageObject>("coinimg", *Coin::GetFrames(), 10);
	coinimg->SetPosition((*cointext)->GetPosition() - glm::vec2{ coinimg->GetSize().x + (*cointext)->GetSize().x / 2, 0 });
	MyFM.addObject(formName, std::move(coinimg));

	auto eventobj = std::make_shared<EventObject>("MoveEvent", moveEvent);
	eventobj->userdata = std::make_shared<GameObjectTuple>(MakeObject::make_Characters(), pipes, MakeObject::make_Props(), objs);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = MyFM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_2, "UpdateTimeTextEvent")->userdata;
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	//MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateCoinCountText", UpdateCoinCountText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateFrameCount", UpdateFrameCount));

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = checkPointArray;
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));
	
	//writeForm(MyFM, MyAPP::Form::FormNames::Form_1_2_Pipe);
}

INITFORM_FUNC(initForm_1_2_to_1_4) {
	using MyAPP::Form::Object::MakeObject;
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_2_to_1_4;
	auto& PositionReference = PositionReference::GetPositionReference();

	// �q�a���ɨ��o�Ҧ����
	auto Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_2_to_1_4_Images);
	auto pipes = GetPipeBricks(Blocks);
	auto flagpole = GetFlagpoles(Blocks);
	auto checkPointArray = GetCheckPoints(Blocks);
	auto leftedge = std::make_shared<LeftEdge>("LeftEdge");
	leftedge->SetPosition({ GetLeftEdge(leftedge), 0 });
	Blocks->push_back(leftedge);
	AddToFormManager(MyFM, formName, Blocks);

	// ���o�a�ϻP���O��
	{
		auto BMptr = MyAPP::Form::Object::MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::MAP::Background_1_2_to_1_4_ImagePath,
			Blocks, { GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 5.5, GetTopEdge(PositionReference) - PositionReference->GetSize().x * 10 });
		MyFM.addObject(formName, std::move(BMptr.first));
		auto mario = std::move(BMptr.second);
		mario->changeType(self->mariotype);
		MyFM.addObject(formName, std::move(mario));
	}

	// ���o�ɶ��B���ơB�ͩR��r���
	auto texts = MakeObject::make_GameText("1-2");
	AddToFormManager(MyFM, formName, texts);
	auto cointext = std::find_if(texts->begin(), texts->end(), [](auto& it) {
		return it->name == "CoinnumText";
	});

	// ���o�Ҧ��ĤH
	auto enemys = MakeObject::make_Characters();
	{
		auto tmp = std::make_shared<PiranaPlant>("PiranaPlant", 9);
		tmp->SetPosition({ GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 5.5, GetTopEdge(PositionReference) - PositionReference->GetSize().x * 11.5 });
		tmp->SetPos(tmp->GetPosition());
		tmp->setResetPosition(tmp->GetPosition());
		enemys->push_back(std::move(tmp));
	}
	AddToFormManager(MyFM, formName, enemys);

	auto props = MakeObject::make_Props();

	auto flagformpole = std::make_shared<FlagFromPole>("FlagFromPole", 100);
	flagformpole->SetPosition({ GetLeftEdge(PositionReference) + PositionReference->GetSize().x * 23.5f, GetTopEdge(PositionReference) - PositionReference->GetSize().y * 2 });
	MyFM.addObject(formName, (flagformpole));


	auto objs = MakeObject::make_Objs();
	objs->push_back(std::move(flagformpole));

	auto coinimg = std::make_shared<ImageObject>("coinimg", *Coin::GetFrames(), 10);
	coinimg->SetPosition((*cointext)->GetPosition() - glm::vec2{ coinimg->GetSize().x + (*cointext)->GetSize().x / 2, 0 });
	MyFM.addObject(formName, std::move(coinimg));

	// �]�w���ƥ�
	auto eventobj = std::make_shared<EventObject>("freeForm_1_2", freeForm, true);
	eventobj->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("MoveEvent", moveEvent);
	eventobj->userdata = std::make_shared<GameObjectTuple>(enemys, pipes, props, objs);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateFrameCount", UpdateFrameCount));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = MyFM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_2, "UpdateTimeTextEvent")->userdata;
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateleftedgePosEvent", [](EventObject* const self, void* data) {
		auto leftedge = std::static_pointer_cast<LeftEdge>(self->userdata);
		leftedge->m_Transform.translation = { GetLeftEdge(leftedge), 0 };
	});
	eventobj->userdata = std::move(leftedge);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("CheckFlagpoleCollision", CheckFlagpoleCollision);
	eventobj->userdata = (flagpole);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FlagpoleAddPoint", FlagpoleAddPoint, false));

	eventobj = std::make_shared<EventObject>("moveToDoor", moveToDoor, false);
	eventobj->userdata = Getdoors(Blocks);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateCoinCountText", UpdateCoinCountText, true));
	//MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = checkPointArray;
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));

	//MyAPP::Form::writeForm(MyFM, formName);
}

INITFORM_FUNC(initForm_1_4) {
	using MyAPP::Form::Object::MakeObject;
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::Form_1_4;
	auto& PositionReference = PositionReference::GetPositionReference();

	auto Blocks = MakeObject::make_Bricks_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_4_Images, BrickColor::grey);
	auto checkPointArray =  GetCheckPoints(Blocks);
	auto leftedge = std::make_shared<LeftEdge>("LeftEdge");
	Blocks->push_back(leftedge);
	AddToFormManager(MyFM, formName, Blocks);

	{
		auto BMptr = MakeObject::make_Background_And_Mario(MyAPP::MyResourcesFilePath::MAP::Background_1_4_ImagePath, Blocks, { GetLeftEdge(PositionReference) + PositionReference->GetSize().x, GetTopEdge(PositionReference) - PositionReference->GetSize().y * 6 });
		MyFM.addObject(formName, std::move(BMptr.first));
		auto mario = std::move(BMptr.second);
		mario->changeType(self->mariotype);
		MyFM.addObject(formName, std::move(mario));
	}

	auto texts = MakeObject::make_GameText("1-4");
	AddToFormManager(MyFM, formName, texts);
	auto cointext = std::find_if(texts->begin(), texts->end(), [](auto& it) {
		return it->name == "CoinnumText";
	});

	auto enemys = MakeObject::make_Enemys_From_File(MyAPP::MyResourcesFilePath::MAP::Form_1_4_Characters, Blocks);
	AddToFormManager(MyFM, formName, enemys);

	auto objs = MakeObject::make_Objs();

	auto coinimg = std::make_shared<ImageObject>("coinimg", *Coin::GetFrames(), 10);
	coinimg->SetPosition((*cointext)->GetPosition() - glm::vec2{ coinimg->GetSize().x + (*cointext)->GetSize().x / 2, 0 });
	MyFM.addObject(formName, std::move(coinimg));

	auto eventobj = std::make_shared<EventObject>("Form_1_2_to_1_4", freeForm, true);
	eventobj->userdata = std::move(std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2_to_1_4));
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("MoveEvent", moveEvent);
	eventobj->userdata = std::make_shared<GameObjectTuple>(enemys, std::move(MakeObject::make_Bricks()), std::move(MakeObject::make_Props()), objs);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("UpdateTimeTextEvent", UpdateTimeText);
	eventobj->userdata = std::make_shared<std::tuple<int, int>>(0, 300);
	MyFM.addObject(formName, std::move(eventobj));

	MyFM.addObject(formName, std::make_shared<EventObject>("CheckMarioPosition", CheckMarioPosition));

	//MyFM.addObject(formName, std::make_shared<EventObject>("UpdateHPText", UpdateHPText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdatePointText", UpdatePointText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateCoinCountText", UpdateCoinCountText, true));
	MyFM.addObject(formName, std::make_shared<EventObject>("UpdateFrameCount", UpdateFrameCount));

	eventobj = std::make_shared<EventObject>("UpdateleftedgePosEvent", [](EventObject* const self, void* data) {
		auto leftedge = std::static_pointer_cast<LeftEdge>(self->userdata);
		leftedge->m_Transform.translation = { GetLeftEdge(leftedge), 0 };
	});
	eventobj->userdata = std::move(leftedge);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("SleepAllevent", SleepAllevent, false);
	MyFM.addObject(formName, std::move(eventobj));

	eventobj = std::make_shared<EventObject>("GoBackCheckPoint", GoBackCheckPoint, false);
	eventobj->userdata = std::move(GetCheckPoints(Blocks));
	MyFM.addObject(formName, std::move(eventobj));

	{
		auto door = Getdoors(Blocks);
		auto event = std::make_shared<EventObject>("moveToDoor", [](EventObject*const self, void* data) {
			auto door = std::static_pointer_cast<BrickPtrVec>(self->userdata);
			static_cast<MyAPP::GameManager*>(data)->opMode = false;
			if (door) {
				auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
				auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent")->userdata);
				auto& [enemys, pipes, props, objs] = (*tuplePtr);
				auto background = FM.GetFormObject<MyAPP::Form::Object::ImageObject>(FM.GetNowForm(), "Background");
				auto mario = FM.GetFormObject<MyAPP::Form::Object::Mario>(FM.GetNowForm(), "Mario");
				auto block = std::static_pointer_cast<BrickPtrVec>(background->userdata);
				auto flag = true;
				auto marioPos = mario->GetPosition();
				auto mariosize = mario->GetSize();
				float Displacement = MyAPP::Form::Object::getDEFAULTDISPLACEMENT();
				auto pos = (background)->GetPosition();
				pos.x -= Displacement;
				std::for_each(std::execution::seq, block->begin(), block->end(),
					[&](auto& it) {
						it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
					});
				std::for_each(std::execution::seq, enemys->begin(), enemys->end(),
					[&](auto& it) {
						it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
					});
				std::for_each(std::execution::seq, props->begin(), props->end(),
					[&](auto& it) {
						it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
					});
				std::for_each(std::execution::seq, objs->begin(), objs->end(),
					[&](auto& it) {
						it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
					});
				(background)->SetPosition(pos);
				mario->move();
			}
		}, false);
		event->userdata = std::move(door);
		MyFM.addObject(formName,std::move(event));
	}

	MyFM.addObject(formName, std::make_shared<EventObject>("FinifhEvent", CallFinish, false));
	MyFM.addObject(formName, std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false));


	//writeForm(MyFM, formName);
}

INITFORM_FUNC(diedForm) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = MyAPP::Form::FormNames::DiedForm;
	const auto multiple = ((float)WINDOW_HEIGHT / 480.f);
	auto& PositionReference = PositionReference::GetPositionReference();
	using MRFP = MyAPP::MyResourcesFilePath;
	
	auto texts = MakeObject::make_GameText("1-1");

	{
		texts->erase(std::find_if(texts->begin(), texts->end(), [](auto& it) {
			return it->name == "Timetext";
		}));
	}

	{
		auto label1 = std::make_shared<TextObject>("label1", MRFP::SuperMarioFont, 20 * multiple, "WORLD 1-1", Util::Color::FromName(Util::Colors::WHITE), 100);
		label1->SetPosition({ 0, label1->GetSize().y * 2 });
		texts->push_back(std::move(label1));
	}

	{
		auto cointext = std::find_if(texts->begin(), texts->end(), [](auto& it) {
			return it->name == "CoinnumText";
		});
		auto coinimg = std::make_shared<ImageObject>("coinimg", *Coin::GetFrames(), 10);
		coinimg->SetPosition((*cointext)->GetPosition() - glm::vec2{ coinimg->GetSize().x + (*cointext)->GetSize().x / 2, 0 });
		MyFM.addObject(formName, std::move(coinimg));
	}

	{
		auto marioimg = std::make_shared<ImageObject>("marioimg", MRFP::MarioStanding, 100);
		marioimg->SetPosition({ marioimg->GetSize() * glm::vec2{-2.0, 0} });

		auto text = std::make_shared<TextObject>("label2", MRFP::SuperMarioFont, 20 * multiple, "x  3", Util::Color::FromName(Util::Colors::WHITE), 100);
		text->SetPosition(marioimg->GetPosition() + glm::vec2{ PositionReference->GetSize().x * 3, 0 });
		texts->push_back(std::move(text));

		MyFM.addObject(formName, std::move(marioimg));
	}

	AddToFormManager(MyFM, formName, texts);

	{
		{
			auto updateEvent = std::make_shared<EventObject>("UpdateInfo", [](EventObject* const self, void* data) {
				auto GM = static_cast<MyAPP::GameManager*>(data);
				auto& FM = GM->GetFormManger();
				auto strptr = std::static_pointer_cast<std::string>(self->userdata);
				if (strptr == nullptr) {
					strptr = std::make_shared<std::string>("???");
				}
				{
					auto text = FM.GetFormObject<TextObject>(FM.GetNowForm(), "NOWWorldtext");
					if (text) {
						std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(*strptr);
					}
				}
				{
					auto text = FM.GetFormObject<TextObject>(FM.GetNowForm(), "label1");
					if (text) {
						std::unique_ptr<char> buffer(new char[16]);
						std::sprintf(buffer.get(), "WORLD %s", strptr->c_str());
						std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(buffer.get());
					}
				}
				{
					auto text = FM.GetFormObject<TextObject>(FM.GetNowForm(), "CoinnumText");
					if (text) {
						std::unique_ptr<char> buffer(new char[16]);
						std::sprintf(buffer.get(), "x%02u", GM->coinCount);
						std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(buffer.get());
					}
				}
				{
					auto text = FM.GetFormObject<TextObject>(FM.GetNowForm(), "PointText");
					if (text) {
						std::unique_ptr<char> buffer(new char[16]);
						std::sprintf(buffer.get(), "%06d", GM->GetPoint());
						std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(buffer.get());
					}
				}
				{
					auto text = FM.GetFormObject<TextObject>(FM.GetNowForm(), "label2");
					if (text) {
						std::unique_ptr<char> buffer(new char[8]);
						std::sprintf(buffer.get(), "x  %d", GM->GetHP());
						std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(buffer.get());
					}
				}
				self->Enable = false;
			});
			updateEvent->userdata = std::make_shared<std::string>("1-1");
			MyFM.addObject(formName, std::move(updateEvent));
		}
		{
			auto delayEvent = std::make_shared<EventObject>("DelayEvent", [](EventObject* const self, void* data) {
				auto GM = static_cast<MyAPP::GameManager*>(data);
				auto& FM = GM->GetFormManger();
				auto delayCount = std::static_pointer_cast<int>(self->userdata);
				if (*delayCount > 0) {
					(*delayCount)--;
				}
				else {
					FM.GetFormObject<EventObject>(FM.GetNowForm(), "ChangeFormEvent")->Enable = true;
				}
			});
			delayEvent->userdata = std::make_shared<int>(FPS_CAP * 2);
			MyFM.addObject(formName, std::move(delayEvent));
		}
		MyFM.addObject(formName, std::make_shared<EventObject>("UpdateFrameCount", UpdateFrameCount));
		{
			auto changeevent = std::make_shared<EventObject>("ChangeFormEvent", ChangeFormEvent, false);
			changeevent->userdata = std::make_shared<std::string>(FormNames::Form_1_1);
			MyFM.addObject(formName, std::move(changeevent));
		}
	}
}

INITFORM_FUNC(initForm1) {
	auto& MyFM = self->GetFormManger();
	constexpr auto& formName = "Form1";
	using MPATH = MyAPP::MyResourcesFilePath;
	
	//��r���
	{
		if (auto text = std::make_shared<TextObject>("label1", MPATH::ArialFontPath, 50, "hello world!", Util::Color(255, 255, 255))) {
			text->SetPosition({ 0, 0 });
			MyFM.addObject(formName, std::move(text));
		}
	}
	// ���s
	{
		auto buttoncallback = [](Button* const self, void* data) {
			std::cout << self->name << " is clicked!\n\r";
		};
		for (auto i = 0; i < 3; ++i) {
			auto button = std::make_shared<Button>(std::string("Button") + std::to_string(i), MPATH::ArialFontPath, 50, std::string("Button") + std::to_string(i), Util::Color(255, 255, 255));
			if (button == nullptr)
				continue;
			button->CallBackFunc = buttoncallback;
			button->SetPosition({ GetLeftEdge(button) + button->GetSize().x, GetTopEdge(button) - button->GetSize().y * i });
			MyFM.addObject(formName, std::move(button));
		}
	}
	// �Ϥ����
	{
		if (auto img = std::make_shared<ImageObject>("img", MY_RESOURCE_DIR "\\Image\\Background\\cat.jpg",1)) {
			img->SetPosition({ -GetLeftEdge(img), -GetTopEdge(img) });
			MyFM.addObject(formName, std::move(img));
		}
	}
	//�ƥ�
	{
		auto systemTime = [](EventObject*const self,void*data) {
			auto num = std::static_pointer_cast<int>(self->userdata);
			if ((*num)++ >= FPS_CAP) {
				auto currentTime = std::chrono::system_clock::now();
				auto time = std::chrono::system_clock::to_time_t(currentTime);
				std::cout << "�ثe�ɶ��G" << std::ctime(&time);
				(*num) = 0;
			}
		};
		if (auto timeEvent = std::make_shared<EventObject>("timeEvent", systemTime)) {
			timeEvent->userdata = std::make_shared<int>(0);
			MyFM.addObject(formName, std::move(timeEvent));
		}
	}
}

#endif // !INITFORMFUNC_HPP
