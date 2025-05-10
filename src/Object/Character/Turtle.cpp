#include "Object/Character/Turtle.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"

#include <memory>
#include <execution>
#include <algorithm>
namespace MyAPP {
	namespace Form {
		namespace Object {
			void Turtle::behavior(void* data) {
				if (!static_cast<MyAPP::GameManager*>(data)->pause) {
					if (moveFlag) {
						move();
					}
					if (!static_cast<MyAPP::GameManager*>(data)->pause) {
						ChangeImg();

						comeDown();
					}
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
							imageChangeDelay = FPS_CAP;
							return;
						}
					}
					for (auto& it : *bricks) {
						if (it->collisionable && it->inRange(tmp, MySize)) {
							SetPosition(MyPos);
							return;
						}
					}
					if (diedFlag) {
						moveFlag = false;
					}
					else {
						left ^= 1;
						imageChangeDelay = FPS_CAP;
					}
				}
			}


			void Turtle::ChangeImg() noexcept {
				if (!diedFlag) {
					imageChangeDelay++;
					if (imageChangeDelay >= (FPS_CAP / 3)) {
						imgIndex++;
						imgIndex &= 1;
						std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage((left ? Frames[imgIndex] : imgs_r[imgIndex]));
						imageChangeDelay = 0;
					}
				}
			}

			void Turtle::comeDown() noexcept {
				auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(userdata);
				bool flag = true;
				auto tmp = GetPosition();
				if (tmp.y < WINDOW_HEIGHT) {
					tmp.y -= DEFAULTDISPLACEMENT;
					const auto MySize = GetSize();
					std::for_each(std::execution::par, bricks->begin(), bricks->end(), [&](auto& it) {
						if (it->collisionable && it->inRange(tmp, MySize)) {
							if (it->getState() == Brick::State::jump) {
								died();
								tmp = GetPosition();
								// break;
							}
							flag = false;
							tmp.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
							// break;
						}
					});
					// for (auto& it : *bricks) {
					//	if (it->collisionable && it->inRange(tmp, MySize)) {
					//		if (it->collisionable && it->inRange(tmp, MySize)) {
					//			if (it->getState() == Brick::State::jump) {
					//				died();
					//				tmp = GetPosition();
					//				break;
					//			}
					//			flag = false;
					//			tmp.y = it->GetPosition().y + (static_cast<int>(it->GetSize().y) >> 1) + (static_cast<int>(MySize.y) >> 1);
					//			//break;
					//		}
					//	}
					// }
					SetPosition(tmp);
				}
			}
		}
	}
}