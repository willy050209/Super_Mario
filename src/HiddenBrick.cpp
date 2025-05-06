#include "Object/HiddenBrick.hpp"
#include "Object/ObjectType.hpp"
#include "GameManager.hpp"
#include <memory>

void HiddenBrick::behavior(void* data) {
	if (!m_Visible) {
		auto GM = static_cast<GameManager*>(data);
		auto& FM = GM->GetFormManger();
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		if (mario->inRange(this->m_Transform.translation, GetSize())) {
			bonkJump();
			m_Visible = true;
			collisionable = true;
			GM->IncHP();
			FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdateHPText")->Enable = true;
		}
	}
	//dojump();
	//comeDown();
}
