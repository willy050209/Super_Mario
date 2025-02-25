
#include "Core/Context.hpp"
#include "GameManager.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    GameManager gameManger;
    
    gameManger.init();
    while (!context->GetExit()) {
        if (gameManger.isEnd()) {
            context->SetExit(true);
        }
        gameManger.Update();
        context->Update();
    }
    return 0;
}
