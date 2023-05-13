#include "../include/portal.h"

void Portal::loadTextures(){
    for(int i = 0; i < PORTAL_CNT; i++){
        textures.push_back(new Texture);
        loadTrimmedTexture(textures[i], path + DIR_DELIM + PORTAL_PATH + NAME_DELIM + to_string(i) + PORTAL_FORMAT);
    }
}

Portal::Portal(string _path, const vector< vector<int> > &mp){
    _path += DIR_DELIM + TEXTURES_DIR + DIR_DELIM + PORTAL_DIR;
    path = _path;
    loadTextures();
    sprite = new Sprite();
    bool flag = false;
    for(int i = 0; i < (int)mp.size(); i++){
        if(flag){
            break;
        }
        for(int j = 0; j < (int)mp[i].size(); j++){
            if(mp[i][j] == ENT_PORTAL){
                sprite -> setPosition(j * GRID_SIZEF, i * GRID_SIZEF);
                flag = true;
                break;
            }
        }
    }
    float zoom = GRID_SIZEF / textures[0] -> getSize().x;
    zoom *= PORTAL_ZOOM;
    sprite -> setScale(sprite -> getScale() * zoom);
    spriteInd = 0;
}

Sprite* Portal::getSprite(){
    return sprite;
}

void Portal::incrementMovement(){
    if(!isTicked(clock, TICKING_TIME)){
        return;
    }
    spriteInd++;
    spriteInd %= PORTAL_CNT;
    fitTextureInSprite(sprite, textures[spriteInd]);
}

Portal::~Portal(){
    delete sprite;
    for(int i = 0; i < (int)textures.size(); i++){
        delete textures[i];
    }
}
