#ifndef LEVEL_H_
#define LEVEL_H_

#include "general.h"
#include "turtle.h"
#include "ground.h"
#include "enemy.h"
#include "baby.h"
#include "portal.h"
#include <fstream>
using namespace sf;

const std::string MAPS_DIR = "maps";
const std::string MAPS_PREFIX = "map";
const std::string MAPS_FORMAT = ".txt";
const int ENTITY_CNT = 11;
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
};

#endif // LEVEL_H_
