#include "Object/Character/Koopa.hpp"
#include "config.hpp"

void MyAPP::Form::Object::Koopa::behavior(void* data) {
	move();
	comeDown();
	CheckCollision(data);
}

void MyAPP::Form::Object::Koopa::died() noexcept {
}

void MyAPP::Form::Object::Koopa::move() noexcept {
}

void MyAPP::Form::Object::Koopa::checkPosition() noexcept {
	if (std::abs(GetPosition().y) > WINDOW_HEIGHT/2) {
		died();
	}
}

void MyAPP::Form::Object::Koopa::CheckCollision(void* data) {
}
