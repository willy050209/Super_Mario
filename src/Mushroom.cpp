#include "Object/Props/Mushroom.hpp"
#include "GameManager.hpp"
#include <iostream>

void Mushroom::behavior(void* data) {
	touch(data);
}

void Mushroom::touch(void* gm) {
	if (m_Visible) {
		auto& fm = static_cast<GameManager*>(gm)->GetFormManger();
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
