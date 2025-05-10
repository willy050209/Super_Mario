#include "Object/Brick/SpinningFireBalls.hpp"
#include "Object/Brick/FireBall.hpp"
#include "config.hpp"
#include <memory>
#include <cmath>
#include <algorithm>
#include <execution>


void MyAPP::Form::Object::SpinningFireBalls::behavior(void* data) {
	PlayFrames();
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
	std::for_each(std::execution::par, vecptr->begin(), vecptr->end(), [&](auto& it) {
		glm::vec2 pos{ 0, 0 };
		auto i = std::find(vecptr->begin(), vecptr->end(), it) - vecptr->begin();
		pos.x = thispos.x + std::cos(static_cast<double>(imgindex) / Last_Frame * 2 * PI - (PI / 2)) * i * it->GetSize().x;
		pos.y = thispos.y + std::sin(static_cast<double>(imgindex) / Last_Frame * 2 * PI - (PI / 2)) * i * it->GetSize().y;
		(it)->SetPosition(pos);
	});
}


