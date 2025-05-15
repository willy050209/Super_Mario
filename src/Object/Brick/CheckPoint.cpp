#include "Object/Brick/CheckPoint.hpp"
#include "GameManager.hpp"

void MyAPP::Form::Object::CheckPoint::behavior(void* data) {
	CheckCollision(data);
}

void MyAPP::Form::Object::CheckPoint::CheckCollision(void* data) {
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto background = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "Background");
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	auto pos = background->GetPosition();
	if (Enable && inRange(marioPos, marioSize)) {
		Enable = false;
		puts("CheckPoint");
		static_cast<MyAPP::GameManager*>(data)->SaveCheckPointPos(marioPos);
	}
}
