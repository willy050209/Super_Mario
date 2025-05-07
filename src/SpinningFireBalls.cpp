#include "SpinningFireBalls.hpp"
#include "FireBall.hpp"
#include "config.hpp"
#include <memory>
#include <cmath>
#include <algorithm>
#include <execution>


void MyAPP::Form::Object::SpinningFireBalls::behavior(void* data) {
	PlayGIF();
	//moveFrieBalls();
}


void MyAPP::Form::Object::SpinningFireBalls::PlayGIF() noexcept {
	if (std::abs(GetPosition().x) <= WINDOW_WIDTH  && std::abs(GetPosition().y) <= WINDOW_HEIGHT ) {
		if (play) {
			++(count);
			if (count >= (3)) {
				++imgindex;
				imgindex %= 103;
				std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage(GetFrame());
				moveFrieBalls();
				count = 0;
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
		pos.x = thispos.x + std::cos(static_cast<double>(imgindex) / 103. * 2 * PI - (PI / 2)) * i * it->GetSize().x;
		pos.y = thispos.y + std::sin(static_cast<double>(imgindex) / 103. * 2 * PI - (PI / 2)) * i * it->GetSize().y;
		(it)->SetPosition(pos);
	});
}

[[nodiscard]] std::shared_ptr<MyAPP::Form::Object::SpinningFireBalls> MyAPP::Form::Object::SpinningFireBalls::make_SpinningFireBalls(const std::string& name, int zindex) noexcept {
	auto result = std::make_shared<SpinningFireBalls>(name, zindex);
	std::vector<std::shared_ptr<FireBalls>> fireballs;
	for (int i = 0; i < 6; ++i) {
		fireballs.push_back(std::make_shared<FireBalls>("", 0));
	}
	result->userdata = std::make_shared<std::vector<std::shared_ptr<FireBalls>>>(fireballs);
	return result;
}

