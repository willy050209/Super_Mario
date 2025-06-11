#include "Object/Brick/MovingPlatform.hpp"
#include "Position.hpp"
#include "GameManager.hpp"
#include "FormManger.hpp"
#include "Object/Character/Mario.hpp"

void MyAPP::Form::Object::MovingPlatform::behavior(void* data) {
	if (up) {
		SetPosition(m_Transform.translation + glm::vec2{ 0, 2 * ((float)WINDOW_HEIGHT / 480) });
		if (!isInWindow(this)) {
			SetPosition(glm::vec2{ m_Transform.translation.x, -GetTopEdge(this) } - glm::vec2{ 0, GetSize().y });
		}
	}
	else {
		SetPosition(m_Transform.translation - glm::vec2{ 0, 2 * ((float)WINDOW_HEIGHT / 480) });
		if (!isInWindow(this)) {
			SetPosition(glm::vec2{ m_Transform.translation.x, GetTopEdge(this) } + glm::vec2{ 0, GetSize().y });
		}
	}
	//CheckCollision(data);
}

void MyAPP::Form::Object::MovingPlatform::CheckCollision(void* data) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	if (mario) {
		if (inRange(mario->GetPosition(), GetSize()) ) {
			mario->SetPosition({ mario->GetPosition().x, GetPosition().y + GetSize().y / 2 + mario->GetSize().y/2  });
		}
	}
}

