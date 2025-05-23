#include "Object/Props/FireFlower.hpp"
#include "config.hpp"
#include "GameManager.hpp"
#include <iostream>
namespace MyAPP {
	namespace Form {
		namespace Object {
			namespace Props {
				void FireFlower::behavior(void* data) {
					PlayFrames();
					CheckCollision(data);
				}

				void FireFlower::PlayFrames() noexcept {
					++(count);
					if (count >= (FPS_CAP / 3)) {
						++imgindex;
						imgindex &= 3;
						std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(frames[imgindex]);
						count = 0;
					}
				}

				void FireFlower::CheckCollision(void* data) {
					if (m_Visible) {
						auto& fm = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
						auto& mario = fm.GetFormObject<Mario>(fm.GetNowForm(), "Mario");
						if (inRange(mario->GetPosition(), mario->GetSize())) {
							mario->changeType(Mario::Mario_type::FieryMario);
							std::cout << "touch FireFlower\n";
							m_Visible = false;
						}
					}
				}
			}
		}
	}
}