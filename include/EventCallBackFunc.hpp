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
    void** voidarr = (std::static_pointer_cast<void*>(self->userdata).get());
    auto& background = *((std::shared_ptr<ImageObject>*) * voidarr);
    auto& mario = *((std::shared_ptr<Mario>*)(void*)((char*)voidarr[0] + sizeof(void*)));
    if (Util::Input::IsKeyPressed(Util::Keycode::UP) && (mario)->GetState() == Mario::State::MOVE) {
        (mario)->jump();
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        auto pos = (background)->GetPosition();
        if (mario->GetPosition().x!=0 && pos.x == GetX0(background) ) {
            mario->SetPosition({ mario->GetPosition().x + 10,mario->GetPosition().y });
        }
        else if(pos.x > -GetX0(background))
        {
            pos.x-=10;
        }
        else if (mario->GetPosition().x < (WINDOW_WIDTH / 2) - mario->GetSize().x)
        {
            mario->SetPosition({ mario->GetPosition().x + 10,mario->GetPosition().y });
        }
        (background)->SetPosition(pos);
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        auto pos = (background)->GetPosition();
        if (mario->GetPosition().x != 0 && pos.x == -GetX0(background)) {
            mario->SetPosition({ mario->GetPosition().x - 10,mario->GetPosition().y });
        }
        else if (pos.x < GetX0(background))
        {
            pos.x += 10;
        }
        else if (mario->GetPosition().x > (-WINDOW_WIDTH / 2) + mario->GetSize().x)
        {
            mario->SetPosition({ mario->GetPosition().x - 10,mario->GetPosition().y });
        }
        (background)->SetPosition(pos);
    }
}
#endif