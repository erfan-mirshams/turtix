#ifndef TURTLE_H_
#define TURTLE_H_

#include "general.h"
#include "sprite.h"
using namespace std;
using namespace sf;

const int INITIAL_VELOCITY_Y = 0;
const int INITIAL_ACCELERATION_Y = 1;
const int INITIAL_VELOCITY_X = 15;
const int ACTIONS_CNT = 3;
const int ACTIONS_PIX_CNT[ACTIONS_CNT] = {8, 8, 0};
const string ACTIONS_PATHS[ACTIONS_CNT] = {"turtle-walk-right", "turtle-walk-left", "TBD"};
const string ACTIONS_FORMAT[ACTIONS_CNT] = {".png", ".png", "TBD"};
enum IMG_NAME {TURT_RIGHT_WALK, TURT_LEFT_WALK, TURT_JUMP};

class Turtle{
    private:
    Clock clock;
    int action;
    int spriteInd;
    vector< vector<Texture*> > textures;
    Sprite *sprite;
    Vector2i posGrid;
    Vector2f posView;
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
    bool onGround();
    void moveY();
};

#endif // TURTLE_H_
