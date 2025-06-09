#include "Object/Character/Koopa.hpp"
#include "Object/Character/MArio.hpp"
#include "GameManager.hpp"
#include "FilePath.hpp"
#include "config.hpp"
#include <iostream>
#include <ctime>

void MyAPP::Form::Object::Koopa::behavior(void* data) {
	if(!isdied){
		move();
		if (!jump)
			comeDown();
		CheckCollision(data);
		checkPosition();
		random_shoot(data);
		turn(data);
		PlayFrames();
	}
	else {
		m_Transform.translation.y -= getDEFAULTDISPLACEMENT();
	}
}

void MyAPP::Form::Object::Koopa::died() noexcept {
	HP--;
	std::cout << "Koopa HP" << HP << std::endl;
	if (HP <= 0) {
		std::cout << "Koopa died" << std::endl;
		std::static_pointer_cast<Util::Image>(GetDrawable())->SetImage("imgs/super mario/KoopaDie.png");
		isdied = true;
	}
}

void MyAPP::Form::Object::Koopa::move() noexcept {
	switch (koopstate) {
	case MyAPP::Form::Object::Koopa::KoopaState::jump1:
		m_Transform.translation += glm::vec2{ -getDEFAULTDISPLACEMENT() / 2, getDEFAULTDISPLACEMENT() / 2 };
		jumpcout--;
		break;
	case MyAPP::Form::Object::Koopa::KoopaState::null:
		delaycount--;
		break;
	case MyAPP::Form::Object::Koopa::KoopaState::jump2:
		m_Transform.translation += glm::vec2{ getDEFAULTDISPLACEMENT() / 2, getDEFAULTDISPLACEMENT() / 2 };
		jumpcout--;
		break;
	default:
		break;
	}
	if (jumpcout <= 0 && koopstate != KoopaState::null) {
		koopstate = KoopaState::null;
		delaycount = FPS_CAP / 2;
		jump = false;
	}
	if (delaycount <= 0 && koopstate == KoopaState::null) {
		jump = true;
		jumpcout = FPS_CAP;
		koopstate = (is_L_or_R) ? KoopaState::jump1 : KoopaState::jump2;
		is_L_or_R = !is_L_or_R;
	}
}

void MyAPP::Form::Object::Koopa::checkPosition() noexcept {
	if (std::abs(GetPosition().y) > WINDOW_HEIGHT/2) {
		died();
	}
}

void MyAPP::Form::Object::Koopa::turn(void* data) noexcept {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	left = (GetPosition().x >= mario->GetPosition().x) ? 1 : 0;
}

void MyAPP::Form::Object::Koopa::CheckCollision(void* data) {
	using namespace MyAPP::Form::Object;
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	if (!GM->opMode && !mario->isInvincible() && !mario->isdied()) {
		if (collisionable && inRange(marioPos, marioSize)) {
			mario->died();
			if (!mario->isdied()) {
				GM->LostALife();
			}
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

void MyAPP::Form::Object::Koopa::random_shoot(void* data) noexcept {
	shootdelay++;
	if(shootdelay >= FPS_CAP){
		static bool seeded = false;
		if (!seeded) {
			srand(static_cast<unsigned int>(time(0)));
			seeded = true;
		}

		auto randomNumber = rand() % 100;

		if (randomNumber < 50) {
			shoot(data);
		}
		shootdelay = 0;
	}
}

void MyAPP::Form::Object::Koopa::shoot(void* data) noexcept {
	std::cout << "shoot\n\r";
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	Koopa_Fire::CreateFire(FM);
}

void MyAPP::Form::Object::Koopa_Fire::behavior(void* data) {
	this->CheckCollision(data);
	this->Move({ (left) ? -getDEFAULTDISPLACEMENT() / 2 : getDEFAULTDISPLACEMENT() / 2, 0 });
	if (destroyflag)
		destroyFire(static_cast<GameManager*>(data)->GetFormManger());
}

void MyAPP::Form::Object::Koopa_Fire::CreateFire(MyAPP::Form::FormManger& FM) noexcept {
	auto koopa_ptr = FM.GetFormObject<Koopa>(FM.GetNowForm(), "Koopa");
	auto moveEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
	auto fire = std::make_shared<Koopa_Fire>("Koopa_Fire", 20);
	if (koopa_ptr && moveEvent && fire) {
		auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveEvent->userdata);
		auto& [enemys, pipes, props, objs] = (*tuplePtr);
		if (tuplePtr == nullptr)
			return;
		fire->left = koopa_ptr->isLeft();
		if (fire->left) {
			fire->SetPosition(koopa_ptr->GetPosition() - glm::vec2(fire->GetSize().x, 0));
		}
		else {
			fire->SetPosition(koopa_ptr->GetPosition() + glm::vec2(fire->GetSize().x, 0));
		}
		FM.addObject(FM.GetNowForm(), fire);
		objs->push_back(std::move(fire));
	}
}

void MyAPP::Form::Object::Koopa_Fire::Move(const glm::vec2& distance) noexcept {
	m_Transform.translation.x += distance.x;
	Xcount += distance.x;
	if (Xcount > WINDOW_WIDTH) {
		destroyflag = true;
	}
}


void MyAPP::Form::Object::Koopa_Fire::CheckCollision(void* data) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto moveEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
	if (mario == nullptr || moveEvent == nullptr || GM->opMode)
		return;
	if (inRange(mario->GetPosition(), mario->GetSize()))
	{
		mario->died();
		if (mario->GetState() == Mario::State::DIED) {
			GM->LostALife();
		}
		destroyflag = true;
	}
	bool flag = false;
	for (auto& it : *std::static_pointer_cast<BrickPtrVec>(mario->userdata)) {
		if (it->collisionable && it->inRange(GetPosition(), GetSize())) {
			flag = true;
		}
	}
	if (flag)
		destroyflag = true;
}

void MyAPP::Form::Object::Koopa_Fire::destroyFire(FormManger& FM) noexcept {
	auto moveEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
	auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveEvent->userdata);
	auto& [enemys, pipes, props, objs] = (*tuplePtr);
	if (tuplePtr == nullptr)
		return;
	FM.removeObject<Koopa_Fire>(FM.GetNowForm(), m_ID);
	objs->erase(std::remove_if(objs->begin(), objs->end(), [&](const ObjectPtr& obj) {
		return obj->m_ID == m_ID;
	}),
		objs->end());
	destroyflag = false;
}
