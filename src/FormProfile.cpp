#include "FormProfile.hpp"
#include "MyContext.hpp"

#include <fstream>
#include <istream>

void readFormProfile() noexcept{
    std::ifstream fin(FORMPROFILE_FILE);
    if (fin.good()) {
        fin >> WINDOW_POS_X >> WINDOW_POS_Y >> WINDOW_WIDTH >> WINDOW_HEIGHT >> FPS_CAP;
    }
    new_WINDOW_WIDTH = WINDOW_WIDTH;
    new_WINDOW_HEIGHT = WINDOW_HEIGHT;
    fin.close();
}

void writeFormProfile(std::shared_ptr<Core::Context>& context) noexcept{
    std::ofstream fout(FORMPROFILE_FILE);
    //SDL_GetWindowPosition(context->GetWindow(), &WINDOW_POS_X, &WINDOW_POS_Y);
    //SDL_GetWindowSize(context->GetWindow(), &WINDOW_WIDTH, &WINDOW_HEIGHT);
    fout.clear();
    fout << WINDOW_POS_X << ' ' << WINDOW_POS_Y << ' ' << new_WINDOW_WIDTH << ' ' << new_WINDOW_HEIGHT << ' ' << FPS_CAP;
    fout.close();
}