#include "Object/Props/Mushroom.hpp"
#include "GameManager.hpp"
#include <iostream>
namespace MyAPP {
	namespace Form {
		namespace Object {
			namespace Props {
				void Mushroom::behavior(void* data) {
					CheckCollision(data);
				}

				void Mushroom::CheckCollision(void* gm) {
					if (m_Visible) {
						auto& fm = static_cast<MyAPP::GameManager*>(gm)->GetFormManger();
						auto& mario = fm.GetFormObject<Mario>(fm.GetNowForm(), "Mario");
						if (inRange(mario->GetPosition(), mario->GetSize())) {
							switch (MyCategory) {
							case Mushroom::Category::Mushroom:
								std::cout << "touch Mushroom\n";
								break;
							case Mushroom::Category::MushroomDark:
								std::cout << "touch MushroomDark\n";
								break;
							case Mushroom::Category::BigMushroom:
								std::cout << "touch BigMushroom\n";
								break;
							default:
								break;
							}

							m_Visible = false;
						}
					}
				}
			}
		}
	}
}