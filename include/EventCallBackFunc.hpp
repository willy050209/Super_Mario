#ifndef EVENTCALLCALLBACKFUNC_hpp
#define EVENTCALLCALLBACKFUNC_hpp

#include "incallobj.hpp"
#include "config.hpp"
#include "util/Input.hpp"
#include "Position.hpp"
#include<GameManager.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
#include <tuple>

#define EVENTCALLCALLBACKFUN(FUNC_name) static void FUNC_name(EventObject* const self, void* data)


EVENTCALLCALLBACKFUN(GetSystemTimeFunc){
    auto num = std::static_pointer_cast<int>(self->userdata);
    if ((*num)++ >= FPS_CAP) {
        auto currentTime = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(currentTime);
        std::cout << "目前時間：" << std::ctime(&time);
        (*num) = 0;
    }
}

EVENTCALLCALLBACKFUN(moveEvent) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
    auto&& Displacement = WINDOW_HEIGHT/15/8.f;
	//const auto Displacement = WINDOW_HEIGHT / 15/2;
	auto tuplePtr = std::static_pointer_cast<std::tuple<std::vector<std::shared_ptr<Character>>>>(self->userdata);
	auto& enemys = std::get<0>(*tuplePtr);
	auto& background = std::static_pointer_cast<ImageObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::ImageObject, "Background"));
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
    auto block = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(background->userdata);
    bool flag = true;
    auto tmp = mario->GetPosition();
	auto mariosize = mario->GetSize();

    if (Util::Input::IsKeyPressed(Util::Keycode::RSHIFT)) {
		Displacement *= 4;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::UP) && (mario)->GetState() == Mario::State::MOVE) {
        (mario)->jump();
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        auto pos = (background)->GetPosition();
		mario->left = 0;
        for (auto& it : *block) {
			if (it->collisionable && it->inRange({ tmp.x + Displacement, tmp.y }, mariosize)) {
                flag = false;
                break;
            }
        }
        if (mario->GetPosition().x!=0 && pos.x == GetX0(background) && flag ) {
            mario->SetPosition({ mario->GetPosition().x + Displacement,mario->GetPosition().y });
        }
        else if(pos.x > -GetX0(background) && flag)
        {
            pos.x-= Displacement;
            for (auto& it : *block) {
                it->SetPosition({ it->GetPosition().x - Displacement,it->GetPosition().y });
            }
            for (auto& it : enemys) {
				it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
            }
        }
        else if (mario->GetPosition().x < (WINDOW_WIDTH / 2) - mario->GetSize().x && flag)
        {
            mario->SetPosition({ mario->GetPosition().x + Displacement,mario->GetPosition().y });
        }
        if(flag)
            (background)->SetPosition(pos);
		mario->move();
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
		mario->left = 1;
        auto pos = (background)->GetPosition();
        for (auto& it : *block) {
			if (it->collisionable && it->inRange({ tmp.x - Displacement, tmp.y }, mariosize)) {
                flag = false;
                break;
            }
        }
        if (mario->GetPosition().x != 0 && pos.x == -GetX0(background) && flag) {
			mario->SetPosition({ mario->GetPosition().x - Displacement, mario->GetPosition().y });
        }
        else if (pos.x < GetX0(background) && flag)
        {
            pos.x += Displacement;
            for (auto& it : *block) {
                it->SetPosition({ it->GetPosition().x + Displacement,it->GetPosition().y });
            }
			for (auto& it : enemys) {
				it->SetPosition({ it->GetPosition().x + Displacement, it->GetPosition().y });
			}
        }
        else if (mario->GetPosition().x > (-WINDOW_WIDTH / 2) + mario->GetSize().x && flag)
        {
            mario->SetPosition({ mario->GetPosition().x - Displacement,mario->GetPosition().y });
        }
        if(flag)
            (background)->SetPosition(pos);
		mario->move();
        
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
		for (auto& it : *block) {
			if (it->inRange({ tmp.x, tmp.y }, mariosize)) {
				flag = false;
				break;
			}
		}
		std::cout << flag;
    }
	
    /*test*/
    if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
		mario->jump();
	}
    else if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
		mario->SetPosition({ mario->GetPosition().x, GetY0(mario) });
    }
}

EVENTCALLCALLBACKFUN(UpdateTimeText) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto& num = std::get<0>(*(std::static_pointer_cast < std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::shared_ptr<TextObject>>>(self->userdata)));
    if ((*num)++ >= FPS_CAP) {
        auto& timetext = std::get<std::shared_ptr<TextObject>>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<TextObject>>>(self->userdata));
		auto& nowtime = *std::get<1>(*(std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::shared_ptr<TextObject>>>(self->userdata)));
        std::static_pointer_cast<Util::Text>(timetext->GetDrawable())->SetText(std::to_string(--nowtime));
        (*num) = 0;
        if (nowtime == 0) {
			std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "FinifhEvent"))->Enable = true;
        }
    }
}

EVENTCALLCALLBACKFUN(QuestionBlockPlayGIF) {
	const std::string imgs[] = { "imgs/super mario/QuestionBlock/frame0.png" , "imgs/super mario/QuestionBlock/frame1.png", "imgs/super mario/QuestionBlock/frame2.png", "imgs/super mario/QuestionBlock/frame3.png", "imgs/super mario/QuestionBlock/frame4.png", "imgs/super mario/QuestionBlock/frame5.png" };
	auto& questions = std::get<std::vector<std::shared_ptr<ImageObject>>>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<ImageObject>>>>(self->userdata));
	auto& count = std::get<0>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<ImageObject>>>>(self->userdata));
	auto& imgindex = std::get<1>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<ImageObject>>>>(self->userdata));
	++(*count);
	if (*count >= FPS_CAP / 6) {
		++*imgindex;
		*imgindex %= 6;
		for (auto& it : questions) {
			if ((it)->name == "QuestionBlock" && abs(it->GetPosition().x) <= WINDOW_WIDTH / 2 && abs(it->GetPosition().y) <= WINDOW_HEIGHT / 2) {
				std::static_pointer_cast<Util::Image>((it)->GetDrawable())->SetImage(imgs[*imgindex]);
			}
		}
		*count = 0;
	}
}

EVENTCALLCALLBACKFUN(CheckDoors) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto doorarrPtr = std::static_pointer_cast<std::array<std::shared_ptr<ImageObject>, 2>>(self->userdata);
	auto mario = FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario");
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	for (auto& it : *doorarrPtr) {
		if (it->inRange(marioPos, marioSize)) {
			auto& objandform = FM.GetFormAndObject(FM.GetNowForm());
			for (auto& eventobj : objandform.m_Events) {
				eventobj->Enable = false;
			}
			FM.changeForm(Form_1_2);
			break;
		}
	}
}

EVENTCALLCALLBACKFUN(CheckEneyCollision) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto& eneys = std::static_pointer_cast<std::vector<std::shared_ptr<Character>>>(self->userdata);
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
    for (auto& it : *eneys) {
		if (it->collisionable && it->inRange(marioPos, marioSize)) {
            if (marioPos.y > it->GetPosition().y) {
				it->collisionable = false;
				it->SetVisible(false);
            }
			else {
				std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "FinifhEvent"))->Enable = true;
				auto bgm = std::make_shared<Util::BGM>(MY_RESOURCE_DIR "/BGM/08. Lost a Life.mp3");
				//bgm->LoadMedia(MY_RESOURCE_DIR "/BGM/08. Lost a Life.mp3");
				bgm->Play(1);
			}
        }
    }
}

EVENTCALLCALLBACKFUN(CallFinish) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto bgm = std::make_shared<Util::BGM>(MY_RESOURCE_DIR "/BGM/08. Lost a Life.mp3");
	bgm->LoadMedia(MY_RESOURCE_DIR "/BGM/08. Lost a Life.mp3");
	bgm->Play(1);
	/*mario->changeState("DIED");
	mario->changeImg();*/
	mario->diedjump();
	auto& objandform = FM.GetFormAndObject(FM.GetNowForm());
    for (auto& eventobj : objandform.m_Events) {
		eventobj->Enable = false;
    }
	//static_cast<GameManager*>(data)->pause = true;
	FM.addObject(Form_1_1, std::make_shared<TextObject>("Finishtext", MyFontPath, 20, "GameOver", Util::Color::FromName(Util::Colors::WHITE), 100));
	puts("Game Over");
}


EVENTCALLCALLBACKFUN(CheckFlagpoleCollision) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto& flagpole = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(self->userdata);
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	for (auto& it = flagpole->begin(); it < flagpole->end();++it) {
		if ((*it)->inRange(marioPos, marioSize)) {
			printf("FlagpoleCollision.\nTouch height:%d",it - flagpole->begin());
			self->Enable = false;
			break;
		}
	}
}

#endif