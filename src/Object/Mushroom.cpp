#include "Object/Props/Mushroom.hpp"
#include "GameManager.hpp"
#include "userType.hpp"
#include <iostream>

void MyAPP::Form::Object::Props::Mushroom::behavior(void* data) {
	CheckCollision(data);
	doUp();
	Move(glm::vec2(GetSize().x / 16, 0));
	doDown();
}

void MyAPP::Form::Object::Props::Mushroom::Move(glm::vec2 distance) noexcept {
	if (m_movable) {
		using MyAPP::Form::Object::Brick;
		auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
		auto MyPos = GetPosition() + distance;
		const auto MySize = GetSize();
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(MyPos, MySize)) {
				MyPos.x = it->GetPosition().x - (static_cast<int>(it->GetSize().x) >> 1) - (static_cast<int>(MySize.x) >> 1);
				break;
			}
		}
		m_Transform.translation = MyPos;

	}
}

void MyAPP::Form::Object::Props::Mushroom::CheckCollision(void* gm) {
	if (m_Visible) {
		auto GM = static_cast<MyAPP::GameManager*>(gm);
		auto& FM = GM->GetFormManger();
		auto& mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		if (inRange(mario->GetPosition(), mario->GetSize())) {
			switch (MyCategory) {
			case Mushroom::Category::Mushroom:
				std::cout << "touch Mushroom\n";
				GM->IncHP();
				Points::UpdatePoint(FM, Points::PointType::pts1up);
				break;
			case Mushroom::Category::MushroomDark:
				std::cout << "touch MushroomDark\n";
				GM->IncHP();
				Points::UpdatePoint(FM, Points::PointType::pts1up);
				break;
			case Mushroom::Category::BigMushroom:
				std::cout << "touch BigMushroom\n";
				if (mario->GetMario_type() == Mario::Mario_type::Mario) {
					mario->changeType(Mario::Mario_type::SuperMario);
				}
				else if (mario->GetMario_type() == Mario::Mario_type::InvincibleMario) {
					mario->changeType(Mario::Mario_type::InvincibleSuperMario);
				}
				break;
			default:
				break;
			}

			m_Visible = false;
		}
	}
}
void MyAPP::Form::Object::Props::Mushroom::doUp() noexcept {
	if (UpDistance <= 0) {
		return;
	}
	auto tmp = GetSize().y / 16;
	UpDistance -= tmp;
	if (UpDistance <= 0) {
		UpDistance = 0;
		m_movable = true;
	}
	m_Transform.translation.y += tmp;
}

void MyAPP::Form::Object::Props::Mushroom::doDown() noexcept {
	if (UpDistance > 0) {
		return;
	}
	using MyAPP::Form::Object::Brick;
	auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
	auto MyPos = GetPosition();
	if (MyPos.y < WINDOW_HEIGHT) {
		const auto MySize = GetSize();
		MyPos.y -= GetSize().y / 8;
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(MyPos, MySize)) {
				MyPos.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
				break;
			}
		}
		SetPosition(MyPos);
	}
}

		