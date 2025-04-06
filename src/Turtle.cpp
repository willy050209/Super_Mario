#include "Turtle.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"

#include <memory>

void Turtle::behavior(void* data) {
	if (!static_cast<GameManager*>(data)->pause) {
		ChangeImg();
		comeDown();
	}
}

void Turtle::died() noexcept {
	diedFlag = true;
	std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(TortoiseShell[0]);
}


void Turtle::ChangeImg() noexcept {
	if (!diedFlag) {
		imageChangeDelay++;
		if (imageChangeDelay >= FPS_CAP / 6) {
			imgIndex++;
			imgIndex &= 1;
			std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(imgs[imgIndex]);
			imageChangeDelay = 0;
		}
	}
}

void Turtle::comeDown() noexcept {
	auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(userdata);
	bool flag = true;
	auto tmp = GetPosition();
	if (tmp.y < WINDOW_HEIGHT) {
		tmp.y -= DEFAULTDISPLACEMENT;
		const auto MySize = GetSize();
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(tmp, MySize)) {
				flag = false;
				tmp.y = it->GetPosition().y + it->GetSize().y / 2 + MySize.y / 2;
				break;
			}
		}
		SetPosition(tmp);
	}
}