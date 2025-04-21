#include "Turtle.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"

#include <memory>

void Turtle::behavior(void* data) {
	if (moveFlag) {
		move();
	}
	if (!static_cast<GameManager*>(data)->pause) {
		ChangeImg();
		
		comeDown();
	}
}

void Turtle::died() noexcept {
	diedFlag = true;
	std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(TortoiseShell[0]);
}

void Turtle::move() noexcept {
	auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(userdata);
	bool flag = true;
	auto MyPos = GetPosition();
	if (MyPos.y < WINDOW_HEIGHT) {
		const auto MySize = GetSize();
		MyPos.x += (left == 1 ? -(((int)MySize.x) >> 4) : (((int)MySize.x) >> 4));
		auto tmp = MyPos;
		tmp.y -= MySize.y;
		tmp.x += (left == 1 ? -((int)MySize.x) >> 1 : ((int)MySize.x) >> 1);
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(MyPos, MySize)) {
				if (diedFlag) {
					moveFlag = false;
					return;
				}
				left ^= 1;
				return;
			}
		}
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(tmp, MySize)) {
				SetPosition(MyPos);
				return;
			}
		}
		left ^= 1;
	}
}


void Turtle::ChangeImg() noexcept {
	if (!diedFlag) {
		imageChangeDelay++;
		if (imageChangeDelay >= (FPS_CAP & 15)) {
			imgIndex++;
			imgIndex &= 1;
			std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage((left ? imgs[imgIndex] : imgs_r[imgIndex]));
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
				tmp.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
				break;
			}
		}
		SetPosition(tmp);
	}
}