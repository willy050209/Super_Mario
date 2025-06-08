#pragma once
#ifndef EVENTCALLCALLBACKFUNC_hpp
#define EVENTCALLCALLBACKFUNC_hpp
#include "InitFormFunc.hpp"
#include "incallobj.hpp"
#include "config.hpp"
#include "Position.hpp"
#include "Form/FormNames.hpp"
#include "Util/Input.hpp"
#include "userType.hpp"

#include <execution>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <ctime>
#include <memory>
#include <tuple>

using namespace MyAPP::Form::Object;

#define EVENTCALLCALLBACKFUN(FUNC_name) static void FUNC_name(MyAPP::Form::Object::EventObject* const self, void* data)

// INITFORM_FUNC(initForm_1_2);

// inline void loadCheckpoint(GameManager* const GM, std::shared_ptr<std::vector<std::shared_ptr<CheckPoint>>> checkPoints) noexcept {
//	auto& FM = GM->GetFormManger();
//	auto& mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
//	auto& background = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "Background");
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
// }


/// <summary>
/// 取得現在系統時間，並輸出至CMD
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
EVENTCALLCALLBACKFUN(GetSystemTimeFunc) {
	auto num = std::static_pointer_cast<int>(self->userdata);
	if ((*num)++ >= FPS_CAP) {
		auto currentTime = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(currentTime);
		std::cout << "目前時間：" << std::ctime(&time);
		(*num) = 0;
	}
}

/// <summary>
/// 移動事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::tuple(std::vector(std::shared_ptr(Character)), std::vector(std::shared_ptr(Brick))) </param>
EVENTCALLCALLBACKFUN(moveEvent) {
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	// const auto Displacement = WINDOW_HEIGHT / 15/2;
	auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(self->userdata);
	auto& [enemys, pipes, props, objs] = (*tuplePtr);
	auto background = FM.GetFormObject<MyAPP::Form::Object::ImageObject>(FM.GetNowForm(), "Background");
	auto mario = FM.GetFormObject<MyAPP::Form::Object::Mario>(FM.GetNowForm(), "Mario");
	auto block = std::static_pointer_cast<BrickPtrVec>(background->userdata);
	auto flag = true;
	auto marioPos = mario->GetPosition();
	auto mariosize = mario->GetSize();
	auto&& Displacement = static_cast<int>(mariosize.x) >> 3;
	auto& opmode = static_cast<MyAPP::GameManager*>(data)->opMode;
	

	if (mario->GetState() == Mario::State::DIED)
		return;
	if (Util::Input::IsKeyPressed(Util::Keycode::RSHIFT) || Util::Input::IsKeyPressed(Util::Keycode::LSHIFT)) {
		if (Util::Input::IsKeyDown(Util::Keycode::RSHIFT) || Util::Input::IsKeyDown(Util::Keycode::LSHIFT)) {
			mario->shootFire();
		}
		Displacement *= 2;
	}
	if (!opmode && Util::Input::IsKeyDown(Util::Keycode::UP) && (mario)->GetState() == MyAPP::Form::Object::Mario::State::MOVE) {
		(mario)->jump();
	}
	if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
		auto pos = (background)->GetPosition();
		if (mario->isLeft()) {
			mario->SetLeft<false>();
			mario->changeImg();
		}
		for (auto& it : *block) {
			if (it->collisionable && it->inRange({ marioPos.x + Displacement, marioPos.y }, mariosize)) {
				flag = false;
				marioPos.x = it->GetPosition().x - ((static_cast<int>(it->GetSize().x) >> 1) + (static_cast<int>(mariosize.x) >> 1));
				break;
			}
		}
		if (abs(mario->GetPosition().x) >= mariosize.x  && flag) {
			mario->SetPosition({ mario->GetPosition().x + Displacement, mario->GetPosition().y });
		}
		else if (pos.x > -GetLeftEdge(background) && flag) {
			pos.x -= Displacement;
			std::for_each(std::execution::seq, block->begin(), block->end(), 
				[&](auto& it) {
					it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y }); 
				});
			std::for_each(std::execution::seq, enemys->begin(), enemys->end(),
				[&](auto& it) {
					it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
				});
			std::for_each(std::execution::seq, props->begin(), props->end(),
				[&](auto& it) {
					it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
				});
			std::for_each(std::execution::seq, objs->begin(), objs->end(),
				[&](auto& it) {
					it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
				});
			/*thread_object_move.push_back(std::thread([&]() {for (auto& it : *block) {
				it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
			} }));
			thread_object_move.push_back(std::thread([&]() {for (auto& it : enemys) {
				it->SetPosition({ it->GetPosition().x - Displacement, it->GetPosition().y });
			} }));*/
		}
		else if (mario->GetPosition().x < ((static_cast<int>(WINDOW_WIDTH) >> 1)) - mario->GetSize().x && flag) {
			mario->SetPosition({ mario->GetPosition().x + Displacement, mario->GetPosition().y });
		}
		if (flag)
			(background)->SetPosition(pos);
		else
			mario->SetPosition(marioPos);
		mario->move();
	}
	else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
		if (!mario->isLeft()) {
			mario->SetLeft<true>();
			mario->changeImg();
		}
		auto pos = (background)->GetPosition();
		for (auto& it : *block) {
			if (it->collisionable && it->inRange({ marioPos.x - Displacement, marioPos.y }, mariosize)) {
				flag = false;
				//marioPos = it->GetPosition();
				marioPos.x = it->GetPosition().x + ((static_cast<int>(it->GetSize().x) >> 1) + (static_cast<int>(mariosize.x) >> 1));
				break;
			}
		}
		if (abs(mario->GetPosition().x) >= mariosize.x && flag) {
			mario->SetPosition({ mario->GetPosition().x - Displacement, mario->GetPosition().y });
		}
		//else if (pos.x < GetLeftEdge(background) && flag) {
		//	pos.x += Displacement;
		//	std::for_each(std::execution::seq, block->begin(), block->end(),
		//		[&](auto& it) {
		//			it->SetPosition({ it->GetPosition().x + Displacement, it->GetPosition().y });
		//		});
		//	std::for_each(std::execution::seq, enemys->begin(), enemys->end(),
		//		[&](auto& it) {
		//			it->SetPosition({ it->GetPosition().x + Displacement, it->GetPosition().y });
		//		});
		//	std::for_each(std::execution::seq, props->begin(), props->end(),
		//		[&](auto& it) {
		//			it->SetPosition({ it->GetPosition().x + Displacement, it->GetPosition().y });
		//		});
		//	std::for_each(std::execution::seq, objs->begin(), objs->end(),
		//		[&](auto& it) {
		//			it->SetPosition({ it->GetPosition().x + Displacement, it->GetPosition().y });
		//		});
		//	/*thread_object_move.push_back(std::thread([&]() {for (auto& it : *block) {
		//		it->SetPosition({ it->GetPosition().x + Displacement, it->GetPosition().y });
		//	} }));
		//	thread_object_move.push_back(std::thread([&]() {for (auto& it : enemys) {
		//		it->SetPosition({ it->GetPosition().x + Displacement, it->GetPosition().y });
		//	} }));*/
		//}
		else if (mario->GetPosition().x > (-(static_cast<int>(WINDOW_WIDTH) >> 1)) + mario->GetSize().x && flag) {
			mario->SetPosition({ mario->GetPosition().x - Displacement, mario->GetPosition().y });
		}
		if (flag)
			(background)->SetPosition(pos);
		else
			mario->SetPosition(marioPos);
		mario->move();
	}
	else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
		static_cast<MyAPP::GameManager*>(data)->mariotype = mario->GetMario_type();
		for (auto& it : *pipes) {
			if (it->inRange({ marioPos.x, marioPos.y }, mariosize)) {
				mario->SetLeft<false>();
				if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_1) {
					initForm_1_1_Pip(static_cast<MyAPP::GameManager*>(data));
					auto ChangeFormEventObject = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "ChangeFormEvent"));
					ChangeFormEventObject->Enable = true;
					ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1_Pipe);
					return;
				}
				else {
					initForm_1_2_Pipe(static_cast<MyAPP::GameManager*>(data));
					auto ChangeFormEventObject = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "ChangeFormEvent"));
					ChangeFormEventObject->Enable = true;
					ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2_Pipe);
					return;
				}
			}
		}
	}

	/*test*/
	if (Util::Input::IsKeyDown(Util::Keycode::O)) {
		opmode = !opmode;
		std::cout << "opmode : " << (opmode ? "true" : "false") << '\n';
	}
	else if (Util::Input::IsKeyDown(Util::Keycode::T)) {
		mario->died();
		static_cast<MyAPP::GameManager*>(data)->LostALife();
	}
	else if (Util::Input::IsKeyDown(Util::Keycode::B)) {
		mario->changeType(Mario::Mario_type::SuperMario);
	}
	else if (Util::Input::IsKeyDown(Util::Keycode::N)) {
		mario->changeType(Mario::Mario_type::FieryMario);
	}
	else if (Util::Input::IsKeyDown(Util::Keycode::LCTRL)) {
		mario->shootFire();
	}

	if (opmode) {
		if (Util::Input::IsKeyDown(Util::Keycode::W)) {
			marioPos.y += mariosize.y;
			mario->SetPosition(marioPos);
		}
		else if (Util::Input::IsKeyDown(Util::Keycode::S)) {
			marioPos.y -= mariosize.y;
			mario->SetPosition(marioPos);
		}
		else if (Util::Input::IsKeyDown(Util::Keycode::D)) {
			marioPos.x += mariosize.x;
			mario->SetPosition(marioPos);
		}
		else if (Util::Input::IsKeyDown(Util::Keycode::A)) {
			marioPos.x -= mariosize.x;
			mario->SetPosition(marioPos);
		}
		else if (Util::Input::IsKeyDown(Util::Keycode::LCTRL)) {
			mario->shootFire();
		}
	}

	/*for (auto& it : thread_object_move) {
		it.join();
	}*/
}

/// <summary>
/// 變更時間事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::tuple(int, int, std::shared_ptr(TextObject))) </param>
EVENTCALLCALLBACKFUN(UpdateTimeText) {
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto& [num, nowtime] = (*(std::static_pointer_cast<std::tuple<int, int>>(self->userdata)));
	auto timetext = FM.GetFormObject<TextObject>(FM.GetNowForm(), "Timetext");
	if ((num)++ >= FPS_CAP) {
		// auto& timetext = std::get<std::shared_ptr<MyAPP::Form::Object::TextObject>>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<MyAPP::Form::Object::TextObject>>>(self->userdata));
		// auto& nowtime = std::get<1>(*(std::static_pointer_cast<std::tuple<int,int, std::shared_ptr<MyAPP::Form::Object::TextObject>>>(self->userdata)));
		std::static_pointer_cast<Util::Text>(timetext->GetDrawable())->SetText(std::to_string(--nowtime));
		(num) = 0;
		if (nowtime == 0) {
			(FM.GetFormObject<EventObject>(FM.GetNowForm(), "FinifhEvent"))->Enable = true;
		}
	}
}

// EVENTCALLCALLBACKFUN(QuestionBlockPlayGIF) {
//	static const std::string imgs[] = { "imgs/super mario/QuestionBlock/frame0.png" , "imgs/super mario/QuestionBlock/frame1.png", "imgs/super mario/QuestionBlock/frame2.png", "imgs/super mario/QuestionBlock/frame3.png", "imgs/super mario/QuestionBlock/frame4.png", "imgs/super mario/QuestionBlock/frame5.png" };
//	auto& questions = std::get<std::vector<std::shared_ptr<QuestionBlock>>>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<QuestionBlock>>>>(self->userdata));
//	auto& count = std::get<0>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<MyAPP::Form::Object::ImageObject>>>>(self->userdata));
//	auto& imgindex = std::get<1>(*std::static_pointer_cast<std::tuple<std::shared_ptr<int>, std::shared_ptr<int>, std::vector<std::shared_ptr<MyAPP::Form::Object::ImageObject>>>>(self->userdata));
//	++(*count);
//	if (*count >= FPS_CAP / 6) {
//		++*imgindex;
//		*imgindex %= 6;
//		for (auto& it : questions) {
//			if ((it)->name == "QuestionBlock" && abs(it->GetPosition().x) <= (static_cast<unsigned>(WINDOW_WIDTH) >> 1) && abs(it->GetPosition().y) <= (static_cast<unsigned>(WINDOW_HEIGHT) >> 1)) {
//				std::static_pointer_cast<Util::Image>((it)->GetDrawable())->SetImage(imgs[*imgindex]);
//			}
//		}
//		*count = 0;
//	}
// }

/// <summary>
/// 判斷是否到達大門
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::array(std::shared_ptr(Brick), 2) </param>
EVENTCALLCALLBACKFUN(CheckDoors) {
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto doorarrPtr = std::static_pointer_cast<BrickPtrVec>(self->userdata);
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	for (auto& it : *doorarrPtr) {
		if (it->inRange(marioPos, marioSize)) {
			auto& objandform = FM.GetFormAndObject(FM.GetNowForm());
			for (auto& eventobj : objandform.m_Events) {
				eventobj->Enable = false;
			}
			auto ChangeFormEventObject = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "ChangeFormEvent"));
			ChangeFormEventObject->Enable = true;
			if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_1) {
				initForm_1_1_to_1_2(static_cast<MyAPP::GameManager*>(data));
				ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1_to_1_2);
			}
			else if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_1_Pipe) {
				auto& form_1_1_OBJ = FM.GetFormAndObject(MyAPP::Form::FormNames::Form_1_1);
				std::for_each(std::execution::seq, form_1_1_OBJ.m_Characters.begin(), form_1_1_OBJ.m_Characters.end(), [displacement = doorarrPtr->front()->GetSize().x * (-107)](auto& it) {
					it->incPositionX(displacement);
				});
				std::for_each(std::execution::seq, form_1_1_OBJ.m_Images.begin(), form_1_1_OBJ.m_Images.end(), [displacement = doorarrPtr->front()->GetSize().x * (-107)](auto& it) {
					it->incPositionX(displacement);
				});
				/*for (auto& it : form_1_1_OBJ.m_Characters) {
					auto tmp = it->GetPosition();
					tmp.x -= doorarrPtr->front()->GetSize().x * (107);
					it->SetPosition(tmp);
				}*/
				/*for (auto& it : form_1_1_OBJ.m_Images) {
					auto tmp = it->GetPosition();
					tmp.x -= doorarrPtr->front()->GetSize().x * (107);
					it->SetPosition(tmp);
				}*/
				FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "SleepAllevent")->Enable = true;
				FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "SleepAllevent")->userdata = std::make_shared<SleepAllEventUserDataType>(FPS_CAP, std::vector<bool>());
				(FM.GetFormObject<Mario>(MyAPP::Form::FormNames::Form_1_1, "Mario"))->SetPosition({ -(WINDOW_WIDTH >> 1) + (*doorarrPtr)[0]->GetSize().x * 9, GetTopEdge((*doorarrPtr)[0]) - (*doorarrPtr)[0]->GetSize().y * 10 });
				(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "freeForm_1_1_pipe"))->Enable = true;
				ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_1);
				//(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "UpdateHPText"))->Enable = true;
				(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "UpdatePointText"))->Enable = true;
			}
			else if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_1_to_1_2) {
				initForm_1_2(static_cast<MyAPP::GameManager*>(data));
				ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2);
			}
			else if (FM.GetNowForm() == MyAPP::Form::FormNames::Form_1_2_Pipe) {
				auto& form_1_2_OBJ = FM.GetFormAndObject(MyAPP::Form::FormNames::Form_1_2);
				std::for_each(std::execution::seq, form_1_2_OBJ.m_Characters.begin(), form_1_2_OBJ.m_Characters.end(), [displacement = doorarrPtr->front()->GetSize().x * (-12)](auto& it) {
					it->incPositionX(displacement);
				});
				std::for_each(std::execution::seq, form_1_2_OBJ.m_Images.begin(), form_1_2_OBJ.m_Images.end(), [displacement = doorarrPtr->front()->GetSize().x * (-12)](auto& it) {
					it->incPositionX(displacement);
				});
				/*for (auto& it : form_1_2_OBJ.m_Characters) {
					auto tmp = it->GetPosition();
					tmp.x -= doorarrPtr->front()->GetSize().x * (10);
					it->SetPosition(tmp);
				}
				for (auto& it : form_1_2_OBJ.m_Images) {
					auto tmp = it->GetPosition();
					tmp.x -= doorarrPtr->front()->GetSize().x * (10);
					it->SetPosition(tmp);
				}*/
				FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "SleepAllevent")->Enable = true;
				FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_1, "SleepAllevent")->userdata = std::make_shared<SleepAllEventUserDataType>(FPS_CAP, std::vector<bool>());
				(FM.GetFormObject<Mario>(MyAPP::Form::FormNames::Form_1_2, "Mario"))->SetPosition({ -(WINDOW_WIDTH >> 1) + (*doorarrPtr)[0]->GetSize().x * 10, GetTopEdge((*doorarrPtr)[0]) - (*doorarrPtr)[0]->GetSize().y * 10 });
				ChangeFormEventObject->userdata = std::make_shared<std::string>(MyAPP::Form::FormNames::Form_1_2);
				(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_2, "freeForm_1_2_Pipe"))->Enable = true;
				//(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_2, "UpdateHPText"))->Enable = true;
				(FM.GetFormObject<EventObject>(MyAPP::Form::FormNames::Form_1_2, "UpdatePointText"))->Enable = true;
			}
			else {
				winForm(static_cast<MyAPP::GameManager*>(data));
				ChangeFormEventObject->userdata = std::make_shared<std::string>("Win");
			}
			// initForm_1_2(static_cast<MyAPP::GameManager*>(data));
			break;
		}
	}
}

/// <summary>
/// 判斷與敵人碰撞
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::vector(std::shared_ptr(Character)) </param>
//EVENTCALLCALLBACKFUN(CheckEneyCollision) {
//	auto GM = static_cast<MyAPP::GameManager*>(data);
//	auto& FM = GM->GetFormManger();
//	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
//	auto eneys = std::static_pointer_cast<std::vector<std::shared_ptr<MyAPP::Form::Object::Character>>>(self->userdata);
//	auto marioPos = mario->GetPosition();
//	auto marioSize = mario->GetSize();
//	if (!GM->opMode) {
//		for (auto& it : *eneys) {
//			if (it->collisionable && it->inRange(marioPos, marioSize)) {
//				if (mario->isInvincible() ||  marioPos.y > it->GetPosition().y) {
//					it->died();
//					/*it->collisionable = false;
//					it->SetVisible(false);*/
//				}
//				else {
//					// (FM.GetFormObject<EventObject>(FM.GetNowForm(), "FinifhEvent"))->Enable = true;
//					/*GM->bgm->LoadMedia(Lost_a_Life);
//					GM->bgm->Play(1);*/
//					//if (it->MyType == ObjectType::Turtle && )
//					GM->DecHP();
//					mario->died();
//					GM->bgm->Pause();
//					GM->sfx->LoadMedia(MyAPP::MyResourcesFilePath::Lost_a_Life);
//					GM->sfx->Play(0);
//					(FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdateHPText"))->Enable = true;
//					if (GM->GetHP() == 0) {
//						GM->bgm->LoadMedia(MyAPP::MyResourcesFilePath::Game_Over);
//						auto sleepevent = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "SleepAllevent"));
//						sleepevent->Enable = true;
//						sleepevent->userdata.reset();
//						sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP*3, std::vector<bool>());
//						(FM.GetFormObject<EventObject>(FM.GetNowForm(), "FinifhEvent"))->Enable = true;
//						break;
//					}
//					else {
//						(FM.GetFormObject<EventObject>(FM.GetNowForm(), "GoBackCheckPoint"))->Enable = true;
//						auto sleepevent = (FM.GetFormObject<EventObject>(FM.GetNowForm(), "SleepAllevent"));
//						sleepevent->Enable = true;
//						sleepevent->userdata.reset();
//						sleepevent->userdata = std::make_shared<std::tuple<int, std::vector<bool>>>(FPS_CAP, std::vector<bool>());
//						break;
//					}
//					//std::this_thread::sleep_for(std::chrono::seconds(4));
//					//GM->bgm->Resume();
//				}
//			}
//		}
//	}
//}

/// <summary>
/// Game Over Event
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
EVENTCALLCALLBACKFUN(CallFinish) {
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto& bgm = static_cast<MyAPP::GameManager*>(data)->bgm;
	auto& sfx = static_cast<MyAPP::GameManager*>(data)->sfx;
	/*mario->changeState("DIED");
	mario->changeImg();*/
	auto& objandform = FM.GetFormAndObject(FM.GetNowForm());
	for (auto& eventobj : objandform.m_Events) {
		eventobj->Enable = false;
	}
	static_cast<MyAPP::GameManager*>(data)->pause = true;
	//std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	bgm->Play(1);
	FM.addObject(FM.GetNowForm(), std::make_shared<TextObject>("Finishtext", MyAPP::MyResourcesFilePath::MyFontPath, 20, "GameOver", Util::Color::FromName(Util::Colors::WHITE), 100));
	puts("Game Over");
}

/// <summary>
/// 判斷與旗桿碰撞
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::vector(std::shared_ptr(Brick)) </param>
EVENTCALLCALLBACKFUN(CheckFlagpoleCollision) {

	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto flagpole = std::static_pointer_cast<BrickPtrVec>(self->userdata);
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();

	for (auto& it = flagpole->begin(); it < flagpole->end(); ++it) {
		if ((*it)->inRange(marioPos, marioSize)) {
			auto f_height = static_cast<int>(it - flagpole->begin());
			static_cast<MyAPP::GameManager*>(data)->addPoint(1000 * f_height);
			printf("FlagpoleCollision.\nTouch height:%d", f_height);
			mario->down();
			self->Enable = false;
			(FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdatePointText"))->Enable = true;
			(FM.GetFormObject<EventObject>(FM.GetNowForm(), "moveToDoor"))->Enable = true;
			(FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent"))->Enable = false;
			static_cast<MyAPP::GameManager*>(data)->opMode = false;
			auto flagformpole = FM.GetFormObject<FlagFromPole>(FM.GetNowForm(), "FlagFromPole");
			if (flagformpole) {
				flagformpole->enabled = true;
			}
			auto flagformpolePosUpdate = FM.GetFormObject<EventObject>(FM.GetNowForm(), "flagformpolePosUpdate");
			if (flagformpolePosUpdate) {
				flagformpolePosUpdate->Enable = false;
			}
			break;
		}
	}
}

/// <summary>
/// 移動到大門事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::array(std::shared_ptr(Brick), 2) </param>
EVENTCALLCALLBACKFUN(moveToDoor) {
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto doorarrPtr = std::static_pointer_cast<BrickPtrVec>(self->userdata);
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto marioPos = mario->GetPosition();
	auto marioSize = mario->GetSize();
	auto&& Displacement = (int)marioSize.x >> 3;
	if (mario->GetState() == Mario::State::MOVE) {
		if (marioPos.x > (*doorarrPtr->begin())->GetPosition().x) {
			marioPos.x -= Displacement;
			mario->SetLeft<true>();
		}
		else {
			marioPos.x += Displacement;
			mario->SetLeft<false>();
		}
	}
	mario->SetPosition(marioPos);
	mario->move();
}

/// <summary>
/// 判斷與存檔點碰撞事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::vector(std::shared_ptr(CheckPoint)) </param>
//EVENTCALLCALLBACKFUN(CheckPointCollision) {
//	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
//	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
//	auto background = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "Background");
//	auto checkPoints = std::static_pointer_cast<std::vector<std::shared_ptr<CheckPoint>>>(self->userdata);
//	auto marioPos = mario->GetPosition();
//	auto marioSize = mario->GetSize();
//	auto pos = background->GetPosition();
//	for (auto& it = checkPoints->begin(); it < checkPoints->end(); ++it) {
//		if ((*it)->Enable && (*it)->inRange(marioPos, marioSize)) {
//			(*it)->Enable = false;
//			puts("CheckPoint");
//			static_cast<MyAPP::GameManager*>(data)->SaveCheckPointPos(marioPos);
//			break;
//		}
//	}
//}

/// <summary>
/// 返回存檔點事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::vector(std::shared_ptr(CheckPoint)) </param>
EVENTCALLCALLBACKFUN(GoBackCheckPoint) {
	auto& FM = static_cast<MyAPP::GameManager*>(data)->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	auto bricks = std::static_pointer_cast<BrickPtrVec>(mario->userdata);
	auto moveEvent = FM.GetFormObject<EventObject>(FM.GetNowForm(), "MoveEvent");
	auto tuplePtr = std::static_pointer_cast<GameObjectTuple>(moveEvent->userdata);
	auto& [enemys, pipes, props, objs] = (*tuplePtr);
	auto checkPoints = std::static_pointer_cast<CheckPointPtrVec>(self->userdata);
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	auto GM = static_cast<MyAPP::GameManager*>(data);
	GM->bgm->Play();
	auto& allobj = FM.GetFormAndObject(FM.GetNowForm());
	auto gobackposx = 0;
	mario->SetPosition(static_cast<MyAPP::GameManager*>(data)->GetCheckPointPos());
	mario->Reset();
	for (int i = checkPoints->size() - 1; i >= 0; --i) {
		if (!(*checkPoints)[i]->Enable) {
			gobackposx = -(*checkPoints)[i]->GetPosition().x;
			std::for_each(std::execution::seq, allobj.m_Images.begin(), allobj.m_Images.end(),
				[&](auto& obj) {
				if (obj->MyType != ObjectType::CheckPoint && obj->name!="coinimg") {
					obj->incPositionX(gobackposx);
				} });
			std::for_each(std::execution::seq, allobj.m_Characters.begin(), allobj.m_Characters.end(),
				[&](auto& obj) {
				if (obj->MyType != ObjectType::Mario) {
					obj->incPositionX(gobackposx);
					obj->Reset();
				} });
			self->Enable = false;
			break;
		}
	}
	std::for_each(std::execution::seq, checkPoints->begin(), checkPoints->end(),
		[&](auto& it) {
			it->incPositionX(gobackposx);
		});
	std::for_each(std::execution::seq, bricks->begin(), bricks->end(),
		[&](auto& it) {
			it->Reset();
		});
	std::for_each(std::execution::seq, props->begin(), props->end(),
		[&](auto& it) {
			FM.removeObject<Props::Props>(FM.GetNowForm(), it->m_ID);
		});
	props->clear();
}

/// <summary>
/// 更新HP文字事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
EVENTCALLCALLBACKFUN(UpdateHPText) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto text = FM.GetFormObject<TextObject>(FM.GetNowForm(), "HPText");
	std::unique_ptr<char> textstr(new char[10]);
	sprintf(textstr.get(), "HP:%d", GM->GetHP());
	std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(textstr.get());
	self->Enable = false;
}

/// <summary>
/// 判斷Mario座標事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
EVENTCALLCALLBACKFUN(CheckMarioPosition) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto mario = FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario");
	if (!isInWindow(mario) && mario->GetPosition().y < 0) {
		GM->LostALife();
		//(FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdateHPText"))->Enable = true;
		if (GM->GetHP() == 0) {
			(FM.GetFormObject<EventObject>(FM.GetNowForm(), "FinifhEvent"))->Enable = true;
		}
		else {
			(FM.GetFormObject<EventObject>(FM.GetNowForm(), "GoBackCheckPoint"))->Enable = true;
		}
	}
}

/// <summary>
/// 暫停所有事件事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::vector(std::tuple(int, std::vector(bool))) </param>
EVENTCALLCALLBACKFUN(SleepAllevent) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	/// <summary> count 暫停的幀數 
	/// bvec 原本事件的狀態 </summary>
	auto& [count, bvec] = (*std::static_pointer_cast<SleepAllEventUserDataType>(self->userdata));
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
			for (int i = 0; i < allevent.size(); ++i) {
				if (allevent[i]->name == self->name) {
					allevent[i]->Enable = false;
					continue;
				}
				allevent[i]->Enable = bvec[i];
			}
		}
	}
}

/// <summary>
/// 判斷與金幣碰撞事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::vector(std::shared_ptr(Coin)) </param>
//EVENTCALLCALLBACKFUN(CheckCoinsCollision) {
//	auto GM = static_cast<MyAPP::GameManager*>(data);
//	auto& FM = GM->GetFormManger();
//	auto mario = (FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario"));
//	auto coins = std::static_pointer_cast<std::vector<std::shared_ptr<Coin>>>(self->userdata);
//	auto marioPos = mario->GetPosition();
//	auto marioSize = mario->GetSize();
//	for (auto& it : *coins) {
//		if (it->GetVisibility() && it->inRange(marioPos, marioSize)) {
//			it->bonk();
//			GM->addPoint(100);
//			(FM.GetFormObject<EventObject>(FM.GetNowForm(), "UpdatePointText"))->Enable = true;
//		}
//	}
//}

/// <summary>
/// 更新分數事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
EVENTCALLCALLBACKFUN(UpdatePointText) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto text = FM.GetFormObject<TextObject>(FM.GetNowForm(), "PointText");
	/// <summary>分數文字</summary>
	std::unique_ptr<char> textstr(new char[10]);
	sprintf(textstr.get(), "%06d", GM->GetPoint());
	std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(textstr.get());
	//self->Enable = false;
}

/// <summary>
/// 龜殼碰撞事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata"> *std::vector(std::shared_ptr(Turtle)) </param>
//EVENTCALLCALLBACKFUN(CheckTortoiseShellCollision) {
//	auto GM = static_cast<MyAPP::GameManager*>(data);
//	auto& FM = GM->GetFormManger();
//	auto mario = (FM.GetFormObject<Mario>(FM.GetNowForm(), "Mario"));
//	auto turtles = std::static_pointer_cast<std::vector<std::shared_ptr<Turtle>>>(self->userdata);
//	auto marioPos = mario->GetPosition();
//	auto marioSize = mario->GetSize();
//	for (auto& it : *turtles) {
//		if (it->diedFlag && it->GetVisibility() && it->inRange(marioPos, marioSize)) {
//			//auto turtlePos{ it->GetPosition() };
//			if (it->GetPosition().x > marioPos.x) {
//				it->SetLeft<false>();
//				it->setMoveFlag(true);
//			}
//			else {
//				it->SetLeft<true>();
//				it->setMoveFlag(true);
//			}
//			//it->SetPosition(turtlePos);
//		}
//	}
//}

///// <summary>
///// 道具碰撞事件
///// </summary>
///// <param name=""></param>
//EVENTCALLCALLBACKFUN(CheckPropsCollision) {
//	
//}



/// <summary>
/// 改變表單事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata">切換目的表單</param>
EVENTCALLCALLBACKFUN(ChangeFormEvent) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto form = std::static_pointer_cast<std::string>(self->userdata);
	if (form == nullptr) {
		form = std::make_shared<std::string>("null");
	}
	self->Enable = false;
	if (*form == "Form_1_1") {
		GM->bgm->LoadMedia(MyAPP::MyResourcesFilePath::Ground_Theme);
		GM->bgm->Play(-1);
	}
	else if (*form == "Form_1_1_Pipe") {
		GM->bgm->LoadMedia(MyAPP::MyResourcesFilePath::Underground_Theme);
		GM->bgm->Play(-1);
	}
	else if (*form == "Form_1_2" || *form == "Form_1_2_Pipe") {
		GM->bgm->LoadMedia(MyAPP::MyResourcesFilePath::Underground_Theme);
		GM->bgm->Play(-1);
	}
	FM.changeForm(*form);
	// std::cout << "now form is:" <<  * form << '\n';
	//auto& bgm = std::make_shared<Util::BGM>();
}

/// <summary>
/// 釋放表單事件
/// </summary>
/// <param name="self">指向當前物件的指標</param>
/// <param name="data">GameManager *</param>
/// <param name="self->userdata">目標表單</param>
EVENTCALLCALLBACKFUN(freeForm) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	FM.freeForm(*std::static_pointer_cast<std::string>(self->userdata));
	self->Enable = false;
	//auto& m_Events = FM.GetFormAndObject(FM.GetNowForm()).m_Events;
	
	// m_Events.erase(std::find_if(m_Events.begin(), m_Events.end(), [&](auto& i) { return i->name == self->name; }));
}

EVENTCALLCALLBACKFUN(UpdateFrameCount) {
	static size_t frameCount = 0;
	static size_t coinimgIndex = 0;
	frameCount++;
	if (frameCount % 10 == 0) {
		QuestionBlock::nextFrame();
		Coin::nextFrame();
		coinimgIndex = (coinimgIndex + 1) % 6;
		auto GM = static_cast<MyAPP::GameManager*>(data);
		auto& FM = GM->GetFormManger();
		auto coinimg = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "coinimg");
		if (coinimg) {
			std::static_pointer_cast<Util::Image>(coinimg->GetDrawable())->SetImage(Coin::GetFrames()[coinimgIndex]);
		}
	}
	if (frameCount % 3 == 0) {
		PiranaPlant::nextFrame();
	}
	frameCount %= 15;
}

EVENTCALLCALLBACKFUN(UpdateCoinCountText) {
	auto GM = static_cast<MyAPP::GameManager*>(data);
	auto& FM = GM->GetFormManger();
	auto text = FM.GetFormObject<TextObject>(FM.GetNowForm(), "CoinnumText");
	if (text) {
		auto coinimg = FM.GetFormObject<ImageObject>(FM.GetNowForm(), "coinimg");
		coinimg->SetPosition((text)->GetPosition() - glm::vec2{ coinimg->GetSize().x + (text)->GetSize().x / 2, 0 });
		if (GM->coinCount >= 100) {
			GM->coinCount -= 100;
			GM->IncHP();
		}
		std::unique_ptr<char> buffer(new char[10]);
		std::sprintf(buffer.get(), "x%02d", GM->coinCount);
		std::static_pointer_cast<Util::Text>(text->GetDrawable())->SetText(buffer.get());
	}
}

#endif