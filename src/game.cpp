#include "../include/general.h"
#include "../include/game.h"
#include <SFML/Window/Keyboard.hpp>

void Game::initVariables(){
    endGame = false;
    path = removeFinalTwoDirsFromPath(getExecutablePath());
    turtle = new Turtle(path + DIR_DELIM + TEXTURES_DIR);
    font = new Font();
    font -> loadFromFile(path + DIR_DELIM + FONTS_DIR + DIR_DELIM + FONTS_NAME);
    menu = new Menu(font);
    mode = IT_MENU;
}

void Game::initWindow(){
    videoMode = VideoMode(WIDTH, HEIGHT);
    view.setSize(WIDTH, HEIGHT);
    view.setCenter(WIDTH / 2.0, HEIGHT / 2.0);
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

void Game::pollEvents(){
    keyPressed = false;
    while(window -> pollEvent(sfmlEvent)){
        clock.restart();
        if(sfmlEvent.type == Event::Closed){
          endGame = true;
        }
        if(mode == IT_MENU){
            if(sfmlEvent.type == Event::KeyPressed) {
                if (sfmlEvent.key.code == Keyboard::W ||
                    sfmlEvent.key.code == Keyboard::Up ||
                    sfmlEvent.key.code == Keyboard::K) {
                    menu -> moveUp();
                }
                if (sfmlEvent.key.code == Keyboard::S ||
                    sfmlEvent.key.code == Keyboard::Down ||
                    sfmlEvent.key.code == Keyboard::J) {
                    menu -> moveDown();
                }
            }
        }
        else{
            if(sfmlEvent.type == Event::KeyPressed) {
                keyPressed = true;
                if (sfmlEvent.key.code == Keyboard::D ||
                    sfmlEvent.key.code == Keyboard::Right ||
                    sfmlEvent.key.code == Keyboard::L) {
                    turtle->moveRight();
                }
                if (sfmlEvent.key.code == Keyboard::A ||
                    sfmlEvent.key.code == Keyboard::Left ||
                    sfmlEvent.key.code == Keyboard::H) {
                    turtle->moveLeft();
                }
            }
            if (sfmlEvent.type == Event::KeyReleased) {
                keyPressed = true;
                if (sfmlEvent.key.code == Keyboard::W ||
                    sfmlEvent.key.code == Keyboard::Up ||
                    sfmlEvent.key.code == Keyboard::K) {
                    turtle->jump();
                }
                if (sfmlEvent.key.code == Keyboard::Space) {
                    turtle->attack();
                }
            }
        }
    }
}

void Game::setViewPos(){
    Vector2i pos = getPosWindow(turtle -> getSprite());
    Vector2f offset(0, 0);
    int leftMargin = percentage(BOX_PERCENTAGE_LIMIT, WIDTH) + viewOffset.x;
    if(pos.x < leftMargin){
        offset.x = pos.x - leftMargin;
    }
    int rightMargin = percentage(PERCENTAGE_AMOUNT - BOX_PERCENTAGE_LIMIT, WIDTH) + viewOffset.x;
    if(pos.x > rightMargin){
        offset.x = pos.x - rightMargin;
    }
    int topMargin = percentage(BOX_PERCENTAGE_LIMIT, HEIGHT) + viewOffset.y;
    if(pos.y < topMargin){
        offset.y = pos.y - topMargin;
    }
    int bottomMargin = percentage(PERCENTAGE_AMOUNT - BOX_PERCENTAGE_LIMIT, HEIGHT) + viewOffset.y;
    if(pos.y > bottomMargin){
        offset.y = pos.y - bottomMargin;
    }
    view.setCenter(view.getCenter() + offset);
    viewOffset += offset;
}

void Game::update(){
    if(endGame){
        close();
    }
    pollEvents();
    if(mode == IT_MENU){

    }
    else{
        if(!keyPressed && isTicked()){
            turtle -> fixHorizontalMovement();
            turtle -> fixTurtle();
        }
        turtle -> incrementMovement();
        setViewPos();
    }
}

bool Game::isTicked(){
    if(clock.getElapsedTime() >= LEVEL_TIMEOUT){
        clock.restart();
        return true;
    }
    return false;
}

void Game::render(){
    window -> clear();
    if(mode == IT_MENU){
        menu -> draw(window);
    }
    else{
        window->setView(view);
        window->draw(*(turtle->getSprite()));
        Vector2i pos;
        pos = getPosGrid(turtle->getSprite());
        cout << "POS GRID: " << pos.x << " " << pos.y << endl;
        window->setView(window->getDefaultView());
    }
    window -> display();
}

Game::~Game(){
    delete window;
    delete turtle;
    delete font;
}

void Game::close(){
    window -> close();
}
