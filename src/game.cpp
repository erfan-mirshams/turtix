#include "../include/general.h"
#include "../include/game.h"
#include <SFML/Window/Keyboard.hpp>

void Game::initVariables(){
    endGame = false;
    path = removeFinalTwoDirsFromPath(getExecutablePath()) + DIR_DELIM + RESOURCES_DIR;
    font = new Font();
    font -> loadFromFile(path + DIR_DELIM + FONTS_DIR + DIR_DELIM + FONTS_NAME);
    menu = new Menu(font);
    view = new View();
    videoMode = VideoMode(WIDTH, HEIGHT);
    view -> setSize(WIDTH, HEIGHT);
    view -> setCenter(WIDTH / 2.0, HEIGHT / 2.0);
    window = new RenderWindow(videoMode, GAME_TITLE, Style::None);
    window -> setFramerateLimit(FRAME_RATE_LIMIT);
    mode = IT_MENU;
    level = new Level(window, view, font, path);
}

bool Game::isRunning(){
    return (!endGame && window -> isOpen());
}

Game::Game(){
    initVariables();
}

void Game::menuHandleEvent(){
    if (sfmlEvent.type == Event::KeyPressed) {
        if (sfmlEvent.key.code == Keyboard::W ||
            sfmlEvent.key.code == Keyboard::Up ||
            sfmlEvent.key.code == Keyboard::K) {
            menu->moveUp();
        }
        if (sfmlEvent.key.code == Keyboard::S ||
            sfmlEvent.key.code == Keyboard::Down ||
            sfmlEvent.key.code == Keyboard::J) {
            menu->moveDown();
        }
        if (sfmlEvent.key.code == Keyboard::Enter ||
            sfmlEvent.key.code == Keyboard::Space ||
            sfmlEvent.key.code == Keyboard::L) {
            mode = (IT_MODE)menu->getItem();
        }
    }
}

void Game::levelHandleEvent() {
    if (sfmlEvent.type == Event::KeyPressed) {
        keyPressed = true;
        if (sfmlEvent.key.code == Keyboard::D ||
            sfmlEvent.key.code == Keyboard::Right ||
            sfmlEvent.key.code == Keyboard::L) {
            level -> rightKeyPress();
        }
        if (sfmlEvent.key.code == Keyboard::A ||
            sfmlEvent.key.code == Keyboard::Left ||
            sfmlEvent.key.code == Keyboard::H) {
            level -> leftKeyPress();
        }
        if (sfmlEvent.key.code == Keyboard::Q){
            mode = IT_MENU;
        }
    }
    if (sfmlEvent.type == Event::KeyReleased) {
        keyPressed = true;
        if (sfmlEvent.key.code == Keyboard::W ||
            sfmlEvent.key.code == Keyboard::Up ||
            sfmlEvent.key.code == Keyboard::K) {
            level -> upKeyPress();
        }
        if (sfmlEvent.key.code == Keyboard::Space) {
            level -> SpaceKeyPress();
        }
        if (sfmlEvent.key.code == Keyboard::V){
            level -> vKeyPress();
        }
    }
}

void Game::pollEvents(){
    keyPressed = false;
    while(window -> pollEvent(sfmlEvent)){
        clock.restart();
        if(sfmlEvent.type == Event::Closed || mode == IT_EXIT){
          endGame = true;
        }
        if(mode == IT_MENU){
            menuHandleEvent();
        }
        if(mode == IT_PLAY){
            levelHandleEvent();
        }
    }
}

void Game::levelUpdate(){
    if (!keyPressed && isTicked()) {
        level->fixTurtle();
    }
    level->incrementMovements();
}

void Game::update(){
    if(endGame){
        close();
    }
    pollEvents();
    if(mode == IT_MENU){

    }
    if(mode == IT_PLAY){
        levelUpdate();
    }
    else{
    }
}

bool Game::isTicked(){
    if(clock.getElapsedTime() >= LEVEL_TIMEOUT){
        clock.restart();
        return true;
    }
    return false;
}

void Game::menuRender(){
    menu -> draw(window);
}

void Game::levelRender(){
    level -> draw();
}

void Game::render(){
    window -> clear(colors[mode]);
    if(mode == IT_MENU){
        menuRender();
    }
    if(mode == IT_PLAY){
        levelRender();
    }
    window -> display();
}

Game::~Game(){
    delete window;
    delete font;
    delete level;
    delete view;
}

void Game::close(){
    window -> close();
}
