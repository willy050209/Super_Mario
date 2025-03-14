#ifndef EVENTCALLCALLBACKFUNC_hpp
#define EVENTCALLCALLBACKFUNC_hpp

#include "incallobj.hpp"
#include "config.hpp"
#include "util/Input.hpp"
#include "Position.hpp"

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
        std::cout << "�ثe�ɶ��G" << std::ctime(&time);
        (*num) = 0;
    }
}

EVENTCALLCALLBACKFUN(moveEvent) {
    constexpr auto Displacement = 4;
    auto tuplePtr = std::static_pointer_cast<std::tuple<std::shared_ptr<ImageObject>, std::shared_ptr<Mario>>>(self->userdata);
    auto& background = std::get<std::shared_ptr<ImageObject>>(*tuplePtr);
    auto& mario = std::get<std::shared_ptr<Mario>>(*tuplePtr);
    auto bricks = std::static_pointer_cast<std::vector<std::shared_ptr<ImageObject>>>(background->userdata);
    bool flag = true;
    auto tmp = mario->GetPosition();
    if (Util::Input::IsKeyPressed(Util::Keycode::UP) && (mario)->GetState() == Mario::State::MOVE) {
        (mario)->jump();
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        auto pos = (background)->GetPosition();
        for (auto& it : *bricks) {
            if (it->inRange({ tmp.x + Displacement + mario->GetSize().x / 2,tmp.y })) {
                flag = false;
            }
        }
        if (mario->GetPosition().x!=0 && pos.x == GetX0(background) && flag ) {
            mario->SetPosition({ mario->GetPosition().x + Displacement,mario->GetPosition().y });
        }
        else if(pos.x > -GetX0(background) && flag)
        {
            pos.x-= Displacement;
            for (auto& it : *bricks) {
                it->SetPosition({ it->GetPosition().x - Displacement,it->GetPosition().y });
            }
        }
        else if (mario->GetPosition().x < (WINDOW_WIDTH / 2) - mario->GetSize().x && flag)
        {
            mario->SetPosition({ mario->GetPosition().x + Displacement,mario->GetPosition().y });
        }
        if(flag)
            (background)->SetPosition(pos);
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        auto pos = (background)->GetPosition();
        for (auto& it : *bricks) {
            if (it->inRange({ tmp.x - Displacement - mario->GetSize().x / 2,tmp.y })) {
                flag = false;
            }
        }
        if (mario->GetPosition().x != 0 && pos.x == -GetX0(background) && flag) {
            mario->SetPosition({ mario->GetPosition().x - Displacement,mario->GetPosition().y });
        }
        else if (pos.x < GetX0(background) && flag)
        {
            pos.x += Displacement;
            for (auto& it : *bricks) {
                it->SetPosition({ it->GetPosition().x + Displacement,it->GetPosition().y });
            }
        }
        else if (mario->GetPosition().x > (-WINDOW_WIDTH / 2) + mario->GetSize().x && flag)
        {
            mario->SetPosition({ mario->GetPosition().x - Displacement,mario->GetPosition().y });
        }
        if(flag)
            (background)->SetPosition(pos);
        
    }
}
#endif