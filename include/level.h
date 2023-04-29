#ifndef LEVEL_H_
#define LEVEL_H_

#include "general.h"
#include "turtle.h"
using namespace sf;

const std::string TEXTURES_DIR = "textures";

class Level{
    private:
    View* view;
    Font* font;
    Turtle* turtle;
    RenderWindow* window;
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
    void setViewPos();
    void fixTurtle();
    void incrementMovements();
    void draw();
};

#endif // LEVEL_H_
