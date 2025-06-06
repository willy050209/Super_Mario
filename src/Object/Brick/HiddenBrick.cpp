#include "Object/Brick/HiddenBrick.hpp"
#include "Object/ObjectType.hpp"
#include "Object/Props/Mushroom.hpp"
#include "Object/Character/Character.hpp"
#include "Object/Character/Mario.hpp"
#include "Object/EventObject.hpp"
#include "Object/Props/Props.hpp"
#include "GameManager.hpp"
#include "userType.hpp"
#include <memory>


void MyAPP:: Form::Object::HiddenBrick::behavior(void* data) {
	CheckCollision(data);
}

void MyAPP::Form::Object::HiddenBrick::CheckCollision(void* data) {
	if (!m_Visible) {
		using namespace MyAPP::Form::Object;
		auto GM = static_cast<MyAPP::GameManager*>(data);
		auto& FM = GM->GetFormManger();
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		if (mario->inRange(this->m_Transform.translation, GetSize()) && mario->GetState() == Mario::State::UP) {
			//bonkJump();
			m_Visible = true;
			collisionable = true;
			using namespace MyAPP::Form::Object::Props;
			using MyAPP::Form::Object::Props::Props;
			auto data = std::static_pointer_cast<std::string>(userdata);
			if (data) {
				if (*data == "Mushroom") {
					auto mushroom = std::make_shared<Mushroom>("Mushroom", Mushroom::GetImages<Mushroom::Category::Mushroom>(), Mushroom::Category::Mushroom, 9);
					mushroom->SetPosition(GetPosition());
					mushroom->SetUpDistance(GetSize().y * 1.1);
					mushroom->userdata = mario->userdata;
					{
						auto& moveevent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
						auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveevent->userdata);
						auto& [_, __, props, ___] = (*tuplePtr);
						props->push_back(mushroom);
					}
					FM.addObject(FM.GetNowForm(), std::move(mushroom));
				}
				else {
					CoinPoints::CreateCoinPoints(FM, GetPosition());
					GM->coinCount++;
				}
			}
		}
	}
}