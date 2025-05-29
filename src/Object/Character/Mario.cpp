#include "Object/Character/Mario.hpp"
#include "Object/ImageObject.hpp"
#include "Util/Input.hpp"
#include "config.hpp"
#include "FilePath.hpp"
#include "GameManager.hpp"
#include <execution>

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
		if (!static_cast<MyAPP::GameManager*>(data)->pause && !static_cast<MyAPP::GameManager*>(data)->opMode) {
			// move();
			comeDown();
			doJump();
			// if (state != State::DIED)
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
						(it)->bonk();
						(it)->bonkJump();
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
		state = State::DIED;
		displacement = 2.5 * DEFAULTDISPLACEMENT;
		index = 0;
		// jumpDelay = 0;
		jumpcount = 10;
		changeImg();

		// state = State::UP;
	}

	// void Mario::changeType(Mario_type type_) noexcept {
	//	mario_type = type_;
	//	changeImg();
	// }

	// void Mario::isInvincible(bool flag) noexcept {
	//	if (flag)
	//		mario_invincible = State::Invincible;
	//	else
	//		mario_invincible = State::MOVE;
	//	changeImg();
	// }
}
