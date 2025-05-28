#include "Object/Character/Koopa.hpp"
#include "Object/Character/MArio.hpp"
#include "GameManager.hpp"
#include "FilePath.hpp"
#include "config.hpp"
#include <iostream>

void MyAPP::Form::Object::Koopa::behavior(void* data) {
	move();
	comeDown();
	CheckCollision(data);
	checkPosition();
	PlayFrames();
}

void MyAPP::Form::Object::Koopa::died() noexcept {
	std::cout << "Koopa died" << std::endl;
}

void MyAPP::Form::Object::Koopa::move() noexcept {
}

void MyAPP::Form::Object::Koopa::checkPosition() noexcept {
	if (std::abs(GetPosition().y) > WINDOW_HEIGHT/2) {
		died();
	}
}

void MyAPP::Form::Object::Koopa::CheckCollision(void* data) {
	using namespace MyAPP::Form::Object;
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	if (!GM->opMode && mario->GetState() != Mario::State::DIED) {
		if (collisionable && inRange(marioPos, marioSize)) {
			mario->died();
			GM->LostALife();
		}
	}
}

void MyAPP::Form::Object::Koopa::PlayFrames() noexcept {
	imageChangeDelay++;
	if (imageChangeDelay >= (FPS_CAP / 3)) {
		imgIndex++;
		imgIndex &= 1;
		std::static_pointer_cast<Util::Image>(m_Drawable)->SetImage(GetFrame());
		imageChangeDelay = 0;
	}
}
