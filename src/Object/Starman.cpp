#include "Object/Props/Starman.hpp"
//#include "Object/Mario.hpp"
#include "config.hpp"
#include "GameManager.hpp"

#include <iostream>
namespace MyAPP::Form::Object::Props {
	void Starman::behavior(void* data) {
		PlayFrames();
		CheckCollision(data);
		doJump();
		doDown();
		Move({ GetSize().x / 16, 0 });
	}

	void Starman::Move(const glm::vec2& distance) noexcept {
		if (m_movable) {
			using MyAPP::Form::Object::Brick;
			auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
			auto MyPos = GetPosition() + distance;
			const auto MySize = GetSize();
			for (auto& it : *bricks) {
				if (it->collisionable && it->inRange(MyPos, MySize)) {
					MyPos.x = it->GetPosition().x - ((it->GetSize().x) /2) - ((MySize.x) /2);
					break;
				}
			}
			m_Transform.translation = MyPos;
		}
	}

	void Starman::PlayFrames() noexcept {
		++(count);
		if (count >= (FPS_CAP / 3)) {
			++imgindex;
			imgindex &= 3;
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(frames[imgindex]);
			count = 0;
		}
	}

	void Starman::CheckCollision(void* gm) {
		if (m_Visible) {
			auto& fm = static_cast<MyAPP::GameManager*>(gm)->GetFormManger();
			auto& mario = fm.GetFormObject<Mario>(fm.GetNowForm(), "Mario");
			if (inRange(mario->GetPosition(), mario->GetSize())) {
				std::cout << "touch Starman\n";
				switch (mario->GetMario_type()) {
				case Mario::Mario_type::Mario:
					mario->changeType(Mario::Mario_type::InvincibleMario);
					break;
				case Mario::Mario_type::FieryMario:
					mario->changeType(Mario::Mario_type::InvincibleFieryMario);
					break;
				case Mario::Mario_type::SuperMario:
					mario->changeType(Mario::Mario_type::InvincibleSuperMario);
					break;
				default:
					break;
				}
				static_cast<MyAPP::GameManager*>(gm)->addPoint(1000);
				Points::UpdatePoint(fm, Points::PointType::pts1000);
				mario->setInvincible(FPS_CAP * 10);
				m_Visible = false;
			}
		}
	}
	void Starman::doDown() noexcept {
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
					MyPos.y = it->GetPosition().y + ((it->GetSize().y) /2) + ((MySize.y) /2);
					break;
				}
			}
			SetPosition(MyPos);
		}
	}

	void Starman::doJump() noexcept {
		if (UpDistance <= 0) {
			return;
		}
		auto tmp = GetSize().y / 16;
		UpDistance -= tmp;
		if (UpDistance <= 0) {
			UpDistance = 0;
		}
		m_Transform.translation.y += tmp;
	}
}
