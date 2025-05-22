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
			std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(Frames[imgIndex]);
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
		if (collisionable && inRange(marioPos, marioSize)) {
			if (mario->isInvincible() || mario->GetState() == Mario::State::DOWN || mario->GetState() == Mario::State::UP) {
				died();
			}
			else {
				GM->DecHP();
				mario->died();
				GM->bgm->Pause();
				GM->sfx->LoadMedia(MyAPP::MyResourcesFilePath::Lost_a_Life);
				GM->sfx->Play(0);
				(FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdateHPText"))->Enable = true;
				if (GM->GetHP() == 0) {
					GM->bgm->LoadMedia(MyAPP::MyResourcesFilePath::Game_Over);
					auto sleepevent = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "SleepAllevent"));
					sleepevent->Enable = true;
					sleepevent->userdata.reset();
					sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP * 3, std::vector<bool>());
					(FM.GetFormObject<EventObject>(FM.GetNowForm(), "FinifhEvent"))->Enable = true;
				}
				else {
					(FM.GetFormObject<EventObject>(FM.GetNowForm(), "GoBackCheckPoint"))->Enable = true;
					auto sleepevent = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "SleepAllevent"));
					sleepevent->Enable = true;
					sleepevent->userdata.reset();
					sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP, std::vector<bool>());
				}
			}
		}
	}
}