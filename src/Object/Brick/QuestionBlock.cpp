#include "Object/Brick/QuestionBlock.hpp"
#include "config.hpp"
#include "GameManager.hpp"
#include "Form/FormManger.hpp"
#include "Object/EventObject.hpp"
#include "Util/Image.hpp"
#include "FilePath.hpp"
#include "Object/Props/Props.hpp"
#include "userType.hpp"
#include <memory>
#include <utility> // for std::move
namespace MyAPP::Form:: Object {
	void QuestionBlock::bonk() noexcept {
		if (play) {
			isbonked = true;
			SetVisible(true);
			play = false;
			switch (color) {
			case MyAPP::Form::Object::BrickColor::normal:
				std::static_pointer_cast<Util::Image>(GetDrawable())
					->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockImagePath);
				break;
			case MyAPP::Form::Object::BrickColor::dark:
				std::static_pointer_cast<Util::Image>(GetDrawable())
					->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockDarkImagePath);
				break;
			case MyAPP::Form::Object::BrickColor::grey:
				std::static_pointer_cast<Util::Image>(GetDrawable())
					->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockGreyImagePath);
				break;
			default:
				break;
			}
		}
	}

	void QuestionBlock::behavior(void* data) {
		PlayFrames();
		dojump();
		comeDown();
		CreateProp(static_cast<GameManager*>(data));
	}

	void QuestionBlock::PlayFrames() noexcept {
		if (play) {
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(GetFrame());
		}
	}
	void QuestionBlock::CreateProp(GameManager* const GM) noexcept {
		if (!isbonked) {
			return;
		}
		auto& FM = GM->GetFormManger();
		if (userdata == nullptr) {
			CoinPoints::CreateCoinPoints(FM, GetPosition());
			Points::UpdatePoint(FM, Points::PointType::pts200);
			GM->addPoint(200);
			GM->coinCount++;
			GM->sfx->LoadMedia(MyAPP::MyResourcesFilePath::Get_coin);
			GM->sfx->Play(0);
			isbonked = false;
			return;
		}
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		if (mario == nullptr) {
			return;
		}
		{
			using namespace MyAPP::Form::Object::Props;
			PropsPtr prop;
			auto proptype = std::static_pointer_cast<std::string>(userdata);
			if (proptype != nullptr && *proptype == "BigMushroom") {
				if (mario->isMiniMario()) {
					prop = std::make_shared<Mushroom>("Mushroom", Mushroom::GetImages<Mushroom::Category::BigMushroom>(), Mushroom::Category::BigMushroom, 9);
					prop->SetPosition(GetPosition());
					std::static_pointer_cast<Mushroom>(prop)->SetUpDistance(GetSize().y*1.1);
				}
				else {
					prop = std::make_shared<FireFlower>("FireFlower", 9);
					prop->SetPosition(GetPosition());
					std::static_pointer_cast<FireFlower>(prop)->SetUpDistance(GetSize().y);
					/*prop = std::make_shared<Starman>("FireFlower", 9);
					prop->SetPosition(GetPosition() + glm::vec2{ 0,GetSize().y });
					std::static_pointer_cast<Starman>(prop)->SetUpDistance(GetSize().y*3);*/
				}
			}
			if(prop){
				prop->userdata = mario->userdata;
				// Set the position of the prop to be slightly above the question block
				{
					auto& moveevent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
					auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveevent->userdata);
					auto& [_, __, props, ___] = (*tuplePtr);
					FM.addObject(FM.GetNowForm(), prop);
					props->push_back(std::move(prop));
				}
			}
			isbonked = false;
		}
	}
}