#include "Object/Props/FireFlower.hpp"
#include "config.hpp"
#include "GameManager.hpp"
#include <iostream>

void FireFlower::behavior(void* data) {
	playFrames();
	touch(data);
}

void FireFlower::playFrames() {
	++(count);
	if (count >= (FPS_CAP / 3)) {
		++imgindex;
		imgindex &= 3;
		std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(frames[imgindex]);
		count = 0;
	}
}

void FireFlower::touch(void* gm) {
	if (m_Visible) {
		auto& fm = static_cast<GameManager*>(gm)->GetFormManger();
		auto& mario = std::static_pointer_cast<Mario>(fm.GetFormObject(fm.GetNowForm(), ObjectType::Mario, "Mario"));
		if (inRange(mario->GetPosition(), mario->GetSize())) {
			mario->changeType(Mario::Mario_type::FieryMario);
			std::cout << "touch FireFlower\n";
			m_Visible = false;
		}
	}
}
