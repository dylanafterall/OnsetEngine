// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// main.cpp
//  designated entry point to Onset Engine program
// -----------------------------------------------------------------------------

#include "core_game.hpp"

int main(int argc, char* argv[]) {
    Game game;

    // pre - game loop
    game.initialize();
    game.setup();

    // game loop
    game.run();

    // post - game loop
    game.destroy();

    return 0;
}
