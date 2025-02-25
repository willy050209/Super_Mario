#include "Mario.hpp"
#include "Util/Input.hpp"

void Mario::move(const float& d)
{
    auto tmp = GetPosition();
    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        tmp.y += d;
    }
    /*else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        tmp.y -= d;
    }*/
    else if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        tmp.x += d;
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        tmp.x -= d;
    }
    SetPosition(tmp);
}
