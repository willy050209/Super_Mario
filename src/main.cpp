#include "config.hpp"
#include "MyContext.hpp"
#include "GameManager.hpp"
#include "FormProfile.hpp"
#include "ImageResizer.hpp"


#include <iostream>
#include <thread>
#include <filesystem>


#define IMAGERESIZER_EXE MY_IMAGERESIZER_DIR"/ImageResizer.exe"
#define FOLDERPATH MY_RESOURCE_DIR "/super mario"
#define OUTPUTFOLDPATH "imgs/super mario"

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;
int new_WINDOW_WIDTH = 0;
int new_WINDOW_HEIGHT = 0;
unsigned int FPS_CAP = 60;
int WINDOW_POS_X = SDL_WINDOWPOS_UNDEFINED;
int WINDOW_POS_Y = SDL_WINDOWPOS_UNDEFINED;

constexpr auto ICOP_PATH = MY_RESOURCE_DIR"/image/ICON/Untitled.png";


int main(int, char** argc) {
	puts(argc[0]);
    readFormProfile();
		//#if WINDOW_WIDTH == 960
//    std::cout << "960\n";
//#else
//    std::cout << WINDOW_WIDTH << "\n";
//#endif

    //std::atomic<int> atom{0};
  //  std::thread ImageResizer([&]() {
  //      // IMAGERESIZER_EXE return 0 if completes normally else return -1
		//char callImageResize[512];
		//
		//std::snprintf(callImageResize,sizeof(callImageResize), "%s %s %s %.1f", IMAGERESIZER_EXE, FOLDERPATH, OUTPUTFOLDPATH, (WINDOW_HEIGHT) / 480.f);
		//puts(callImageResize);
		////std::snprintf(callImageResize,sizeof(callImageResize), IMAGERESIZER_EXE " " FOLDERPATH " " OUTPUTFOLDPATH " %d", WINDOW_WIDTH);
		//if (system(callImageResize) != 0) {
  //          atom++;
  //      }
  //      });

    std::thread ImageResizer([]() {
		std::filesystem::create_directory("imgs");
		total = get_all_files(FOLDERPATH);
		puts("init images");
		enlargeImages(FOLDERPATH, (WINDOW_HEIGHT) / 480.f, OUTPUTFOLDPATH);
		showProgressBar(total, total);
	});
	
    auto context = Core::Context::GetInstance();

    GameManager gameManger;
    
    context->SetWindowIcon(ICOP_PATH);

    ImageResizer.join();


	gameManger.init();
    
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
		char cmdBuf[1024];
		memset(cmdBuf, 0x00, sizeof(cmdBuf));
#if defined(_WIN64) || defined(_WIN32) || defined(WIN32)
		std::snprintf(cmdBuf, sizeof(cmdBuf), "start \"\" \"%s\"", argc[0]);
		puts(cmdBuf);
		system(cmdBuf);
#else
		
		std::snprintf(cmdBuf, sizeof(cmdBuf), "start \"\" \"%s\"", argc[0]);
		puts(cmdBuf);
		system(cmdBuf);

#endif
    }
    return 0;
}
