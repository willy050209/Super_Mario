#include "Object/Brick/MovingPlatform.hpp"
#include "Position.hpp"

void MyAPP::Form::Object::MovingPlatform::behavior(void* data) {
	if (up) {
		SetPosition(m_Transform.translation + glm::vec2{ 0, 2 * ((float)WINDOW_HEIGHT / 480) });
		if (!inWindows(this)) {
			SetPosition(glm::vec2{ m_Transform.translation.x, -GetY0(this) } - glm::vec2{ 0, GetSize().y });
		}
	}
	else {
		SetPosition(m_Transform.translation - glm::vec2{ 0, 2 * ((float)WINDOW_HEIGHT / 480) });
		if (!inWindows(this)) {
			SetPosition(glm::vec2{ m_Transform.translation.x, GetY0(this) } + glm::vec2{ 0, GetSize().y });
		}
	}
}

