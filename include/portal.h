#ifndef PORTAL_H_
#define PORTAL_H_

#include "general.h"
#include "sprite.h"
using namespace std;
using namespace sf;

const int PORTAL_CNT = 4;
const string PORTAL_DIR = "portal";
const string PORTAL_PATH = "portal";
const string PORTAL_FORMAT = ".png";
const float PORTAL_ZOOM = 1.5;

class Portal{
private:
    Clock clock;
    Sprite *sprite;
    int spriteInd;
    string path;
    vector<Texture*> textures;
public:
    void loadTextures();
    void incrementMovement();
    bool isTicked();
    Sprite* getSprite();
    Portal(string _path, const vector< vector<int> > &mp);
    virtual ~Portal();
};

#endif // PORTAL_H_
