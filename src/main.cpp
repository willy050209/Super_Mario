#include "config.hpp"
#include "MyContext.hpp"
#include "GameManager.hpp"
#include "FormProfile.hpp"

#include <iostream>
#include <thread>
#include <atomic>



#define IMAGERESIZER_EXE MY_IMAGERESIZER_DIR"/ImageResizer.exe"
#define FOLDERPATH MY_RESOURCE_DIR
#define OUTPUTFOLDPATH "out"

int WINDOW_WIDTH = 960;
int WINDOW_HEIGHT = 540;
int new_WINDOW_WIDTH = 0;
int new_WINDOW_HEIGHT = 0;
unsigned int FPS_CAP = 60;
int WINDOW_POS_X = SDL_WINDOWPOS_UNDEFINED;
int WINDOW_POS_Y = SDL_WINDOWPOS_UNDEFINED;


constexpr auto ICOP_PATH = MY_RESOURCE_DIR"/image/ICON/Untitled.png";



int main(int, char**) {
    
    readFormProfile();
#if WINDOW_WIDTH == 960
    std::cout << "960\n";
#else
    std::cout << WINDOW_WIDTH << "\n";
#endif

    auto context = Core::Context::GetInstance();

    GameManager gameManger;

    std::atomic<int> atom;
    std::thread ImageResizer([&]() {
        // IMAGERESIZER_EXE return 0 if completes normally else return -1
        if (system(IMAGERESIZER_EXE " " FOLDERPATH " " OUTPUTFOLDPATH " 1.0") != 0) { 
            atom++;
        }
    });


    gameManger.init();
    
    context->SetWindowIcon(ICOP_PATH);

    ImageResizer.join();
    if (atom) {
        std::cerr << "Failed to initialize image\n";
        context->SetExit(true);
        exit(1);
    }

    while (!context->GetExit()) {
        if (gameManger.isEnd()) {
            writeFormProfile(context);
            context->SetExit(true);
            break;
        }
        gameManger.Update(context);
        context->Update();
    }
    if (gameManger.GetRestart()) {
        system("start Super_Mario.exe");
    }
    return 0;
}
