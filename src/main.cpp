#include "config.hpp"
#include "MyContext.hpp"
#include "GameManager.hpp"
#include "FormProfile.hpp"

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;
unsigned int FPS_CAP = 60;
int WINDOW_POS_X = SDL_WINDOWPOS_UNDEFINED;
int WINDOW_POS_Y = SDL_WINDOWPOS_UNDEFINED;


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
            break;
        }
        gameManger.Update(context);
        context->Update();
    }
    if (context->GetRestart()) {
        system("start Super_Mario.exe");
    }
    return 0;
}
