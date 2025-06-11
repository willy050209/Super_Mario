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
		auto moveEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
		auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveEvent->userdata);
		auto& [enemys, pipes, props, objs] = (*tuplePtr);
		std::for_each(enemys->begin(), enemys->end(), [](auto& it) {
			it->setResetPosition(it->GetPosition());
		});
	}
}
