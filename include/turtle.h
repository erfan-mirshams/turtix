#ifndef TURTLE_H_
#define TURTLE_H_

#include "general.h"
#include "sprite.h"
using namespace std;
using namespace sf;

const int INITIAL_JUMP_CAP = 2;
const int INITIAL_VELOCITY_Y = 20;
const int INITIAL_ACCELERATION_Y = 2;
const int INITIAL_VELOCITY_X = 15;
const int ACTIONS_CNT = 4;
const int ACTIONS_PIX_CNT[ACTIONS_CNT] = {5, 8, 8, 22};
const string TURTLE_DIR = "turtle";
const string ACTIONS_PATHS[ACTIONS_CNT] = {"idle", "run", "jump", "attack"};
const string ACTIONS_FORMAT[ACTIONS_CNT] = {".png", ".png", ".png", ".png"};
const float TURTLE_ZOOM = 1.5;
enum ACTION {TURT_IDLE, TURT_RUN, TURT_JUMP, TURT_ATTACK};

class Turtle{
    private:
    Clock clock;
    DIRECTION dir;
    bool changedDir;
    int action;
    int spriteInd;
    int jumpCap;
    vector< vector<Texture*> > textures;
    Sprite *sprite;
    int accelerationY;
    int velocityY;
    int velocityX;
    bool isTicked();
    public:
    Turtle(string path);
    virtual ~Turtle();
    void initializeTextures(string path);
    void moveRight();
    void moveLeft();
    Sprite* getSprite();
    void incrementMovement();
    void fixTurtle();
    void fixHorizontalMovement();
    void jump();
    void attack();
    bool interrupt();
    bool onGround();
    bool finishedAttack();
};

#endif // TURTLE_H_