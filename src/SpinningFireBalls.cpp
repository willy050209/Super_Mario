#include "SpinningFireBalls.hpp"
#include "config.hpp"

void MyAPP::Form::Object::SpinningFireBalls::bonk() noexcept {
}

void MyAPP::Form::Object::SpinningFireBalls::behavior(void* data) {
	PlayGIF();
}

void MyAPP::Form::Object::SpinningFireBalls::PlayGIF() noexcept {
	if (play) {
		++(count);
		if (count >= (3)) {
			++imgindex;
			imgindex %= 103;
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(GetFrame());
			count = 0;
		}
	}
}
