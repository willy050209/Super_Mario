#include "Object/Character/Character.hpp"
#include "Object/ImageObject.hpp"
#include "Object/Brick/Brick.hpp"

void MyAPP::Form::Object::Character::move() noexcept {
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
void MyAPP::Form::Object::Character::comeDown() noexcept {
	using MyAPP::Form::Object::Brick;
	auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
	auto MyPos = GetPosition();
	if (MyPos.y < WINDOW_HEIGHT) {
		const auto MySize = GetSize();
		MyPos.y -= DEFAULTDISPLACEMENT;
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(MyPos, MySize)) {
				if (it->getState() == Brick::State::jump) {
					died();
					MyPos = GetPosition();
					break;
				}
				MyPos.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
				break;
			}
		}
		SetPosition(MyPos);
	}
}

