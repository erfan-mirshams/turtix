#include "../include/enemy.h"

void EnemyList::initializeTextures(){
    textures.resize(ENM_ACTIONS_CNT);
    for(int i = 0; i < ENM_ACTIONS_CNT; i++){
      for (int j = 0; j < ENM_ACTIONS_PIX_CNT[i]; j++) {
        textures[i].push_back(new Texture);
        loadTrimmedTexture(textures[i][j], path + DIR_DELIM + ENM_ACTIONS_PATHS[i] + NAME_DELIM + to_string(j) + ENM_ACTIONS_FORMAT[i]);
      }
    }
}

bool Enemy::isTicked(){
    if(clock.getElapsedTime() >= TICKING_TIME){
        clock.restart();
        return true;
    }
    return false;
}

bool Enemy::isTickedGhost(){
    if(hurtClock.getElapsedTime() >= GHOST_TIME){
        return true;
    }
    return false;
}

bool Enemy::protectTicked(){
    if(protectClock.getElapsedTime() >= PROTECT_TIME){
        return true;
    }
    return false;
}

Enemy::Enemy(int l, int r, int gridX, int gridY){
    left = l;
    right = r;
    visible = true;
    velocity = ENEMY_VELOCITY;
    isMortal = true;
    life = ENEMY_INITIAL_LIFE;
    action = ENM_RUN;
    spriteInd = 0;
    sprite = new Sprite();
    sprite -> setPosition(gridX * GRID_SIZEF, gridY * GRID_SIZEF);
    sprite -> setScale(ENEMY_ZOOM, ENEMY_ZOOM);
    sprite -> setColor(ENEMY_COLOR);
}

void Enemy::incrementMovement(const vector< vector<Texture*> > &textures){
    if(!isTicked()){
        return;
    }
    if(action == ENM_ATTACK && finishedAttack()){
        protect();
    }
    if(action == ENM_HURT){
        if(isTickedGhost()){
            action = ENM_RUN;
            Color tempCol = sprite -> getColor();
            tempCol.a = COLOR_SIZE;
            sprite -> setColor(tempCol);
        }
        else{
            flicker(sprite);
        }
    }
    if(action == ENM_DIE && finishedDie()){
        if(isTickedGhost()){
            life = 1;
            action = ENM_RUN;
        }
        else{
            return;
        }
    }
    spriteInd++;
    spriteInd %= ENM_ACTIONS_PIX_CNT[action];
    fitTextureInSprite(sprite, textures[action][spriteInd]);
    if(action == ENM_PROTECT && !protectTicked()){
        return;
    }
    if(action == ENM_PROTECT){
        flipSprite(sprite);
        action = ENM_RUN;
        velocity = -velocity;
        isMortal = true;
    }
    if(action == ENM_RUN){
        sprite -> move(velocity, 0);
    }
    if(action == ENM_ATTACK){
        return;
    }
    int x = sprite -> getPosition().x;
    if(x < left || x > right){
        protect();
    }
}

void Enemy::attack(){
    action = ENM_ATTACK;
    spriteInd = NA;
}

bool Enemy::isGhost(){
    return action == ENM_HURT;
}

void Enemy::hurt(){
    life--;
    if(life <= 0){
        die();
        return;
    }
    action = ENM_HURT;
    spriteInd = NA;
    ghostMode();
    cout << "HURT:\n";
}

void Enemy::ghostMode(){
    hurtClock.restart();
}

void Enemy::die(){
    action = ENM_DIE;
    hurtClock.restart();
    spriteInd = NA;
}

bool Enemy::finishedAttack(){
    return (spriteInd == ENM_ACTIONS_PIX_CNT[ENM_ATTACK] - 1);
}

bool Enemy::finishedDie(){
    return (spriteInd == ENM_ACTIONS_PIX_CNT[ENM_DIE] - 1);
}

void Enemy::protect(){
    action = ENM_PROTECT;
    isMortal = false;
    protectClock.restart();
}

bool Enemy::canBeHurt(){
    return isMortal;
}

bool Enemy::isDead(){
    return action == ENM_DIE;
}

bool Enemy::isVisible(){
    return visible;
}

Sprite* Enemy::getSprite(){
    return sprite;
}

void Enemy::dieForGood(){
    visible = false;
}

Enemy::~Enemy(){
    delete sprite;
}

EnemyList::EnemyList(string _path, vector< vector<int> > mp){
    _path += DIR_DELIM + TEXTURES_DIR + DIR_DELIM + ENEMY_DIR;
    path = _path;
    initializeTextures();
    for(int i = 0; i < (int)mp.size(); i++){
        for(int j = 0; j <(int)mp[i].size(); j++){
            if(mp[i][j] != ENT_ENEMY1 || mp[i + 1][j] != ENT_GROUND){
                continue;
            }
            int l, r;
            l = r = j;
            while(mp[i + 1][l - 1] == ENT_GROUND && mp[i][l - 1] == NA){
                l--;
            }
            while(mp[i + 1][r + 1] == ENT_GROUND && mp[i][r + 1] == NA){
                r++;
            }
            cout << "ENM: " << l << " " << r << " " << j << " " << i << endl;
            enemies.push_back(new Enemy(l * GRID_SIZE, r * GRID_SIZE, j, i));
        }
    }
}

void EnemyList::incrementMovement(int ind){
    enemies[ind] -> incrementMovement(textures);
}

void EnemyList::draw(RenderWindow *window){
    for(int i = 0; i < (int)enemies.size(); i++){
        if(enemies[i] -> isVisible()){
            window -> draw(*(enemies[i] -> getSprite()));
        }
    }
}

EnemyList::~EnemyList(){
    for(int i = 0; i < (int)enemies.size(); i++){
        delete enemies[i];
    }
    for(int i = 0; i < (int)textures.size(); i++){
        for(int j = 0; j < (int)textures[i].size(); j++){
            delete textures[i][j];
        }
    }
}
