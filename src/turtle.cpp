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
    sprite -> setPosition(percentage(50, WIDTH), percentage(10, HEIGHT)); //test
    initializeTextures(path);
    sprite -> setScale(TURTLE_ZOOM, TURTLE_ZOOM);
    onGround = false;
    ghost = false;
}

bool Turtle::interrupt(){
    return (action == TURT_ATTACK || action == TURT_HURT);
}

bool Turtle::isTicked(){
    if(clock.getElapsedTime() >= TICKING_TIME){
        clock.restart();
        return true;
    }
    return false;
}

bool Turtle::isTickedGhost(){
    if(flickerClock.getElapsedTime() >= GHOST_TIME){
        ghost = false;
        return true;
    }
    return false;
}

// bool Turtle::onGround(){
//     auto rect = sprite -> getGlobalBounds();
//     if(rect.top + rect.height >= percentage(50, HEIGHT)){
//         return true;
//     }
//     return false;
// }
//
void Turtle::turnOnGroundOn(){
    onGround = true;
}

bool Turtle::finishedAttack(){
    return (action == TURT_ATTACK && spriteInd == ACTIONS_PIX_CNT[TURT_ATTACK] - 1);
}

bool Turtle::finishedHurt(){
    return (action == TURT_HURT && spriteInd == ACTIONS_PIX_CNT[TURT_HURT] - 1);
}

bool Turtle::isAttacking(){
    return (action == TURT_ATTACK);
}

void Turtle::incrementMovement(){
    if(action == NA || !isTicked()){
        return;
    }
    if(ghost){
        if(!isTickedGhost()){
            flicker(sprite);
        }
        else{
            Color tempCol = sprite -> getColor();
            tempCol.a = COLOR_SIZE;
            sprite -> setColor(tempCol);
        }
    }
    sprite -> move(velocityX, velocityY);
    velocityY += accelerationY;
    velocityY = min(velocityY, 3 * INITIAL_VELOCITY_Y);
    if(onGround){
        jumpCap = INITIAL_JUMP_CAP;
        if(action == TURT_JUMP){
            action = TURT_IDLE;
        }
    }
    if(finishedAttack()){
        action = TURT_IDLE;
    }
    if(finishedHurt()){
        action = TURT_IDLE;
    }
    spriteInd++;
    spriteInd %= ACTIONS_PIX_CNT[action];
    fitTextureInSprite(sprite, textures[action][spriteInd]);
    if(changedDir){
        flipSprite(sprite);
        changedDir = false;
    }
    onGround = false;
}

void Turtle::moveRight(){
    if(interrupt()){
        return;
    }
    velocityX = max(INITIAL_VELOCITY_X / 2, velocityX + INITIAL_ACCELERATION_X);
    velocityX = min(INITIAL_VELOCITY_X, velocityX);
    if(action != TURT_JUMP){
        action = TURT_RUN;
    }
    if(dir == LEFT){
        changedDir = true;
    }
    dir = RIGHT;
}

void Turtle::moveLeft(){
    if(interrupt()){
        return;
    }
    velocityX = min(INITIAL_VELOCITY_X / (-2), velocityX - INITIAL_ACCELERATION_X);
    velocityX = max(-INITIAL_VELOCITY_X, velocityX);
    if(action != TURT_JUMP){
        action = TURT_RUN;
    }
    if(dir == RIGHT){
        changedDir = true;
    }
    dir = LEFT;
}

void Turtle::jump(){
    if(jumpCap == 0 || interrupt()){
        return;
    }
    velocityY = -INITIAL_VELOCITY_Y;
    sprite -> move(0, velocityY);
    action = TURT_JUMP;
    onGround = false;
    jumpCap--;
}

void Turtle::attack(){
    if(interrupt() || action == TURT_JUMP){
        return;
    }
    fixHorizontalMovement();
    action = TURT_ATTACK;
    spriteInd = NA;
}

void Turtle::ghostMode(){
    ghost = true;
    flickerClock.restart();
}

void Turtle::hurt(){
    if(interrupt() || ghost){
        return;
    }
    action = TURT_HURT;
    ghostMode();
    spriteInd = NA;
}

void Turtle::fixHorizontalMovement(){
    if(interrupt() || action == TURT_JUMP){
        return;
    }
    velocityX = 0;
}

void Turtle::fixTurtle(){
    if(interrupt()){
        return;
    }

    action = (abs(velocityY) < 5 * INITIAL_ACCELERATION_Y)? TURT_IDLE : TURT_JUMP;
}

Sprite* Turtle::getSprite(){
    return sprite;
}

void Turtle::manageWallImpact(Sprite* wall){
    FloatRect wallBound = wall -> getGlobalBounds();
    FloatRect turtBound = sprite -> getGlobalBounds();
    DIRECTION impactDir = (DIRECTION)whichDirectionAreColliding(sprite, wall);
    if(impactDir == LEFT){
        sprite -> move(wallBound.left - (turtBound.left + turtBound.width), 0);
        velocityX /= 2;
    }
    if(impactDir == RIGHT){
        sprite -> move(wallBound.left + wallBound.width - turtBound.left, 0);
        velocityX /= 2;
    }
    if(impactDir == TOP){
        sprite -> move(0, wallBound.top - (turtBound.top + turtBound.height));
        turnOnGroundOn();
        velocityY = 0;
    }
    if(impactDir == BOTTOM){
        sprite -> move(0, wallBound.top + wallBound.height - turtBound.top);
        velocityY = 0;
    }
}

bool Turtle::isGhost(){
    return ghost;
}

bool Turtle::manageEnemyImpact(Sprite *enemy){
    cout << "IN GERE" << endl;
    FloatRect enemBound = enemy -> getGlobalBounds();
    FloatRect turtBound = sprite -> getGlobalBounds();
    DIRECTION impactDir = (DIRECTION)whichDirectionAreColliding(sprite, enemy);
    if(impactDir == TOP){
        velocityY = -INITIAL_VELOCITY_Y;
        sprite -> move(0, enemBound.top - (turtBound.top + turtBound.height));
        return true;
    }
    return false;
}

Turtle::~Turtle(){
    delete sprite;
    for(int i = 0; i < (int)textures.size(); i++){
        for(int j = 0; j < (int)textures[i].size(); j++){
            delete textures[i][j];
        }
    }
}
