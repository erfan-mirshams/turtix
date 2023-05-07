#ifndef ENEMY_H_
#define ENEMY_H_

#include "general.h"
#include "sprite.h"
using namespace std;
using namespace sf;

const Color ENEMY_COLOR = Color(236, 199, 240);
const Time PROTECT_TIME = seconds(3);
const int ENEMY_VELOCITY = 20;
const int ENEMY_INITIAL_LIFE = 2;
const int ENM_ACTIONS_CNT = 5;
const int ENM_ACTIONS_PIX_CNT[ENM_ACTIONS_CNT] = {8, 1, 8, 4, 4};
const string ENEMY_DIR = "enemy";
const string ENM_ACTIONS_PATHS[ENM_ACTIONS_CNT] = {"run", "protect", "attack", "hurt", "die"};
const string ENM_ACTIONS_FORMAT[ENM_ACTIONS_CNT] = {".png", ".png", ".png", ".png", ".png"};
const float ENEMY_ZOOM = 2.5;
enum ENM_ACTION{ENM_RUN, ENM_PROTECT, ENM_ATTACK, ENM_HURT, ENM_DIE};

class Enemy{
private:
    Clock clock;
    Clock hurtClock;
    Clock protectClock;
    Sprite* sprite;
    DIRECTION dir;
    int left;
    int right;
    int velocity;
    int spriteInd;
    ENM_ACTION action;
    bool isMortal;
    bool visible;
    int life;
public:
    void incrementMovement(const vector< vector<Texture*> > &textures);
    void protect();
    bool isTicked();
    bool isTickedGhost();
    bool protectTicked();
    void attack();
    bool finishedAttack();
    void hurt();
    void die();
    bool finishedDie();
    Sprite* getSprite();
    bool isGhost();
    bool isVisible();
    bool canBeHurt();
    void ghostMode();
    bool isDead();
    void dieForGood();
    Enemy(int l, int r, int gridX, int gridY);
    virtual ~Enemy();
};

class EnemyList{
private:
    vector< vector<Texture*> > textures;
    string path;
public:
    vector<Enemy*> enemies;
    EnemyList(string _path, vector< vector<int> > mp);
    void initializeTextures();
    void incrementMovement(int ind);
    void draw(RenderWindow* window);
    virtual ~EnemyList();
};

#endif // ENEMY_H_
