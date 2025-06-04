#include "Object/Character/Goomba.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"

#include <memory>
#include <execution>
#include <algorithm>
namespace MyAPP::Form:: Object {
	void Goomba::behavior(void* data) {
		if (!static_cast<MyAPP::GameManager*>(data)->pause) {
			ChangeImg();
			move();
			comeDown();
			CheckCollision(data);
		}
	}

	void Goomba::died() noexcept {
		collisionable = false;
		m_Visible = false;
	}


	void Goomba::ChangeImg() noexcept {
		imageChangeDelay++;
		if (imageChangeDelay >= (FPS_CAP / 3)) {
			imgIndex++;
			imgIndex &= 1;
			std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage((dark)?FramesDark[imgIndex]:Frames[imgIndex]);
			imageChangeDelay = 0;
		}
	}

	/*void Goomba::comeDown() noexcept {
		auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
		bool flag = true;
		auto tmp = GetPosition();
		if (tmp.y < WINDOW_HEIGHT) {
			tmp.y -= DEFAULTDISPLACEMENT;
			const auto MySize = GetSize();
			std::for_each(std::execution::seq, bricks->begin(), bricks->end(), [&](auto& it) {
				if (it->collisionable && it->inRange(tmp, MySize)) {
					if (it->getState() == Brick::State::jump) {
						died();
						tmp = GetPosition();
					}
					flag = false;
					tmp.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
				}
			});
			SetPosition(tmp);
		}
	}*/
}


void MyAPP::Form::Object::Goomba::CheckCollision(void* data) {
	using namespace MyAPP::Form::Object;
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	if (!GM->opMode && mario->GetState() != Mario::State::DIED) {
		if (collisionable && mario->collisionable && inRange(marioPos, marioSize)) {
			if (mario->isInvincible() || mario->GetState() == Mario::State::DOWN || mario->GetState() == Mario::State::UP) {
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
				if (mario->GetState() == Mario::State::DOWN) {

					mario->jump(1.0);
				}
			}
			else {
				mario->died();
				if (!mario->isInvincible()) {
					GM->LostALife();
				}
			}
		}
	}
}