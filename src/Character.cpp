#include "Character.hpp"
#include "Object/ImageObject.hpp"

namespace MyAPP {
	namespace Form {
		namespace Object {
			// Character::Character(const std::string& ImagePath) {
			//    SetImage(ImagePath);
			//
			//    ResetPosition();
			//}
			//
			// void Character::SetImage(const std::string& ImagePath) noexcept {
			//    m_ImagePath = ImagePath;
			//
			//    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
			//}

			void Character::move() noexcept {
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
		}
	}
}