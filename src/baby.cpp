#include "../include/baby.h"

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
}

Baby::Baby(int x, int y){
    initPosGrid = Vector2i(x, y);
    visible = true;
    dir = RIGHT;
    velocity = BB_INITIAL_VELOCITY;
    sprite = new Sprite();
    respawn();
    sprite -> setScale(BB_ZOOM, BB_ZOOM);
}

void Baby::die(){
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
    cout << "INJA?" << endl;
    spriteInd++;
    spriteInd %= BB_ACTIONS_PIX_CNT[action];
    fitTextureInSprite(sprite, textures[action][spriteInd]);
    if(action == BB_RUN){
        sprite -> move(velocity, 0);
    }
}

void Baby::setDir(DIRECTION _d){
    if(_d == dir){
        return;
    }
    if(_d == LEFT){
        velocity = -BB_INITIAL_VELOCITY;
        dir = LEFT;
    }
    if(_d == RIGHT){
        velocity = BB_INITIAL_VELOCITY;
        dir = RIGHT;
    }
}

Baby::~Baby(){
    delete sprite;
}

BabyList::BabyList(string _path, vector< vector<int> > mp){
    cout << "IN" << endl;
    _path += DIR_DELIM + TEXTURES_DIR + DIR_DELIM + BB_DIR;
    path = _path;
    initializeTextures();
    for(int i = 0; i < (int)mp.size(); i++){
        for(int j = 0; j < (int)mp[i].size(); j++){
            if(mp[i][j] != ENT_BABY){
                continue;
            }
            cout << ":: " << i << " " << j << endl;
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
