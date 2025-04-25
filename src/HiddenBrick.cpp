#include "Object/HiddenBrick.hpp"
#include "Object/ObjectType.hpp"
#include "GameManager.hpp"
#include <memory>

void HiddenBrick::behavior(void* data) {
	if (!m_Visible) {
		auto GM = static_cast<GameManager*>(data);
		auto& FM = GM->GetFormManger();
		auto mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Mario, "Mario"));
		if (mario->inRange(this->m_Transform.translation, GetSize())) {
			bonkJump();
			m_Visible = true;
			collisionable = true;
			GM->IncHP();
			std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "UpdateHPText"))->Enable = true;
		}
	}
	//dojump();
	//comeDown();
}
