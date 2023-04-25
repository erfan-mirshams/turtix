#include "../include/general.h"
#include "../include/game.h"

void Game::initVariables(){
    endGame = false;
}

void Game::initWindow(){
    videoMode = VideoMode(WIDTH, HEIGHT);
    window = new RenderWindow(videoMode, GAME_TITLE, Style::None);
    window -> setFramerateLimit(FRAME_RATE_LIMIT);
}

bool Game::isRunning(){
    return (!endGame && window -> isOpen());
}

Game::Game(){
    initVariables();
    initWindow();
}

void Game::draw(RenderTarget *target, Sprite sprite){
    target -> draw(sprite);
}

void Game::pollEvents(){
    while(window -> pollEvent(sfmlEvent)){
        if(sfmlEvent.type == Event::Closed){
            endGame = true;
        }
    }
}

void Game::update(){
    if(endGame){
        close();
    }
    pollEvents();
}

void Game::render(){
    window -> clear();
    window -> display();
}

Game::~Game(){
    delete window;
}

void Game::close(){
    window -> close();
}
