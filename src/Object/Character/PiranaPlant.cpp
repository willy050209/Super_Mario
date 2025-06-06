#include "Object/Character/PiranaPlant.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"
#include "userType.hpp"

#include <memory>
#include <execution>
#include <algorithm>

void MyAPP::Form::Object::PiranaPlant::behavior(void* data) {
	move();
	CheckCollision(data);
	PlayFrames();
}

void MyAPP::Form::Object::PiranaPlant::died() noexcept {
	m_Visible = false;
	collisionable = false;
}

void MyAPP::Form::Object::PiranaPlant::move() noexcept {
	switch (m_static) {
	case PiranaPlantStatic::wait_:
		wait();
		m_Visible = false;
		break;
	case PiranaPlantStatic::wait:
		wait();
		m_Visible = true;
		break;
	case PiranaPlantStatic::up:
		up();
		m_Visible = false;
		break;
	case PiranaPlantStatic::down:
		down();
		m_Visible = false;
		break;
	}

}

void MyAPP::Form::Object::PiranaPlant::PlayFrames() noexcept {
	imageChangeDelay++;
	if (imageChangeDelay >= (FPS_CAP / 3)) {
		std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(GetFrame());
		imageChangeDelay = 0;
	}
}

void MyAPP::Form::Object::PiranaPlant::CheckCollision(void *data)  {
}

void MyAPP::Form::Object::PiranaPlant::up() noexcept {
	if (m_Transform.translation.y < pos.y + GetSize().y) {
		m_Transform.translation.y += GetSize().y / 24;
	}
	else {
		static_count = FPS_CAP;
		m_static = PiranaPlantStatic::wait;
	}
}

void MyAPP::Form::Object::PiranaPlant::wait() noexcept {
	static_count--;
	if (static_count <= 0) {
		m_static = (m_static == PiranaPlantStatic::wait) ? PiranaPlantStatic::down : PiranaPlantStatic::up;
	}
}

void MyAPP::Form::Object::PiranaPlant::down() noexcept {
	if (m_Transform.translation.y > pos.y) {
		m_Transform.translation.y -= GetSize().y / 24;
	}
	else {
		static_count = FPS_CAP;
		m_static = PiranaPlantStatic::wait_;
	}
}
