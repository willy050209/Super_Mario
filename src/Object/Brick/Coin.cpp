#include "Object/Brick/Coin.hpp"
#include "config.hpp"
#include "GameManager.hpp"

#include <memory>

void MyAPP::Form::Object::Coin::bonk() noexcept {
	if (play) {
		SetVisible(false);
		play = false;
		// std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(EmptyBlockImagePath);
	}
}

void MyAPP::Form::Object::Coin::behavior(void* data) {
	PlayFrames();
	CheckCollision(data);
}

void MyAPP::Form::Object::Coin::PlayFrames() noexcept {
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
void MyAPP::Form::Object::Coin::CheckCollision(void* data) noexcept {
	using namespace MyAPP::Form::Object;
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = (FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario"));
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	if (GetVisibility() && inRange(marioPos, marioSize)) {
		bonk();
		GM->addPoint(100);
		FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdatePointText")->Enable = true;
	}
}
