#ifndef GAME_H_
#define GAME_H_


#include "general.h"
#include "turtle.h"
#include "menu.h"

const int FRAME_RATE_LIMIT = 120;
const std::string GAME_TITLE = "Turtix";
const std::string TEXTURES_DIR = "resources/textures";
const std::string FONTS_DIR = "resources/fonts";
const std::string FONTS_NAME = "coffe-cake.ttf";
enum IT_MODE{IT_MENU, IT_PLAY, IT_SHOP, IT_OUTRO, IT_EXIT};
using namespace sf;
using namespace std;

class Game{
    private:
        Menu* menu;
        Clock clock;
        bool endGame;
        RenderWindow *window;
        VideoMode videoMode;
        View view;
        Vector2f viewOffset;
        string path;
        Event sfmlEvent;
        Font* font;
        IT_MODE mode;
        void initVariables();
        void initWindow();
        void close();
        void pollEvents();
        bool hasTimePassed();
        Turtle *turtle; // temp
    public:
        bool keyPressed;
        Game();
        virtual ~Game();
        bool isRunning();
        void update();
        void render();
        void turnOnKeyPress();
        void turnOffKeyPress();
        void setViewPos();
        bool isTicked();
};


#endif // GAME_H_
