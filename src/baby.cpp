#include "../include/baby.h"
#include <SFML/Graphics/Rect.hpp>

void BabyList::initializeTextures(){
    textures.resize(BB_ACTIONS_CNT);
    for(int i = 0; i < BB_ACTIONS_CNT; i++){
      for (int j = 0; j < BB_ACTIONS_PIX_CNT[i]; j++) {
        textures[i].push_back(new Texture);
        loadTrimmedTexture(textures[i][j], path + DIR_DELIM + BB_ACTIONS_PATHS[i] + NAME_DELIM + to_string(j) + BB_ACTIONS_FORMAT[i]);
      }
    }
}

bool Baby::isTicked(){
    if(clock.getElapsedTime() >= TICKING_TIME){
        clock.restart();
        return true;
    }
    return false;
}

bool Baby::isVisible(){
    return visible;
}

Sprite* Baby::getSprite(){
    return sprite;
}

void Baby::respawn(){
    action = BB_IDLE;
    sprite -> setPosition(initPosGrid.x * GRID_SIZEF, initPosGrid.y * GRID_SIZEF);
    spriteInd = 0;
    velocityY = 0;
}

Baby::Baby(int x, int y){
    initPosGrid = Vector2i(x, y);
    visible = true;
    dir = RIGHT;
    velocityX = BB_INITIAL_VELOCITY;
    sprite = new Sprite();
    respawn();
    sprite -> setScale(BB_ZOOM, BB_ZOOM);
}

bool Baby::isActive(){
    return (action == BB_RUN);
}

void Baby::die(){
    if(!isActive()){
        return;
    }
    action = BB_DIE;
    spriteInd = NA;
}

bool Baby::finishedDie(){
    return (spriteInd == BB_ACTIONS_PIX_CNT[BB_DIE] - 1);
}

void Baby::incrementMovement(const vector<vector<Texture *>> &textures){
    if(!isTicked() || !isVisible()){
        return;
    }
    if(action == BB_DIE && finishedDie()){
        respawn();
    }
    spriteInd++;
    spriteInd %= BB_ACTIONS_PIX_CNT[action];
    fitTextureInSprite(sprite, textures[action][spriteInd]);
    if(action == BB_RUN && velocityY == 0){
        sprite -> move(velocityX, 0);
    }
    sprite -> move(0, velocityY);
    velocityY += BB_INITIAL_ACCELERATION;
    velocityY = min(velocityY, 2 * BB_INITIAL_VELOCITY);
}

void Baby::setDir(DIRECTION _d){
    if(_d == dir){
        return;
    }
    if(_d == LEFT){
        velocityX = -BB_INITIAL_VELOCITY;
        dir = LEFT;
    }
    if(_d == RIGHT){
        velocityX = BB_INITIAL_VELOCITY;
        dir = RIGHT;
    }
    flipSprite(sprite);
}

void Baby::manageWallImpact(Sprite *wall){
    if(!isVisible()){
        return;
    }
    FloatRect wallBound = wall -> getGlobalBounds();
    FloatRect babBound = sprite -> getGlobalBounds();
    DIRECTION impactDir = (DIRECTION)whichDirectionAreColliding(sprite, wall);
    if(impactDir == LEFT){
        sprite -> move(wallBound.left - (babBound.left + babBound.width), 0);
        setDir(LEFT);
    }
    if(impactDir == RIGHT){
        sprite -> move(wallBound.left + wallBound.width - babBound.left, 0);
        setDir(RIGHT);
    }
    if(impactDir == TOP){
        sprite -> move(0, wallBound.top - (babBound.top + babBound.height));
        velocityY = 0;
    }
}

void Baby::manageTurtleImpact(Sprite *turt){
    if(!isVisible()){
        return;
    }
    FloatRect turtBound = turt -> getGlobalBounds();
    FloatRect babBound = sprite -> getGlobalBounds();
    DIRECTION impactDir = (DIRECTION)whichDirectionAreColliding(sprite, turt);
    action = BB_RUN;
    if(impactDir == LEFT){
        sprite -> move(turtBound.left - (babBound.left + babBound.width), 0);
        setDir(LEFT);
    }
    if(impactDir == RIGHT){
        sprite -> move(turtBound.left + turtBound.width - babBound.left, 0);
        setDir(RIGHT);
    }
}

void Baby::managePortalImpact(){
    visible = false;
}

Baby::~Baby(){
    delete sprite;
}

BabyList::BabyList(string _path, vector< vector<int> > mp){
    _path += DIR_DELIM + TEXTURES_DIR + DIR_DELIM + BB_DIR;
    path = _path;
    initializeTextures();
    for(int i = 0; i < (int)mp.size(); i++){
        for(int j = 0; j < (int)mp[i].size(); j++){
            if(mp[i][j] != ENT_BABY){
                continue;
            }
            babies.push_back(new Baby(j, i));
        }
    }
}

void BabyList::incrementMovement(int ind){
    babies[ind] -> incrementMovement(textures);
}

void BabyList::draw(RenderWindow *window){
    for(int i = 0; i < (int)babies.size(); i++){
        if(babies[i] -> isVisible()){
            window -> draw(*(babies[i] -> getSprite()));
        }
    }
}

BabyList::~BabyList(){
    for(int i = 0; i < (int)babies.size(); i++){
        delete babies[i];
    }
    for(int i = 0; i < (int)textures.size(); i++){
        for(int j = 0; j < (int)textures[i].size(); j++){
            delete textures[i][j];
        }
    }
}
