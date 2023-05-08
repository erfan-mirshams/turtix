#ifndef LEVEL_H_
#define LEVEL_H_

#include "general.h"
#include "turtle.h"
#include "ground.h"
#include "enemy.h"
#include "baby.h"
#include "portal.h"
#include <fstream>
using namespace std;
using namespace sf;

const string MAPS_DIR = "maps";
const string MAPS_PREFIX = "map";
const string MAPS_FORMAT = ".txt";
const int ENTITY_CNT = 11;
const int NUMBER_OF_LEVELS = 2;
const char ENTITY_CHAR[ENTITY_CNT] = {'T', '.', '$', 'E', 'M', 'O', '^', '*', 'H', '|', 'B'};

int charToEntId(char c);

struct GridItem{
    Vector2i pos;
    Sprite* sprite;
    ENTITY type;
    GridItem(Vector2i _pos, ENTITY _type, Sprite* _sprite);
};

class Level{
    private:
    int levelNum;
    View* view;
    Font* font;
    Turtle* turtle;
    Ground* ground;
    EnemyList* enemyList;
    BabyList* babyList;
    Portal* portal;
    RenderWindow* window;
    vector<GridItem> gridPosList;
    Vector2f viewOffset;
    string path;
    int rescued;
    public:
    View* getView();
    Level(RenderWindow* _window, View* _view, Font* _font, string _path);
    virtual ~Level();
    void rightKeyPress();
    void leftKeyPress();
    void upKeyPress();
    void SpaceKeyPress();
    void vKeyPress();
    void setViewPos();
    void fixTurtle();
    void handleEnemyImpact(Enemy* enem);
    void incrementMovements();
    void draw();
    void readMap(int ind);
    void lose();
    void win();
    void tidyUp();
};

#endif // LEVEL_H_
