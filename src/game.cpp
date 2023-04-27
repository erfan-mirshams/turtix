#include "../include/general.h"
#include "../include/game.h"
#include <SFML/Window/Keyboard.hpp>

void Game::initVariables(){
    endGame = false;
    path = removeFinalTwoDirsFromPath(getExecutablePath());
    turtle = new Turtle(path + DIR_DELIM + TEXTURES_DIR);
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
    keyPressed = false;
    while(window -> pollEvent(sfmlEvent)){
        if(sfmlEvent.type == Event::Closed){
            endGame = true;
        }
        if(sfmlEvent.type == Event::KeyPressed){
            keyPressed = true;
            if(sfmlEvent.key.code == Keyboard::D || sfmlEvent.key.code == Keyboard::Right || sfmlEvent.key.code == Keyboard::L){
                turtle -> moveRight();
            }
            if(sfmlEvent.key.code == Keyboard::A || sfmlEvent.key.code == Keyboard::Left || sfmlEvent.key.code == Keyboard::H){
                turtle -> moveLeft();
            }
        }
    }
}

void Game::update(){
    if(endGame){
        close();
    }
    pollEvents();
    if(!keyPressed){
        turtle -> fixTurtle();
    }
    turtle -> incrementMovement();
}

void Game::render(){
    window -> clear();
    draw(window, *(turtle -> getSprite()));
    window -> display();
}

Game::~Game(){
    delete window;
    delete turtle;
}

void Game::close(){
    window -> close();
}
