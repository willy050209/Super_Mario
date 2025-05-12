#include "Object/Brick/SpinningFireBalls.hpp"
#include "Object/Brick/FireBall.hpp"
#include "config.hpp"
#include "GameManager.hpp"
#include "Position.hpp"
#include <memory>
#include <cmath>
#include <algorithm>
#include <execution>


void MyAPP::Form::Object::SpinningFireBalls::behavior(void* data) {
	if (!static_cast<MyAPP::GameManager*>(data)->pause && inWindows(this)) {
		PlayFrames();
		auto vecptr = std::static_pointer_cast<std::vector<std::shared_ptr<FireBalls>>>(userdata);
		auto& thispos = GetPosition();
		std::for_each(vecptr->begin(), vecptr->end(), [&](auto& it) {
			it->behavior(data);
		});
	}
	//moveFrieBalls();
}


void MyAPP::Form::Object::SpinningFireBalls::PlayFrames() noexcept {
	if (std::abs(GetPosition().x) <= WINDOW_WIDTH  && std::abs(GetPosition().y) <= WINDOW_HEIGHT ) {
		if (play) {
			++(Frame_count);
			if (Frame_count >= (3)) {
				++imgindex;
				imgindex %= Last_Frame;
				std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(GetFrame());
				moveFrieBalls();
				Frame_count = 0;
			}
		}
	}
}

void MyAPP::Form::Object::SpinningFireBalls::moveFrieBalls() noexcept {
	
	auto vecptr = std::static_pointer_cast<std::vector<std::shared_ptr<FireBalls>>>(userdata);
	auto& thispos = GetPosition();
	auto i = 0;
	std::for_each(std::execution::seq, vecptr->begin(), vecptr->end(), [&](auto& it) {
		glm::vec2 pos{ 0, 0 };
		pos.x = thispos.x + std::cos(static_cast<double>(imgindex) / Last_Frame * 2 * PI - (PI / 2)) * i * it->GetSize().x;
		pos.y = thispos.y + std::sin(static_cast<double>(imgindex) / Last_Frame * 2 * PI - (PI / 2)) * i * it->GetSize().y;
		(it)->SetPosition(pos);
		++i;
	});
}


