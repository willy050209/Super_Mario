#include "config.hpp"
#include "MyContext.hpp"
#include "GameManager.hpp"
#include "FormProfile.hpp"

unsigned int WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720, FPS_CAP = 60;
int WINDOW_POS_X = SDL_WINDOWPOS_UNDEFINED, WINDOW_POS_Y = SDL_WINDOWPOS_UNDEFINED;


int main(int, char**) {

    readFormProfile();

    auto context = Core::Context::GetInstance();

    GameManager gameManger;
    gameManger.init();

    //SDL_SetWindowTitle(context->GetWindow(), "My Super Mario");
    context->SetWindowIcon(MY_RESOURCE_DIR"/image/ICON/Untitled.png");

    while (!context->GetExit()) {
        if (gameManger.isEnd()) {
            writeFormProfile(context);
            context->SetExit(true);
        }
        gameManger.Update(context);
        context->Update();
    }
    return 0;
}
