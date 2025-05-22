#include "Object/Brick/HiddenBrick.hpp"
#include "Object/ObjectType.hpp"
#include "Object/Props/Mushroom.hpp"
#include "GameManager.hpp"
#include <memory>


void MyAPP:: Form::Object::HiddenBrick::behavior(void* data) {
	CheckCollision(data);
	// dojump();
	// comeDown();
}

void MyAPP::Form::Object::HiddenBrick::CheckCollision(void* data) {
	if (!m_Visible) {
		auto GM = static_cast<MyAPP::GameManager*>(data);
		auto& FM = GM->GetFormManger();
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		if (mario->inRange(this->m_Transform.translation, GetSize())) {
			bonkJump();
			m_Visible = true;
			collisionable = true;
			/*GM->IncHP();
			FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdateHPText")->Enable = true;*/
			using namespace MyAPP::Form::Object::Props;
			auto mushroom = std::make_shared<Mushroom>("Mushroom", Mushroom::GetImages<Mushroom::Category::Mushroom>(), Mushroom::Category::Mushroom, 9);
			mushroom->SetPosition(GetPosition());
			mushroom->SetUpDistance(GetSize().y);
			mushroom->userdata = mario->userdata;
			auto& moveevent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
			auto tuplePtr = std::static_pointer_cast<std::tuple<std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Character>>>, std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Brick>>>, std::shared_ptr<std::vector<std::shared_ptr<MyAPP::Form::Object::Props::Props>>>>>(moveevent->userdata);
			auto& [_, __,props] = (*tuplePtr);
			props->push_back(mushroom);
			FM.addObject(FM.GetNowForm(), std::move(mushroom));
		}
	}
}