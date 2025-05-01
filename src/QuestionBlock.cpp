#include "Object/QuestionBlock.hpp"
#include "config.hpp"
#include <iostream>

void QuestionBlock::bonk() noexcept {
	if (play) {
		SetVisible(true);
		play = false;
		std::dynamic_pointer_cast<Util::Image>(GetDrawable())->SetImage(((blockState == EmptyBlockState::normal) ? EmptyBlockImagePath : EmptyBlockDarkImagePath));
	}
}

void QuestionBlock::behavior(void* data) {
	PlayGIF();
	dojump();
	comeDown();
}

void QuestionBlock::PlayGIF() noexcept {
	if (play) {
		++(count);
		if (count >= (FPS_CAP & 15)) {
			++imgindex;
			imgindex %= 6;
			std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(imgs[imgindex]);
			count = 0;
		}
	}
}
