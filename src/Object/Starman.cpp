#include "Object/Props/Starman.hpp"
//#include "Object/Mario.hpp"
#include "config.hpp"
#include "GameManager.hpp"

#include <iostream>
namespace MyAPP {
	namespace Form {
		namespace Object {
			namespace Props {
				void Starman::behavior(void* data) {
					PlayFrames();
					CheckCollision(data);
				}

				void Starman::PlayFrames() noexcept {
					++(count);
					if (count >= (FPS_CAP / 3)) {
						++imgindex;
						imgindex &= 3;
						std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(frames[imgindex]);
						count = 0;
					}
				}

				void Starman::CheckCollision(void* gm) {
					if (m_Visible) {
						auto& fm = static_cast<MyAPP::GameManager*>(gm)->GetFormManger();
						auto& mario = fm.GetFormObject<Mario>(fm.GetNowForm(), "Mario");
						if (inRange(mario->GetPosition(), mario->GetSize())) {
							std::cout << "touch Starman\n";
							// mario->changeType(Mario::Mario_type::SuperMario);
							mario->changeState(Mario::State::Invincible);
							m_Visible = false;
						}
					}
				}
			}
		}
	}
}