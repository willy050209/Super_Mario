
#include "Core/Context.hpp"
#include "Util/Input.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();

    while (!context->GetExit()) {
        if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
            context->SetExit(true);
        }
        context->Update();
    }
    return 0;
}
