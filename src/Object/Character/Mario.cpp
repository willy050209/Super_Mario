#include "Object/Character/Mario.hpp"
#include "Object/ImageObject.hpp"
#include "Util/Input.hpp"
#include "config.hpp"
#include "FilePath.hpp"
#include "GameManager.hpp"
#include <execution>
#include <iostream>

namespace MyAPP::Form::Object {

	void Mario::jump(float d) noexcept {
		state = State::UP;
		displacement = WINDOW_HEIGHT / 15.f * d / 18;
		index = 0;
		jumpcount = 18;
		changeImg();
		jumpCobo++;
	}

	void Mario::behavior(void* data) {
		if (!static_cast<MyAPP::GameManager*>(data)->opMode) {
			comeDown();
			doJump();
			checkInvincible();
			shoot(data);
			static_cast<MyAPP::GameManager*>(data)->mariotype = mario_type;
		}
	}

	void Mario::doJump() noexcept {
		if (jumpcount > 0 && (state == State::UP || (state == State::DIED && !diedflag))) {
			auto tmp = GetPosition();
			auto blocks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
			auto tmp1 = tmp.y += displacement;
			if (state != State::DIED) {
				std::for_each(std::execution::seq, blocks->begin(), blocks->end(), [&](std::shared_ptr<Brick> it) {
					if ((it)->collisionable && (it)->inRange(tmp, GetSize())) {

						tmp1 = (it)->GetPosition().y - (static_cast<int>((it)->GetSize().y) >> 1) - (static_cast<int>(GetSize().y) >> 1);
						auto tmp2 = GetSize();
						tmp2.x *= 0.75f;
						if (it->inRange(tmp,tmp2)) {
							(it)->bonk();
							(it)->bonkJump();
						}
						displacement = 0;
						if ((mario_type == Mario_type::SuperMario ||
							mario_type == Mario_type::InvincibleSuperMario ||
							mario_type == Mario_type::FieryMario ||
							mario_type == Mario_type::InvincibleFieryMario) &&
							it->MyType == ObjectType::Brick) {
							it->collisionable = false;
							it->SetVisible(false);	
						}
					}
				});
			}
			tmp.y = tmp1;
			SetPosition(tmp);
			jumpcount--;
			if (jumpcount == 0) {
				if (state != State::DIED)
					state = State::DOWN;
				else
					diedflag = true;
				index = 0;
				displacement = DEFAULTDISPLACEMENT;
			}
		}
	}

	void Mario::comeDown() noexcept {
		auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
		bool flag = true;
		auto tmp = GetPosition();
		if (diedflag && state == State::DIED) {
			tmp.y -= displacement * 2;
			SetPosition(tmp);
		}
		else if (state != State::UP && state != State::DIED && tmp.y < WINDOW_HEIGHT) {
			tmp.y -= displacement * 2;
			const auto MySize = GetSize();
			for (auto& it : *bricks) {
				if (it->collisionable && it->inRange(tmp, MySize)) {
					flag = false;
					tmp.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
					break;
				}
			}
			SetPosition(tmp);
			if (flag) {
				state = State::DOWN;
			}
			else {
				if (state != State::MOVE) {
					if (state == State::UP)
						index = 0;
					state = State::MOVE;
					changeImg();
					jumpCobo = 0;
				}
			}
		}
	}

	void Mario::checkInvincible() noexcept {
		if (invincibleCount > 0) {
			invincibleCount--;
			switch (mario_type) {
			case MyAPP::Form::Object::Mario::Mario_type::InvincibleMario:
			case MyAPP::Form::Object::Mario::Mario_type::InvincibleSuperMario:
			case MyAPP::Form::Object::Mario::Mario_type::InvincibleFieryMario:
				move();
				break;
			default:
				break;
			}
		}
		else {
			collisionable = true;
			switch (mario_type) {
			case MyAPP::Form::Object::Mario::Mario_type::InvincibleMario:
				changeType(Mario_type::Mario);
				index++;
				changeImg();
				break;
			case MyAPP::Form::Object::Mario::Mario_type::InvincibleSuperMario:
				changeType(Mario_type::SuperMario);
				index++;
				changeImg();
				break;
			case MyAPP::Form::Object::Mario::Mario_type::InvincibleFieryMario:
				changeType(Mario_type::FieryMario);
				index++;
				changeImg();
				break;
			default:
				break;
			}
		}
	}

	void Mario::shoot(void* data) noexcept {
		if (shootFireTrigger) {
			auto GM = static_cast<MyAPP::GameManager*>(data);
			auto& FM = GM->GetFormManger();
			Fire::CreateFire(FM);
			shootFireTrigger = false;
		}
	}



	void Mario::changeImg() noexcept {
		index %= imgs[mario_type][state][left].size();
		std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(imgs[mario_type][state][left][index]);
	}

	void Mario::move() noexcept {
		imgChangeDelay++;
		if (imgChangeDelay >= 10) {
			index++;
			// index %= imgs[state][left].size();
			changeImg();
			imgChangeDelay = 0;
		}
	}

	void Mario::died() noexcept {
		if (isBigMario()) {
			if (mario_type == Mario_type::FieryMario || mario_type == Mario_type::SuperMario) {
				state = State::MOVE;
				mario_type = Mario_type::Mario;
				invincibleCount = FPS_CAP * 2;
				collisionable = false;
			}
		}
		else {
			state = State::DIED;
			displacement = 2.5 * DEFAULTDISPLACEMENT;
			jumpcount = 10;
		}
		index = 0;
		changeImg();
	}

	void Fire::behavior(void* data) {
		double multiple = ((float)WINDOW_HEIGHT / 480);
		this->CheckCollision(data);
		this->Move({ (left) ? -1 * multiple : multiple * 1, yposition });
	}

	void Fire::CreateFire(MyAPP::Form::FormManger& FM) noexcept {
		double multiple = ((float)WINDOW_HEIGHT / 480);
		static size_t fireCount{ 0 }; // 火球計數器
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		auto moveEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
		auto fire = std::make_shared<Fire>("Fire", 20);
		if (mario && moveEvent && fire) {
			auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveEvent->userdata);
			auto& [enemys, pipes, props, objs] = (*tuplePtr);
			if (tuplePtr == nullptr)
				return;
			fire->left = mario->isLeft();
			if (fire->left) {
				fire->SetPosition(mario->GetPosition() - glm::vec2(fire->GetSize().x, 0));
			}
			else {
				fire->SetPosition(mario->GetPosition() + glm::vec2(fire->GetSize().x, 0));
			}
			fire->yposition = mario->GetPosition().y + 30 * multiple;
			fire->xposition = mario->GetPosition().x;
			fire->my_standar = fire->xposition + 16 * multiple + WINDOW_WIDTH / 2;
			fire->distance_y = 62 * multiple - fire->yposition;
			fire->touch_ground = false;
			FM.addObject(FM.GetNowForm(), fire);
			objs->push_back(std::move(fire));
		}
	}

	void Fire::Move(const glm::vec2& distance) noexcept {
		double multiple = ((float)WINDOW_HEIGHT / 480);

		m_Transform.translation.x += distance.x;

		float currentX = m_Transform.translation.x + WINDOW_WIDTH/2 - my_standar;
		//std::cout << currentX << ' ' << m_Transform.translation.x << '\n';
		if (!touch_ground) {
			m_Transform.translation.y = (-62.0f / 32.0f) * currentX + 62.0f - distance_y;
			//std::cout << currentX << ' ' << m_Transform.translation.x << '\n';
		}
		else  {
			// 實作半圓波形
			//m_Transform.translation.y = yposition;
			//float term = (currentX - 112.0f) / 80.0f;
			//m_Transform.translation.y = 32.0f * std::sqrt(1.0f - (term * term));
		}
		/*else {
			m_Transform.translation.y = 0.0f;
		}*/
		/* static const float PI = std::acos(-1);
		static constexpr auto frequency = 0.4f; // Frequency of the sine wave
		m_Transform.translation.x += distance.x;
		m_Transform.translation.y = GetSize().y * std::sin(2 * PI * frequency * angle) + distance.y;
		angle += 0.055f; // Adjust the angle increment as needed for the desired arc effect*/
	}


	void Fire::CheckCollision(void* data) {
		auto GM = static_cast<GameManager*>(data);
		auto& FM = GM->GetFormManger();
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		auto moveEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
		if (mario == nullptr || moveEvent == nullptr)
			return;
		auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveEvent->userdata);
		auto& [enemys, pipes, props, objs] = (*tuplePtr);
		if (tuplePtr == nullptr)
			return;

		auto remove_fire_image = [&]() {
			FM.removeObject<Fire>(FM.GetNowForm(), m_ID);
			objs->erase(std::remove_if(objs->begin(), objs->end(), [&](const ObjectPtr& obj) {
				return obj->m_ID == m_ID;
			}),
				objs->end());
			};
		for (auto& it : *enemys) {
			if (it->collisionable && it->inRange(GetPosition(), GetSize())) {
				it->died();
				if (it->MyType == ObjectType::Turtle) {
					it->collisionable = false;
					it->SetVisible(false);
					GM->addPoint(200);
					Points::UpdatePoint(FM, Points::PointType::pts200);
				}
				else {
					GM->addPoint(100);
					Points::UpdatePoint(FM, Points::PointType::pts100);
				}
				remove_fire_image();
				return;
			}
		}
		for (auto& it : *std::static_pointer_cast<BrickPtrVec>(mario->userdata)) {
			if (it->collisionable && it->inRange(GetPosition(), GetSize())) {
				remove_fire_image();
				return;
			}
		}
	}


}
