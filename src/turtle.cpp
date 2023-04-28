#include "../include/turtle.h"
#include "../include/general.h"

void Turtle::initializeTextures(string path){
    textures.resize(ACTIONS_CNT);
    for(int i = 0; i < ACTIONS_CNT; i++){
      for (int j = 0; j < ACTIONS_PIX_CNT[i]; j++) {
        textures[i].push_back(new Texture);
        loadTrimmedTexture(textures[i][j], path + DIR_DELIM + ACTIONS_PATHS[i] + NAME_DELIM + to_string(j) + ACTIONS_FORMAT[i]);
      }
    }
}

Turtle::Turtle(string path){
    dir = RIGHT;
    changedDir = false;
    jumpCap = 0;
    path += DIR_DELIM + TURTLE_DIR;
    action = TURT_IDLE;
    spriteInd = 0;
    velocityY = 0;
    velocityX = 0;
    accelerationY = INITIAL_ACCELERATION_Y;
    sprite = new Sprite();
    sprite -> setPosition(percentage(50, WIDTH), percentage(40, HEIGHT)); //test
    initializeTextures(path);
    sprite -> setScale(TURTLE_ZOOM, TURTLE_ZOOM);
}

bool Turtle::interrupt(){
    return (action == TURT_JUMP || action == TURT_ATTACK);
}

bool Turtle::isTicked(){
    if(clock.getElapsedTime() >= TICKING_TIME){
        clock.restart();
        return true;
    }
    return false;
}

bool Turtle::onGround(){
    auto rect = sprite -> getGlobalBounds();
    if(rect.top + rect.height >= percentage(50, HEIGHT)){
        return true;
    }
    return false;
}

bool Turtle::finishedAttack(){
    return (action == TURT_ATTACK && spriteInd == ACTIONS_PIX_CNT[TURT_ATTACK] - 1);
}

void Turtle::incrementMovement(){
    if(action == NA || !isTicked()){
        return;
    }
    sprite -> move(velocityX, velocityY);
    velocityY += accelerationY;
    if(onGround()){
        velocityY = 0;
        jumpCap = INITIAL_JUMP_CAP;
        if(action == TURT_JUMP){
            action = TURT_IDLE;
        }
        auto rect = sprite -> getGlobalBounds();
        sprite -> move(0, percentage(50, HEIGHT) - rect.top - rect.height);
    }
    if(finishedAttack()){
        action = TURT_IDLE;
    }
    spriteInd++;
    spriteInd %= ACTIONS_PIX_CNT[action];
    fitTextureInSprite(sprite, textures[action][spriteInd]);
    if(changedDir){
        cout << "DONE" << endl;
        flipSprite(sprite);
        changedDir = false;
    }
}

void Turtle::moveRight(){
    if(interrupt()){
        return;
    }
    velocityX = INITIAL_VELOCITY_X;
    action = TURT_RUN;
    if(dir == LEFT){
        cout << "LL" << endl;
        changedDir = true;
    }
    dir = RIGHT;
}

void Turtle::moveLeft(){
    if(interrupt()){
        return;
    }
    velocityX = -INITIAL_VELOCITY_X;
    action = TURT_RUN;
    if(dir == RIGHT){
        cout << "LL" << endl;
        changedDir = true;
    }
    dir = LEFT;
}

void Turtle::jump(){
    cout << "HARA" << endl;
    if(jumpCap == 0 || action == TURT_ATTACK){
        return;
    }
    velocityY = -INITIAL_VELOCITY_Y;
    action = TURT_JUMP;
    jumpCap--;
}

void Turtle::attack(){
    if(interrupt()){
        return;
    }
    velocityX = 0;
    action = TURT_ATTACK;
    spriteInd = NA;
}

void Turtle::fixHorizontalMovement(){
    if(!interrupt()){
        velocityX = 0;
    }
}

void Turtle::fixTurtle(){
    if(!interrupt()){
        action = TURT_IDLE;
    }
}

Sprite* Turtle::getSprite(){
    return sprite;
}

Turtle::~Turtle(){
    delete sprite;
    for(int i = 0; i < (int)textures.size(); i++){
        for(int j = 0; j < (int)textures[i].size(); j++){
            delete textures[i][j];
        }
    }
}
