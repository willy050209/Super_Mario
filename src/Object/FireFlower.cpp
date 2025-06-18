#include "Object/Props/FireFlower.hpp"
#include "config.hpp"
#include "GameManager.hpp"
#include <iostream>
namespace MyAPP:: Form:: Object::Props {

	void FireFlower::behavior(void* data) {
		PlayFrames();
		CheckCollision(data);
		doJump();
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
			auto GM = static_cast<GameManager*>(data);
			auto& fm = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
			auto mario = fm.GetFormObject<Mario>(fm.GetNowForm(), "Mario");
			if (inRange(mario->GetPosition(), mario->GetSize())) {
				mario->changeType(Mario::Mario_type::FieryMario);
				std::cout << "touch FireFlower\n";
				GM->sfx->LoadMedia(MyAPP::MyResourcesFilePath::Get_mashroo_fireflower);
				GM->sfx->Play(0);
				m_Visible = false;
			}
		}
	}
	void FireFlower::doJump() noexcept {
		if (UpDistance <= 0) {
			return;
		}
		auto tmp = GetSize().y / 16;
		UpDistance -= tmp;
		if (UpDistance <= 0) {
			UpDistance = 0;
		}
		m_Transform.translation.y += tmp;
	}
}
