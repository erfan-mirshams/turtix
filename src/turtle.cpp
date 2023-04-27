#include "../include/turtle.h"
#include "../include/general.h"

void Turtle::initializeTextures(string path){
    textures.resize(ACTIONS_CNT);
    for(int i = 0; i < ACTIONS_CNT; i++){
      for (int j = 0; j < ACTIONS_PIX_CNT[i]; j++) {
        textures[i].push_back(new Texture);
        textures[i][j]->loadFromFile(path + DIR_DELIM + ACTIONS_PATHS[i] + to_string(j) + ACTIONS_FORMAT[i]);
      }
    }
}

Turtle::Turtle(string path){
    action = NA;
    spriteInd = 0;
    velocityY = 0;
    accelerationY = INITIAL_ACCELERATION_Y;
    sprite = new Sprite();
    sprite -> setPosition(percentage(50, WIDTH), percentage(50, HEIGHT)); //test
    initializeTextures(path);
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

void Turtle::incrementMovement(){
    if(action == NA || !isTicked()){
        return;
    }
    sprite -> move(velocityX, velocityY);
    spriteInd++;
    spriteInd %= ACTIONS_PIX_CNT[action];
    fitTextureInSprite(sprite, textures[action][spriteInd]);
}

void Turtle::moveRight(){
    velocityX = INITIAL_VELOCITY_X;
    action = TURT_RIGHT_WALK;
}

void Turtle::moveLeft(){
    velocityX = -INITIAL_VELOCITY_X;
    action = TURT_LEFT_WALK;
}

void Turtle::fixTurtle(){
    action = NA;
    velocityX = 0;
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
