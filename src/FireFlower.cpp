#include "Object/Props/FireFlower.hpp"
#include "config.hpp"

void FireFlower::behavior(void* data) {
	playFrames();
	touch(data);
}

void FireFlower::playFrames() {
	++(count);
	if (count >= (FPS_CAP & 31)) {
		++imgindex;
		imgindex &= 3;
		std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(frames[imgindex]);
		count = 0;
	}
}

void FireFlower::touch(void* gm) {
}
