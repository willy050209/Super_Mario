#include "Mario.hpp"
#include "Object/ImageObject.hpp"
#include "Util/Input.hpp"
#include "config.hpp"

void Mario::behavior(void* data)
{
    //move();
    doJump();
    comeDown();
}

void Mario::doJump() noexcept
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
    /*if (userdata.get() != nullptr)
    {
        auto tmp = std::static_pointer_cast<ImageObject>(userdata)->GetPosition();
        if (Util::Input::IsKeyPressed(Util::Keycode::UP) && state == State::MOVE) {
            state = State::UP;
            displacement = 2 * DEFAULTDISPLACEMENT;
        }
        else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
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
        else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
            tmp.x += d;
            index++;
            if (index % 10 == 0)
            {
                if (index >= 20) {
                    index = 0;
                }
                setImage(imgs[index / 10]);

            }
        }
        std::static_pointer_cast<ImageObject>(userdata)->SetPosition(tmp);
    }*/
}
