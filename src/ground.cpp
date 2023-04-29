#include "../include/ground.h"

void Ground::loadTextures(){
    for(int i = 0; i < GROUND_CNT; i++){
        textures.push_back(new Texture);
        loadTrimmedTexture(textures[i], path + DIR_DELIM + TEXTURES_DIR + DIR_DELIM + GROUND_DIR + DIR_DELIM + GROUND_PREFIX + NAME_DELIM + intToBinaryString(i) + GROUND_FORMAT);
    }
}

Ground::Ground(string _path, vector< vector<int> > mp){
    path = _path;
    loadTextures();
    for(int i = 0; i < (int)mp.size(); i++){
        for(int j = 0; j < (int)mp[i].size(); j++){
            if(mp[i][j] != ENT_GROUND){
                continue;
            }
            int state = 0;
            for(int d = 0; d < GRID_DIR_CNT; d++){
                if(mp[i + DIRY[d]][j + DIRX[d]] == ENT_GROUND){
                    state ^= (1 << d);
                }
            }
            float zoom = GRID_SIZEF / textures[state] -> getSize().x;
            sprites.push_back(new Sprite);
            int k = (int)sprites.size() - 1;
            fitTextureInSprite(sprites[k], textures[state]);
            sprites[k] -> setScale(sprites[k] -> getScale() * zoom);
            sprites[k] -> setPosition(j * GRID_SIZE, i * GRID_SIZE);
            // cout << ": " << i << " " << j  << " " << intToBinaryString(state) << endl;
        }
    }
}

vector<Sprite*> Ground::getSprites(){
    return sprites;
}

void Ground::draw(RenderWindow *window){
    for(int i = 0; i < (int)sprites.size(); i++){
        window -> draw(*sprites[i]);
    }
}

Ground::~Ground(){
    for(int i = 0; i < (int)textures.size(); i++){
        delete textures[i];
    }
    for(int i = 0; i < (int)sprites.size(); i++){
        delete sprites[i];
    }
}
