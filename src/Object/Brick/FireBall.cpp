#include "Object/Brick/FireBall.hpp"
#include "Object/Character/Mario.hpp"
#include "GameManager.hpp"
#include "config.hpp"

#include <iostream>

void MyAPP::Form::Object::FireBalls::behavior(void* data) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	if (!mario->isInvincible() && !GM->opMode) {
		if (inRange(mario->GetPosition(), mario->GetSize())) {
			GM->DecHP();
			mario->died();
			GM->bgm->Pause();
			GM->sfx->LoadMedia(MyAPP::MyResourcesFilePath::Lost_a_Life);
			GM->sfx->Play(0);
			(FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdateHPText"))->Enable = true;
			if (GM->GetHP() == 0) {
				GM->bgm->LoadMedia(MyAPP::MyResourcesFilePath::Game_Over);
				auto sleepevent = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "SleepAllevent"));
				sleepevent->Enable = true;
				sleepevent->userdata.reset();
				sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP * 3, std::vector<bool>());
				(FM.GetFormObject<EventObject>(FM.GetNowForm(), "FinifhEvent"))->Enable = true;
			}
			else {
				(FM.GetFormObject<EventObject>(FM.GetNowForm(), "GoBackCheckPoint"))->Enable = true;
				auto sleepevent = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "SleepAllevent"));
				sleepevent->Enable = true;
				sleepevent->userdata.reset();
				sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP, std::vector<bool>());
			}
		}
	}
}
