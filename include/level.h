#ifndef LEVEL_H_
#define LEVEL_H_

#include "general.h"
#include "menu.h"
#include "turtle.h"
#include "ground.h"
#include "enemy.h"
#include "baby.h"
#include "portal.h"
#include <fstream>
using namespace std;
using namespace sf;

const Color LOSE_COLOR = Color(147, 14, 36, 0);
const Color WIN_COLOR = Color(11, 183, 157, 0);
const Color LEVEL_BACKGROUND_COLOR = Color::Black;
const string MAPS_DIR = "maps";
const string MAPS_PREFIX = "map";
const string MAPS_FORMAT = ".txt";
const string LOSE_MESSAGE = "Game Over";
const string WIN_MESSAGE = "Congrats";
const int OPACITY_STEP = 5;
const int ENTITY_CNT = 11;
const int NUMBER_OF_LEVELS = 3;
const int LEVEL_FONT_SZ = FONT_SZ + 20;
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
    Text msgText;
    bool finishLevels;
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
    void loseMessage();
    void winMessage();
    void fixTextPosition();
    void textRender();
    void incrementMsg();
    bool isFinished();
    void restartCurrentLevel();
};

#endif // LEVEL_H_
