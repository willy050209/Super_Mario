#include "Object/Brick/Brick.hpp"
namespace MyAPP {
	namespace Form {
		namespace Object {
			void Brick::behavior(void* data) {
				dojump();
				comeDown();
			}

			void Brick::bonk() noexcept {
				/*do something*/
				return;
			}

			void Brick::bonkJump() noexcept {
				if (jumpenable && state == State::null) {
					pos = GetPosition();
					state = State::jump;
					jumpcount = 10;
				}
			}

			void Brick::dojump() noexcept {
				if (state == State::jump) {
					// const auto Displacement = static_cast<unsigned>(GetSize().y) >> 4;
					incPositionY(static_cast<int>(GetSize().y) >> 4);
					jumpcount--;
					if (!jumpcount) {
						state = State::down;
					}
				}
			}

			void Brick::comeDown() noexcept {
				if (state == State::down) {
					// const auto Displacement = static_cast<unsigned>(GetSize().y) >> 4;
					if (GetPosition().y > pos.y) {
						incPositionY(-(static_cast<int>(GetSize().y) >> 4));
					}
					else {
						state = State::null;
						if (MyType != ObjectType::Brick) {
							jumpenable = false;
						}
					}
				}
			}
		}
	}
}