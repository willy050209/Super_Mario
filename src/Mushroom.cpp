#include "Object/Props/Mushroom.hpp"
#include "GameManager.hpp"
#include <iostream>

void Mushroom::behavior(void* data) {
	touch(data);
}

void Mushroom::touch(void* gm) {
	if (m_Visible) {
		auto& fm = static_cast<GameManager*>(gm)->GetFormManger();
		auto& mario = fm.GetFormObject(fm.GetNowForm(), ObjectType::Mario, "Mario");
		if (inRange(mario->GetPosition(), mario->GetSize())) {
			std::cout << "touch Mushroom\n";
			m_Visible = false;
		}
	}
}
