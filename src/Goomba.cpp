#include "Goomba.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"

#include <memory>

void Goomba::behavior(void* data) {
	if (!static_cast<GameManager*>(data)->pause) {
		ChangeImg();
		comeDown();
	}
}


void Goomba::ChangeImg() noexcept {
	imageChangeDelay++;
	if (imageChangeDelay >= FPS_CAP / 6) {
		imgIndex++;
		imgIndex &= 1;
		std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(imgs[imgIndex]);
		imageChangeDelay = 0;
	}
}

void Goomba::comeDown() {
	auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(userdata);
	bool flag = true;
	auto tmp = GetPosition();
	if ( tmp.y < WINDOW_HEIGHT) {
		tmp.y -= DEFAULTDISPLACEMENT;
		const auto aaa = GetSize();
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(tmp, aaa)) {
				flag = false;
				tmp.y = it->GetPosition().y + it->GetSize().y;
				break;
			}
		}
		SetPosition(tmp);
	}
}
