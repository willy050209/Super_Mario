#include "Object/Brick/FireBall.hpp"
#include "Object/Character/Mario.hpp"
#include "GameManager.hpp"
#include "config.hpp"

#include <iostream>

void MyAPP::Form::Object::FireBalls::behavior(void* data) {
	CheckCollision(data);
}

void MyAPP::Form::Object::FireBalls::CheckCollision(void* data) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	if (!mario->isInvincible() && !GM->opMode) {
		if (inRange(mario->GetPosition(), mario->GetSize())) {
			mario->died();
			if (!mario->isInvincible()) {
				GM->LostALife();
			}
		}
	}
}
