#include "../include/level.h"

Level::Level(RenderWindow* _window, View* _view, Font* _font, string _path){
    window = _window;
    view = _view;
    font = _font;
    path = _path;
    viewOffset = Vector2f(0, 0);
    turtle = new Turtle(path + DIR_DELIM + TEXTURES_DIR);
}

void Level::setViewPos(){
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
    view -> setCenter(view -> getCenter() + offset);
    viewOffset += offset;
}

void Level::draw(){
    window -> setView(*view);
    window->draw(*(turtle->getSprite()));
    Vector2i pos;
    pos = getPosGrid(turtle->getSprite());
    cout << "POS GRID: " << pos.x << " " << pos.y << endl;
    window -> setView(window -> getDefaultView());
}

void Level::incrementMovements(){
    turtle -> incrementMovement();
    setViewPos();
}

void Level::fixTurtle(){
    turtle -> fixHorizontalMovement();
    turtle -> fixTurtle();
}

void Level::SpaceKeyPress(){
    turtle -> attack();
}

void Level::upKeyPress(){
    turtle -> jump();
}

void Level::rightKeyPress(){
    turtle -> moveRight();
}

void Level::leftKeyPress(){
    turtle -> moveLeft();
}

View* Level::getView(){
    return view;
}

Level::~Level(){
    view -> setCenter(view -> getCenter() - viewOffset);
    delete turtle;
}
