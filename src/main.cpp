#include "config.hpp"
#include "MyContext.hpp"
#include "GameManager.hpp"

#include <iostream>
#include <fstream>


int main(int, char**) {
    
    auto context = Core::Context::GetInstance();
    GameManager gameManger;
    gameManger.init();
    SDL_SetWindowTitle(context->GetWindow(), "My Super Mario");
    context->SetWindowWidth(WINDOW_WIDTH);
    context->SetWindowHeight(WINDOW_HEIGHT);
    SDL_SetWindowSize(context->GetWindow(), WINDOW_WIDTH, WINDOW_HEIGHT);
    //SDL_SetWindowResizable(context->GetWindow(), SDL_bool::SDL_FALSE);
    //SDL_SetWindowDisplayMode()
    auto displaymode = std::make_shared<SDL_DisplayMode>();
    //displaymode->format 
    //displaymode->
    std::cout << SDL_GetWindowDisplayMode(context->GetWindow(), displaymode.get());
    //SDL_SetWindowPosition(context->GetWindow(), 1920, 100);
    auto render = SDL_GetRenderer(context->GetWindow());
    SDL_RenderDrawLine(render, 0, 0, 1000, 1000);
    SDL_RenderPresent(render);
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
