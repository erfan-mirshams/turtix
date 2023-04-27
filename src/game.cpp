#include "../include/general.h"
#include "../include/game.h"

void Game::initVariables(){
    endGame = false;
    path = removeFinalTwoDirsFromPath(getExecutablePath());
    turtle = new Turtle(path + DIR_DELIM + TEXTURES_DIR);
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
    if(!keyPressed){
        turtle -> fixTurtle();
    }
    turtle -> incrementMovement();
    setViewPos();
}

void Game::render(){
    window -> clear();
    window -> setView(view);
    window -> draw(*(turtle -> getSprite()));
    window -> setView(window -> getDefaultView());
    window -> display();
}

Game::~Game(){
    delete window;
    delete turtle;
}

void Game::close(){
    window -> close();
}
