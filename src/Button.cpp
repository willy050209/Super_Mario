#include "Button.hpp"
#include "util/Input.hpp"
#include "config.hpp"

void Button::behavior(void* data)
{
    int x, y;
    auto e = SDL_GetMouseState(&x, &y);
	if (inRange(Util::Input::GetCursorPosition(), {1,1})) {
        setColor(ClickedColor);
        if (1 == SDL_BUTTON(e) && CallBackFunc) {
            trigger = true;
        }
    }
    else if(GetColor() == ClickedColor) {
        setColor(defultColor);
    }
    if (trigger && (SDL_BUTTON(e) == 0 || (unsigned)SDL_BUTTON(e) > 3)) {
        CallBackFunc(this, data);
        trigger = false;
    }
}
