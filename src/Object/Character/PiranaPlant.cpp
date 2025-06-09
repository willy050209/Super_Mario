#include "Object/Character/PiranaPlant.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"
#include "userType.hpp"

#include <memory>
#include <execution>
#include <algorithm>

void MyAPP::Form::Object::PiranaPlant::behavior(void* data) {
	if (!dead) {
		auto& FM = static_cast<GameManager*>(data)->GetFormManger();
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		move();
		if (std::abs(mario->GetPosition().x - GetPosition().x) >= mario->GetSize().x*2) {
			CheckCollision(data);
			PlayFrames();
		}
		else {
			m_Visible = false;
			collisionable = false;
		}
	}
}

void MyAPP::Form::Object::PiranaPlant::died() noexcept {
	m_Visible = false;
	collisionable = false;
	dead = true;
}

void MyAPP::Form::Object::PiranaPlant::move() noexcept {
	switch (m_static) {
	case PiranaPlantStatic::wait_:
		wait();
		m_Visible = false;
		collisionable = false;
		break;
	case PiranaPlantStatic::wait:
		wait();
		m_Visible = true;
		collisionable = true;
		break;
	case PiranaPlantStatic::up:
		up();
		m_Visible = false;
		collisionable = false;
		break;
	case PiranaPlantStatic::down:
		down();
		m_Visible = false;
		collisionable = false;
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
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	if (mario == nullptr)
		return;
	if (collisionable && inRange(mario->GetPosition(), mario->GetSize())) {
		if (mario->isInvincible()) {
			died();
			switch (mario->jumpCobo) {
			case 0:
			case 1:
				GM->addPoint(100);
				Points::UpdatePoint(FM, Points::PointType::pts100);
				break;
			case 2:
				GM->addPoint(200);
				Points::UpdatePoint(FM, Points::PointType::pts200);
				break;
			case 3:
				GM->addPoint(400);
				Points::UpdatePoint(FM, Points::PointType::pts400);
				break;
			case 4:
				GM->addPoint(800);
				Points::UpdatePoint(FM, Points::PointType::pts800);
				break;
			case 5:
				GM->addPoint(1000);
				Points::UpdatePoint(FM, Points::PointType::pts1000);
				break;
			case 6:
				GM->addPoint(2000);
				Points::UpdatePoint(FM, Points::PointType::pts2000);
				break;
			case 7:
				GM->addPoint(4000);
				Points::UpdatePoint(FM, Points::PointType::pts4000);
				break;
			case 8:
				GM->addPoint(5000);
				Points::UpdatePoint(FM, Points::PointType::pts5000);
				break;
			default:
				GM->IncHP();
				Points::UpdatePoint(FM, Points::PointType::pts1up);
				break;
			}
		}
		else {
			mario->died();
			if (mario->isdied()) {
				GM->LostALife();
			}
		}
	}
}

void MyAPP::Form::Object::PiranaPlant::up() noexcept {
	if (m_Transform.translation.y < pos.y + GetSize().y) {
		m_Transform.translation.y += GetSize().y / 24;
	}
	else {
		static_count = FPS_CAP * 3;
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
		static_count = FPS_CAP * 3;
		m_static = PiranaPlantStatic::wait_;
	}
}
