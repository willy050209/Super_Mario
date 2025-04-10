#ifndef EVENTCALLCALLBACKFUNC_hpp
#define EVENTCALLCALLBACKFUNC_hpp
#include "InitFormFunc.hpp"
#include "incallobj.hpp"
#include "config.hpp"
#include "util/Input.hpp"
#include "Position.hpp"


#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
#include <tuple>

#define EVENTCALLCALLBACKFUN(FUNC_name) static void FUNC_name(EventObject* const self, void* data)

//INITFORM_FUNC(initForm_1_2);

//inline void loadCheckpoint(GameManager* const GM, std::shared_ptr<std::vector<std::shared_ptr<CheckPoint>>> checkPoints) noexcept {
//	auto& FM = GM->GetFormManger();
//	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
//	auto& background = std::static_pointer_cast<ImageObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::ImageObject, "Background"));
//	//auto& checkPoints = std::static_pointer_cast<std::vector<std::shared_ptr<CheckPoint>>>(self->userdata);
//	auto& allobj = FM.GetFormAndObject(FM.GetNowForm());
//	auto marioPos = mario->GetPosition();
//	auto marioSize = mario->GetSize();
//	for (auto& it = checkPoints->end() - 1; it >= checkPoints->begin(); --it) {
//		if ((*it)->Enable) {
//			mario->SetPosition(GM->GetCheckPointPos());
//			for (auto& obj : allobj.m_Images) {
//				auto pos = obj->GetPosition();
//				pos.x = (*it)->GetPosition().x;
//			}
//			break;
//		}
//	}
//}



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
	auto tuplePtr = std::static_pointer_cast<std::tuple<std::vector<std::shared_ptr<Character>>, std::vector<std::shared_ptr<Brick>>>>(self->userdata);
	auto& [enemys, pipes] = (*tuplePtr);
	auto& background = std::static_pointer_cast<ImageObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::ImageObject, "Background"));
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto block = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(background->userdata);
    bool flag = true;
    auto tmp = mario->GetPosition();
	auto mariosize = mario->GetSize();

    if (Util::Input::IsKeyPressed(Util::Keycode::RSHIFT)) {
		Displacement *= 2;
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
		if (abs(mario->GetPosition().x ) >= mariosize.x && pos.x == GetX0(background) && flag) {
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
		if (abs(mario->GetPosition().x) >= mariosize.x && pos.x == -GetX0(background) && flag) {
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
		for (auto& it : pipes) {
			if (it->inRange({ tmp.x, tmp.y }, mariosize)) {
				auto ChangeFormEventObject = std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "ChangeFormEvent"));
				ChangeFormEventObject->Enable = true;
				ChangeFormEventObject->userdata = std::make_shared<std::string>(Form_1_1_Pipe);
				return;
			}
		}
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
	auto& [num, nowtime, timetext] = (*(std::static_pointer_cast<std::tuple<int, int, std::shared_ptr<TextObject>>>(self->userdata)));
    if ((num)++ >= FPS_CAP) {
        //auto& timetext = std::get<std::shared_ptr<TextObject>>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<TextObject>>>(self->userdata));
		//auto& nowtime = std::get<1>(*(std::static_pointer_cast<std::tuple<int,int, std::shared_ptr<TextObject>>>(self->userdata)));
        std::static_pointer_cast<Util::Text>(timetext->GetDrawable())->SetText(std::to_string(--nowtime));
        (num) = 0;
        if (nowtime == 0) {
			std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "FinifhEvent"))->Enable = true;
        }
    }
}

//EVENTCALLCALLBACKFUN(QuestionBlockPlayGIF) {
//	static const std::string imgs[] = { "imgs/super mario/QuestionBlock/frame0.png" , "imgs/super mario/QuestionBlock/frame1.png", "imgs/super mario/QuestionBlock/frame2.png", "imgs/super mario/QuestionBlock/frame3.png", "imgs/super mario/QuestionBlock/frame4.png", "imgs/super mario/QuestionBlock/frame5.png" };
//	auto& questions = std::get<std::vector<std::shared_ptr<QuestionBlock>>>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<QuestionBlock>>>>(self->userdata));
//	auto& count = std::get<0>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<ImageObject>>>>(self->userdata));
//	auto& imgindex = std::get<1>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<ImageObject>>>>(self->userdata));
//	++(*count);
//	if (*count >= FPS_CAP / 6) {
//		++*imgindex;
//		*imgindex %= 6;
//		for (auto& it : questions) {
//			if ((it)->name == "QuestionBlock" && abs(it->GetPosition().x) <= WINDOW_WIDTH / 2 && abs(it->GetPosition().y) <= WINDOW_HEIGHT / 2) {
//				std::static_pointer_cast<Util::Image>((it)->GetDrawable())->SetImage(imgs[*imgindex]);
//			}
//		}
//		*count = 0;
//	}
//}

EVENTCALLCALLBACKFUN(CheckDoors) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto doorarrPtr = std::static_pointer_cast<std::array<std::shared_ptr<Brick>, 2>>(self->userdata);
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	for (auto& it : *doorarrPtr) {
		if (it->inRange(marioPos, marioSize)) {
			auto& objandform = FM.GetFormAndObject(FM.GetNowForm());
			for (auto& eventobj : objandform.m_Events) {
				eventobj->Enable = false;
			}
			auto ChangeFormEventObject = std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "ChangeFormEvent"));
			ChangeFormEventObject->Enable = true;
			if (FM.GetNowForm() == Form_1_1) {
				initForm_1_2((GameManager*)data);
				//initForm_1_2((GameManager*)data);
				ChangeFormEventObject->userdata = std::make_shared<std::string>(Form_1_2);
			}
			else {
				ChangeFormEventObject->userdata = std::make_shared<std::string>("Win");
			}
			//initForm_1_2((GameManager*)data);
			break;
		}
	}
}

EVENTCALLCALLBACKFUN(CheckEneyCollision) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto& eneys = std::static_pointer_cast<std::vector<std::shared_ptr<Character>>>(self->userdata);
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
    for (auto& it : *eneys) {
		if (it->collisionable && it->inRange(marioPos, marioSize)) {
            if (marioPos.y > it->GetPosition().y) {
				it->died();
				/*it->collisionable = false;
				it->SetVisible(false);*/
            }
			else {
				//std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "FinifhEvent"))->Enable = true;
				GM->bgm->LoadMedia(Lost_a_Life);
				GM->bgm->Play(1);
				GM->DecHP();
				mario->diedjump();
				std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "UpdateHPText"))->Enable = true;
				if (GM->GetHP() == 0) {
					std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "FinifhEvent"))->Enable = true;
				}else{
					std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "GoBackCheckPoint"))->Enable = true;
					auto& sleepevent = std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "SleepAllevent"));
					sleepevent->Enable = true;
					sleepevent->userdata.reset();
					sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP, std::vector<bool>());
				}
			}
        }
    }
}

EVENTCALLCALLBACKFUN(CallFinish) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto& bgm = static_cast<GameManager*>(data)->bgm;
	bgm->LoadMedia(Lost_a_Life);
	bgm->Play(1);
	/*mario->changeState("DIED");
	mario->changeImg();*/
	auto& objandform = FM.GetFormAndObject(FM.GetNowForm());
    for (auto& eventobj : objandform.m_Events) {
		eventobj->Enable = false;
    }
	//static_cast<GameManager*>(data)->pause = true;
	FM.addObject(FM.GetNowForm(), std::make_shared<TextObject>("Finishtext", MyFontPath, 20, "GameOver", Util::Color::FromName(Util::Colors::WHITE), 100));
	puts("Game Over");
}


EVENTCALLCALLBACKFUN(CheckFlagpoleCollision) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto& flagpole = std::static_pointer_cast<std::vector<std::shared_ptr<Brick>>>(self->userdata);
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	for (auto& it = flagpole->begin(); it < flagpole->end();++it) {
		if ((*it)->inRange(marioPos, marioSize)) {
			int f_height = static_cast<int>(it - flagpole->begin());
			static_cast<GameManager*>(data)->addPoint(1000 * f_height);
			printf("FlagpoleCollision.\nTouch height:%d", f_height);
			self->Enable = false;
			std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "moveToDoor"))->Enable = true;
			std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "moveEvent"))->Enable = false;
			break;
		}
	}
}

EVENTCALLCALLBACKFUN(moveToDoor) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto doorarrPtr = std::static_pointer_cast<std::array<std::shared_ptr<Brick>, 2>>(self->userdata);
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	auto&& Displacement = WINDOW_HEIGHT / 15 / 8.f;
	if (mario->GetState() == Mario::State::MOVE) {
		if (marioPos.x > (*doorarrPtr->begin())->GetPosition().x) {
			marioPos.x -= Displacement;
			mario->left = 1;
		}
		else {
			marioPos.x += Displacement;
			mario->left = 0;
		}
	}
	mario->SetPosition(marioPos);
	mario->move();
}

EVENTCALLCALLBACKFUN(CheckPointCollision) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto& background = std::static_pointer_cast<ImageObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::ImageObject, "Background"));
	auto& checkPoints = std::static_pointer_cast<std::vector<std::shared_ptr<CheckPoint>>>(self->userdata);
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	auto pos = background->GetPosition();
	for (auto& it = checkPoints->begin(); it < checkPoints->end(); ++it) {
		if ((*it)->Enable && (*it)->inRange(marioPos, marioSize)) {
			(*it)->Enable = false;
			puts("CheckPoint");
			static_cast<GameManager*>(data)->SaveCheckPointPos(marioPos);
			break;
		}
	}
}

EVENTCALLCALLBACKFUN(GoBackCheckPoint) {
	auto& FM = static_cast<GameManager*>(data)->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	auto& checkPoints = std::static_pointer_cast<std::vector<std::shared_ptr<CheckPoint>>>(self->userdata);
	auto& allobj = FM.GetFormAndObject(FM.GetNowForm());
	int gobackposx = 0;
	mario->SetPosition(static_cast<GameManager*>(data)->GetCheckPointPos());
	mario->Reset();
	for (int i = checkPoints->size() - 1; i >= 0;--i) {
		if (!(*checkPoints)[i]->Enable) {
			gobackposx = (*checkPoints)[i]->GetPosition().x;
			for (auto& obj : allobj.m_Images) {
				if (obj->MyType != ObjectType::CheckPoint) {
					auto pos = obj->GetPosition();
					pos.x -= gobackposx;
					obj->SetPosition(pos);
				}
			}
			for (auto& obj : allobj.m_Characters) {
				if (obj->MyType != ObjectType::Mario) {
					auto pos = obj->GetPosition();
					pos.x -= gobackposx;
					obj->SetPosition(pos);
				}
			}
			self->Enable = false;
			break;
		}
	}
	for (auto& it : *checkPoints) {
		auto pos = it->GetPosition();
		pos.x -= gobackposx;
		it->SetPosition(pos);
	}
}

EVENTCALLCALLBACKFUN(UpdateHPText) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto& text = FM.GetFormObject(FM.GetNowForm(), ObjectType::TextObject, "HPText");
	char textstr[10] = "";
	snprintf(textstr, sizeof(textstr), "HP:%d", GM->GetHP());
	std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(textstr);
	self->Enable = false;
}

EVENTCALLCALLBACKFUN(CheckMArioPosition) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Character, "Mario"));
	if (abs(mario->GetPosition().y) >= (((unsigned)WINDOW_HEIGHT) >> 1) && mario->GetPosition().y <0) {
		GM->DecHP();
		std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "UpdateHPText"))->Enable = true;
		if (GM->GetHP() == 0) {
			std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "FinifhEvent"))->Enable = true;
		}
		else {
			std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "GoBackCheckPoint"))->Enable = true;
		}
	}
}

EVENTCALLCALLBACKFUN(SleepAllevent) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto & [ count, bvec ] = (*std::static_pointer_cast<std::tuple<int, std::vector<bool>>>(self->userdata));
	--count;
	if (bvec.size() == 0) {
		auto& allevent = FM.GetFormAndObject(FM.GetNowForm()).m_Events;
		for (auto& it : allevent) {
			bvec.push_back(it->Enable);
			if (it->name != self->name) 
				it->Enable = false;
		}
	}
	else {
		if (count == 0) {
			auto& allevent = FM.GetFormAndObject(FM.GetNowForm()).m_Events;
			for (int i = 0; i < allevent.size();++i) {
				if (allevent[i]->name == self->name) {
					allevent[i]->Enable = false;
					continue;
				}
				allevent[i]->Enable = bvec[i];
			}
		}
	}
}

EVENTCALLCALLBACKFUN(CheckCoinsCollision) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Mario, "Mario"));
	auto& coins = std::static_pointer_cast<std::vector<std::shared_ptr<Coin>>>(self->userdata);
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	for (auto& it : *coins) {
		if (it->GetVisibility() && it->inRange(marioPos, marioSize)) {
			it->bonk();
			GM->addPoint(100);
			std::static_pointer_cast<EventObject>(FM.GetFormObject(FM.GetNowForm(), ObjectType::EventObject, "UpdatePointText"))->Enable = true;
		}
	}
}

EVENTCALLCALLBACKFUN(UpdatePointText) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto& text = FM.GetFormObject(FM.GetNowForm(), ObjectType::TextObject, "PointText");
	char textstr[128] = "";
	snprintf(textstr, sizeof(textstr), "Point:%d", GM->GetPoint());
	std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(textstr);
	self->Enable = false;
}

EVENTCALLCALLBACKFUN(CheckTortoiseShellCollision) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto& mario = std::static_pointer_cast<Mario>(FM.GetFormObject(FM.GetNowForm(), ObjectType::Mario, "Mario"));
	auto& turtles = std::static_pointer_cast<std::vector<std::shared_ptr<Turtle>>>(self->userdata);
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	for (auto& it : *turtles) {
		if (it->GetVisibility() && it->inRange(marioPos, marioSize)) {
			auto turtlePos{ it->GetPosition() };
			if (it->GetPosition().x > marioPos.x) {
				turtlePos.x += it->GetSize().x;
			}
			else {
				turtlePos.x -= it->GetSize().x;
			}
			it->SetPosition(turtlePos);
		}
	}
}

EVENTCALLCALLBACKFUN(ChangeFormEvent) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto form = std::static_pointer_cast<std::string>(self->userdata);
	self->Enable = false;
	FM.changeForm(*form);
}

EVENTCALLCALLBACKFUN(freeForm_1_1) {
	auto GM = static_cast<GameManager*>(data);
	auto& FM = GM->GetFormManger();
	FM.freeForm(Form_1_1);
	self->Enable = false;
	auto& m_Events = FM.GetFormAndObject(Form_1_2).m_Events;
	m_Events.erase(std::find_if(m_Events.begin(), m_Events.end(), [](auto& i) { return i->name == "freeForm_1_1"; }));
}

#endif