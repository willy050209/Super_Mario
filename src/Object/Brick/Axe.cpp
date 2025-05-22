#include "Object/Brick/Axe.hpp"
#include "Util/Image.hpp"
#include "config.hpp"
#include "GameManager.hpp"

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
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
}
