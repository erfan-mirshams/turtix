#include "../include/game.h"
#include "../include/general.h"

int main(int argc, char *argv[]) {
    Game game;
    srand(time(NULL));

    while(game.isRunning()){
        game.update();
        game.render();
    }

    return 0;
}
