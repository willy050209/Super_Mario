#include "Mario.hpp"
#include "Util/Input.hpp"
#include "config.hpp"

void Mario::behavior(void* data)
{
    move();
    jump();
    comeDown();
}

void Mario::jump() noexcept
{
    if (state == State::UP) {
        auto tmp = GetPosition();
        tmp.y += displacement;
        SetPosition(tmp);
        displacement -= 1.0;
        if (displacement <= 0) {
            state = State::DOWN;
            displacement = DEFAULTDISPLACEMENT;
        }
    }
    
}

void Mario::comeDown() noexcept
{
    if (state != State::UP && GetPosition().y > 0) {
        auto tmp = GetPosition();
        tmp.y -= displacement;
        SetPosition(tmp);
        if (GetPosition().y == 0) {
            state = State::MOVE;
        }
    }
}

void Mario::move(const float& d)
{
    auto tmp = GetPosition();
    if (Util::Input::IsKeyPressed(Util::Keycode::UP) && state == State::MOVE) {
        state = State::UP;
        displacement = 2 * DEFAULTDISPLACEMENT;
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        tmp.x += d;
        index++;
        if(index % 10 == 0)
        {
            if (index >= 20) {
                index = 0;
            }
            setImage(imgs[index/10]);
            
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        tmp.x -= d;
        index++;
        if (index % 10 == 0)
        {
            if (index >= 20) {
                index = 0;
            }
            setImage(imgs[index / 10]);

        }
    }
    SetPosition(tmp);
}
