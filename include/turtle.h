#ifndef TURTLE_H_
#define TURTLE_H_

#include "general.h"
#include "sprite.h"
using namespace std;
using namespace sf;

const int INITIAL_JUMP_CAP = 2;
const int TURT_INITIAL_LIFE = 3;
const int INITIAL_VELOCITY_Y = 30;
const int INITIAL_ACCELERATION_Y = 2;
const int INITIAL_ACCELERATION_X = 5;
const int INITIAL_VELOCITY_X = 30;
const int ACTIONS_CNT = 6;
const int ACTIONS_PIX_CNT[ACTIONS_CNT] = {5, 8, 8, 22, 6, 5};
const string TURTLE_DIR = "turtle";
const string ACTIONS_PATHS[ACTIONS_CNT] = {"idle", "run", "jump", "attack", "hurt", "die"};
const string ACTIONS_FORMAT[ACTIONS_CNT] = {".png", ".png", ".png", ".png", ".png", ".png"};
const float TURTLE_ZOOM = 2;
enum ACTION {TURT_IDLE, TURT_RUN, TURT_JUMP, TURT_ATTACK, TURT_HURT, TURT_DIE};

class Turtle{
private:
    Clock clock;
    Clock flickerClock;
    DIRECTION dir;
    bool changedDir;
    int action;
    int spriteInd;
    int jumpCap;
    vector< vector<Texture*> > textures;
    Sprite *sprite;
    int accelerationY;
    bool onGround;
    bool ghost;
    int life;
public:
    int velocityY;
    int velocityX;
    Turtle(string path, Vector2f pos);
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
    void hurt();
    void die();
    bool interrupt();
    void turnOnGroundOn();
    bool finishedAttack();
    bool finishedHurt();
    bool finishedDie();
    bool isDead();
    void ghostMode();
    void manageWallImpact(Sprite* wall);
    bool manageEnemyImpact(Sprite* enemy);
    bool isTicked();
    bool isTickedGhost();
    bool isGhost();
    bool isAttacking();
};

#endif // TURTLE_H_
