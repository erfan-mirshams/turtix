#ifndef BABY_H_
#define BABY_H_

#include "general.h"
#include "sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
using namespace std;
using namespace sf;

const int BB_INITIAL_VELOCITY = 15;
const int BB_ACTIONS_CNT = 3;
const int BB_ACTIONS_PIX_CNT[BB_ACTIONS_CNT] = {5, 8, 4};
const string BB_DIR = "baby";
const string BB_ACTIONS_PATHS[BB_ACTIONS_CNT] = {"idle", "run", "die"};
const string BB_ACTIONS_FORMAT[BB_ACTIONS_CNT] = {".png", ".png", ".png"};
const float BB_ZOOM = 1.5;
enum BB_ACTION{BB_IDLE, BB_RUN, BB_DIE};

class Baby{
private:
    Clock clock;
    Sprite* sprite;
    Vector2i initPosGrid;
    int velocity;
    int spriteInd;
    BB_ACTION action;
    bool visible;
    DIRECTION dir;
public:
    bool isTicked();
    bool isVisible();
    void incrementMovement(const vector< vector<Texture*> > &textures);
    void die();
    bool finishedDie();
    Sprite* getSprite();
    void respawn();
    void setDir(DIRECTION _d);
    Baby(int x, int y);
    virtual ~Baby();
};

class BabyList{
private:
    vector< vector<Texture*> > textures;
    string path;
public:
    vector<Baby*> babies;
    BabyList(string _path, vector< vector<int> > mp);
    void initializeTextures();
    void incrementMovement(int ind);
    void draw(RenderWindow* window);
    virtual ~BabyList();
};
#endif // BABY_H_
