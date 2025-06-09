#include "Object/Brick/PropBrick.hpp"
#include "GameManager.hpp"
#include "userType.hpp"
#include "Object/Props/FireFlower.hpp"
#include "Object/Props/Mushroom.hpp"
#include "Object/Props/Starman.hpp"
#include "FilePath.hpp"

void MyAPP::Form::Object::PropBrick::bonk() noexcept {

	switch (color) {
	case MyAPP::Form::Object::BrickColor::normal:
		std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockImagePath);
		break;
	case MyAPP::Form::Object::BrickColor::dark:
		std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockDarkImagePath);
		break;
	case MyAPP::Form::Object::BrickColor::grey:
		std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(MyAPP::MyResourcesFilePath::EmptyBlockGreyImagePath);
		break;
	default:
		break;
	}
	trigger = true;
}

void MyAPP::Form::Object::PropBrick::behavior(void* data) {
	if (trigger) {
		using namespace MyAPP::Form::Object::Props;
		auto& FM = static_cast<GameManager*>(data)->GetFormManger();
		{
			PropsPtr prop{ nullptr };
			if (proptype == "BigMushroomOrFireFlower") {
				if (FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario")->isMiniMario()) {
					prop = std::make_shared<Mushroom>("BigMushroom", Mushroom::GetImages<Mushroom::Category::BigMushroom>(), Mushroom::Category::BigMushroom, 9);
					std::static_pointer_cast<Mushroom>(prop)->SetUpDistance(GetSize().y*1.1);
				}
				else {
					prop = std::make_shared<FireFlower>("FireFlower", 9);
					std::static_pointer_cast<FireFlower>(prop)->SetUpDistance(GetSize().y);
				}
				prop->SetPosition(GetPosition());
			}
			else if (proptype == "Starman") {
				prop = std::make_shared<Starman>("Starman", 9);
				prop->SetPosition(GetPosition() + glm::vec2{ 0, GetSize().y });
				std::static_pointer_cast<Starman>(prop)->SetUpDistance(GetSize().y*1.1);
			}
			else if (proptype == "BigMushroom") {
				prop = std::make_shared<Mushroom>("BigMushroom", Mushroom::GetImages<Mushroom::Category::BigMushroom>(), Mushroom::Category::BigMushroom, 9);
				prop->SetPosition(GetPosition());
				std::static_pointer_cast<Mushroom>(prop)->SetUpDistance(GetSize().y*1.1);
			}
			else if (proptype == "Mushroom") {
				prop = std::make_shared<Mushroom>("Mushroom", Mushroom::GetImages<Mushroom::Category::Mushroom>(), Mushroom::Category::Mushroom, 9);
				prop->SetPosition(GetPosition());
				std::static_pointer_cast<Mushroom>(prop)->SetUpDistance(GetSize().y*1.1);
			}
			else if (proptype == "MushroomDark") {
				prop = std::make_shared<Mushroom>("MushroomDark", Mushroom::GetImages<Mushroom::Category::MushroomDark>(), Mushroom::Category::MushroomDark, 9);
				prop->SetPosition(GetPosition());
				std::static_pointer_cast<Mushroom>(prop)->SetUpDistance(GetSize().y*1.1);
			}
			else if (proptype == "FireFlower") {
				prop = std::make_shared<FireFlower>("FireFlower", 9);
				prop->SetPosition(GetPosition());
				std::static_pointer_cast<FireFlower>(prop)->SetUpDistance(GetSize().y);
			}
			proptype.clear(); // Clear the proptype after using it
			if (prop == nullptr) {
				return; // No valid prop type specified
			}
			prop->userdata = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario")->userdata;
			// Set the position of the prop to be slightly above the question block
			{
				auto& moveevent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
				auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveevent->userdata);
				auto& [_, __, props, ___] = (*tuplePtr);
				FM.addObject(FM.GetNowForm(), prop);
				props->push_back(std::move(prop));
			}
		}
	}
	dojump();
	comeDown();
}
