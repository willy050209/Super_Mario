#include "FormProfile.hpp"
#include "MyContext.hpp"

#include <fstream>

void readFormProfile() noexcept{
    std::ifstream fin(FORMPROFILE_FILE);
    if (fin.good()) {
        fin >> WINDOW_POS_X >> WINDOW_POS_Y >> WINDOW_WIDTH >> WINDOW_HEIGHT >> FPS_CAP;
    }
    fin.close();
}

void writeFormProfile(std::shared_ptr<Core::Context>& context) noexcept{
    std::ofstream fout(FORMPROFILE_FILE);
    SDL_GetWindowPosition(context->GetWindow(), &WINDOW_POS_X, &WINDOW_POS_Y);
    SDL_GetWindowSize(context->GetWindow(), &WINDOW_WIDTH, &WINDOW_HEIGHT);
    fout.clear();
    fout << WINDOW_POS_X << ' ' << WINDOW_POS_Y << ' ' << WINDOW_WIDTH << ' ' << WINDOW_HEIGHT << ' ' << FPS_CAP;
    fout.close();
}