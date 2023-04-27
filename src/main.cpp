#include "../include/game.h"
#include "../include/general.h"

int main() {
    Game game;
    srand(time(NULL));

    while(game.isRunning()){
        game.update();
        game.render();
    }

    return 0;
}
