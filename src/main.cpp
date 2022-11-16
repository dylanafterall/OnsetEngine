// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// main.cpp
//  designated entry point to Onset Engine program
// -----------------------------------------------------------------------------

#include "core_game.h"

int main(int argc, char* argv[]) {
    Game game;

    // pre loop
    game.initialize();
    game.setup();

    // game loop
    game.run();

    // post loop
    game.destroy();

    return 0;
}
