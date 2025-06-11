#include "Object/Character/Turtle.hpp"
#include "config.hpp"
#include "ImageObject.hpp"
#include "GameManager.hpp"
#include "userType.hpp"

#include <memory>
#include <execution>
#include <algorithm>
namespace MyAPP::Form::Object {
	void Turtle::behavior(void* data) {
		if (!static_cast<MyAPP::GameManager*>(data)->pause) {
			if (moveFlag) {
				move();
			}
			ChangeImg();
			comeDown();
			CheckCollision(data);
		}
	}

	void Turtle::died() noexcept {
		diedFlag = true;
		switch (turtlecolor) {
		case MyAPP::Form::Object::Turtle::TurtleColor::Default:
			std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(TortoiseShell);
			break;
		case MyAPP::Form::Object::Turtle::TurtleColor::Dark:
			std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(DarkTortoiseShell);
			break;
		case MyAPP::Form::Object::Turtle::TurtleColor::Red:
			std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(RedTortoiseShell);
			break;
		default:
			break;
		}
	}

	void Turtle::move() noexcept {
		if (diedFlag) {
			auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
			bool flag = true;
			auto MyPos = GetPosition();
			if (MyPos.y < WINDOW_HEIGHT) {
				const auto MySize = GetSize();
				MyPos.x += (left == 1 ? -(getDEFAULTDISPLACEMENT() / 2) : getDEFAULTDISPLACEMENT() / 2);
				auto tmp = MyPos;
				tmp.y -= MySize.y;
				tmp.x += (left == 1 ? -getDEFAULTDISPLACEMENT() / 2 : getDEFAULTDISPLACEMENT() / 2);
				for (auto& it : *bricks) {
					if (it->collisionable && it->inRange(tmp, GetSize())) {
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
							moveFlag = false;
							return;
						}
					}
					SetPosition(MyPos);
				}
			}
		}
		else {
			auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
			bool flag = false;
			glm::vec2 pos = GetPosition() + glm::vec2{ GetSize().x * ((left == 1) ? -1 : 1), -GetSize().y };
			for (auto& it : *bricks) {
				if (it->collisionable && it->inRange(pos, GetSize())) {
					if (it->MyType == ObjectType::LeftEdge)
						continue;
					flag = true;
					break;
				}
			}
			if (!flag) {
				left ^= 1;
			}
			else {
				Character::move();
			}
		}
	}

	void Turtle::Reset() noexcept {
		Character::Reset();
		diedFlag = false;
		moveFlag = true;
	}


	void Turtle::ChangeImg() noexcept {
		if (!diedFlag) {
			imageChangeDelay++;
			if (imageChangeDelay >= (FPS_CAP / 3)) {
				imgIndex++;
				imgIndex &= 1;
				switch (turtlecolor) {
				case MyAPP::Form::Object::Turtle::TurtleColor::Default:
					std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage((left ? Frames[imgIndex] : imgs_r[imgIndex]));
					break;
				case MyAPP::Form::Object::Turtle::TurtleColor::Dark:
					std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage((left ? FramesDark[imgIndex] : darkimgs_r[imgIndex]));
					break;
				case MyAPP::Form::Object::Turtle::TurtleColor::Red:
					std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage((left ? FramesRed[imgIndex] : Redimgs_r[imgIndex]));
					break;
				default:
					break;
				}
				//std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage((left ? (dark ? FramesDark[imgIndex] : Frames[imgIndex]) : (dark ? darkimgs_r[imgIndex] : imgs_r[imgIndex])));
				imageChangeDelay = 0;
			}
		}
	}

	void Turtle::comeDown() noexcept {
		auto bricks = std::static_pointer_cast<BrickPtrVec>(userdata);
		bool flag = true;
		auto tmp = GetPosition();
		if (tmp.y < WINDOW_HEIGHT) {
			tmp.y -= getDEFAULTDISPLACEMENT();
			const auto MySize = GetSize();
			std::for_each(std::execution::seq, bricks->begin(), bricks->end(), [&](auto& it) {
				if (it->collisionable && it->inRange(tmp, MySize)) {
					if (it->getState() == Brick::State::jump) {
						died();
						tmp = GetPosition();
						// break;
					}
					flag = false;
					tmp.y = it->GetPosition().y + (it->GetSize().y) / 2 + (MySize.y /2);
					// break;
				}
			});
			SetPosition(tmp);
		}
	}
	void Turtle::CheckCollision(void* data) {
		using namespace MyAPP::Form::Object;
		auto GM = static_cast<MyAPP::GameManager*>(data);
		auto& FM = GM->GetFormManger();
		auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
		auto marioPos = mario->GetPosition();
		auto marioSize = mario->GetSize();
		if (!GM->opMode && mario->GetState() != Mario::State::DIED) {
			if (collisionable && mario->collisionable && inRange(marioPos, marioSize)) {
				if (diedFlag && GetVisibility() && inRange(marioPos, marioSize)) {
					if (GetPosition().x > marioPos.x) {
						SetLeft<false>();
						setMoveFlag(true);
					}
					else {
						SetLeft<true>();
						setMoveFlag(true);
					}
				}
				else if (mario->isInvincible() || (mario->GetState() == Mario::State::DOWN && mario->getBottom() >getBottom())) {
					died();
					switch (mario->jumpCobo) {
					case 0:
					case 1:
						GM->addPoint(100);
						Points::UpdatePoint(FM, Points::PointType::pts100);
						break;
					case 2:
						GM->addPoint(200);
						Points::UpdatePoint(FM, Points::PointType::pts200);
						break;
					case 3:
						GM->addPoint(400);
						Points::UpdatePoint(FM, Points::PointType::pts400);
						break;
					case 4:
						GM->addPoint(800);
						Points::UpdatePoint(FM, Points::PointType::pts800);
						break;
					case 5:
						GM->addPoint(1000);
						Points::UpdatePoint(FM, Points::PointType::pts1000);
						break;
					case 6:
						GM->addPoint(2000);
						Points::UpdatePoint(FM, Points::PointType::pts2000);
						break;
					case 7:
						GM->addPoint(4000);
						Points::UpdatePoint(FM, Points::PointType::pts4000);
						break;
					case 8:
						GM->addPoint(5000);
						Points::UpdatePoint(FM, Points::PointType::pts5000);
						break;
					default:
						GM->IncHP();
						Points::UpdatePoint(FM, Points::PointType::pts1up);
						break;
					}
					if (mario->GetState() == Mario::State::DOWN) {

						mario->jump(1.0);
					}
				}
				else if (mario->GetState() == Mario::State::UP) {
					return;
				}
				else {
					mario->died();
					if (mario->isdied()) {
						GM->LostALife();
					}
				}
			}
		}
	}
}