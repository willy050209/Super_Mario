
#include "MyContext.hpp"
#include "GameManager.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    GameManager gameManger;
    gameManger.init();
    SDL_SetWindowTitle(context->GetWindow(), "My Super Mario");
    context->SetWindowWidth(1600);
    context->SetWindowHeight(900);
    SDL_SetWindowResizable(context->GetWindow(), SDL_bool::SDL_FALSE);
    
    SDL_SetWindowSize(context->GetWindow(), 1600, 900);
    context->SetWindowIcon(MY_RESOURCE_DIR"/image/ICON/Untitled.png");
    while (!context->GetExit()) {
        if (gameManger.isEnd()) {
            context->SetExit(true);
        }
        gameManger.Update(context);
        context->Update();
    }
    return 0;
}
