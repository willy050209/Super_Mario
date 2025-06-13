#include "Object/Brick/Axe.hpp"
#include "Util/Image.hpp"
#include "config.hpp"
#include "GameManager.hpp"
#include "Object/ImageObject.hpp"

#include <thread>

void MyAPP::Form::Object::Axe::behavior(void* data) {
	PlayFrames();
	CheckCollision(data);
}

void MyAPP::Form::Object::Axe::PlayFrames() noexcept {
	if (play) {
		++(count);
		if (count >= (FPS_CAP / 5)) {
			++imgindex;
			imgindex %= 6;
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(Frames[imgindex]);
			count = 0;
		}
	}
}

void MyAPP::Form::Object::Axe::CheckCollision(void* data) noexcept {
	using namespace MyAPP::Form::Object;
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto& imgs = FM.GetFormAndObject(FM.GetNowForm()).m_Images;
	auto GetBriges = [&]() -> std::vector<std::shared_ptr<ImageObject>> {
		std::vector<std::shared_ptr<ImageObject>> Briges;
		std::copy_if(imgs.begin(), imgs.end(), std::back_inserter(Briges), [](auto& it) {
			return it->MyType == ObjectType::Bridge;
		});
		std::reverse(Briges.begin(), Briges.end());
		return Briges;
	};
	if (inRange(mario->GetPosition(),mario->GetSize()) && enable && mario->GetState() == Mario::State::MOVE) {
		auto flag = true;
		auto Briges = GetBriges();
		if (auto moveEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent")) {
			moveEvent->Enable = false;
		}
		mario->collisionable = false;
		for (auto& it : Briges) {
			it->SetVisible(false);
			it->collisionable = false;
			flag = false;
			FM.removeObject<Bridge>(FM.GetNowForm(), it->m_ID);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			break;
		}
		if (flag) {
			mario->SetLeft<false>();
			if (auto gotodoor = FM.GetFormObject<EventObject>(FM.GetNowForm(), "moveToDoor")) {
				gotodoor->Enable = true;
			}
			enable = false;
			if (auto koopa = FM.GetFormObject<Koopa>(FM.GetNowForm(), "Koopa")) {
				koopa->kill();
			}
		}
		else {
			if (auto koopa = FM.GetFormObject<Koopa>(FM.GetNowForm(), "Koopa")) {
				koopa->SetEnable(false);
			}
		}
		mario->setInvincible(2147483647);
	}
}
