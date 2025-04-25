#include "Goomba.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"

#include <memory>

void Goomba::behavior(void* data) {
	if (!static_cast<GameManager*>(data)->pause) {
		ChangeImg();
		move();
		comeDown();
	}
}

void Goomba::died() noexcept {
	collisionable = false;
	m_Visible = false;
}


void Goomba::ChangeImg() noexcept {
	imageChangeDelay++;
	if (imageChangeDelay >= (FPS_CAP & 15)) {
		imgIndex++;
		imgIndex &= 1;
		std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(imgs[imgIndex]);
		imageChangeDelay = 0;
	}
}

void Goomba::comeDown() noexcept {
	auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
	bool flag = true;
	auto tmp = GetPosition();
	if ( tmp.y < WINDOW_HEIGHT) {
		tmp.y -= DEFAULTDISPLACEMENT;
		const auto MySize = GetSize();
		for (auto& it : *bricks) {
			if (it->getState() == Brick::State::jump) {
				died();
				break;
			}
			else if (it->collisionable && it->inRange(tmp, MySize)) {
				flag = false;
				tmp.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
				break;
			}
		}
		SetPosition(tmp);
	}
}

