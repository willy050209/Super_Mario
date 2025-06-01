#include "Object/FlagFromPole.hpp"
#include "Object/Character/Mario.hpp"
#include "GameManager.hpp"

void MyAPP::Form::Object::FlagFromPole::behavior(void* data) {
	if(enabled){
		using namespace MyAPP::Form::Object;
		auto GM = static_cast<MyAPP::GameManager*>(data);
		auto& FM = GM->GetFormManger();
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		if (mario->GetState() != Mario::State::MOVE) {
			auto tmp = mario->GetPosition();
			tmp.x = m_Transform.translation.x;
			SetPosition(tmp);
		}
		else {
			m_Visible = false;
		}
	}
}