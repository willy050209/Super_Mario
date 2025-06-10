#include "Object/Character/Character.hpp"
#include "Object/ImageObject.hpp"
#include "Object/Brick/Brick.hpp"

void MyAPP::Form::Object::Character::move() noexcept {
	auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(userdata);
	auto MyPos = GetPosition();
	auto tmp = MyPos - glm::vec2{ 0, GetSize().y / 2 };
	bool flag = false;
	for (auto& it : *bricks) {
		if (it->collisionable && it->inRange(tmp, GetSize())) {
			using MyAPP::Form::Object::ObjectType;
			if (it->MyType == ObjectType::LeftEdge)
				continue;
			flag = true;
			break;
		}
	}
	if (MyPos.y < WINDOW_HEIGHT && flag) {
		const auto MySize = GetSize();
		MyPos.x += (left == 1 ? -getDEFAULTDISPLACEMENT() / 2 : getDEFAULTDISPLACEMENT() / 2);
		for (auto& it : *bricks) {
			if (it->collisionable && it->inRange(MyPos, MySize)) {
				if (it->MyType == ObjectType::LeftEdge)
					continue;
				left ^= 1;
				return;
			}
		}
		SetPosition(MyPos);
	}
}
void MyAPP::Form::Object::Character::comeDown() noexcept {
	using MyAPP::Form::Object::Brick;
	auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
	auto MyPos = GetPosition();
	if (MyPos.y < WINDOW_HEIGHT) {
		const auto MySize = GetSize();
		MyPos.y -= getDEFAULTDISPLACEMENT();
		for (auto& it : *bricks) {
			if (it->MyType == ObjectType::LeftEdge)
				continue;
			if (it->collisionable && it->inRange(MyPos, MySize)) {
				if (it->getState() == Brick::State::jump) {
					died();
					MyPos = GetPosition();
					break;
				}
				MyPos.y = it->GetPosition().y + ((it->GetSize().y) /2) + ((MySize.y) /2);
				break;
			}
		}
		SetPosition(MyPos);
	}
}

