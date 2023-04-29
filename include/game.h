#ifndef GAME_H_
#define GAME_H_


#include "general.h"
#include "menu.h"
#include "level.h"

const int FRAME_RATE_LIMIT = 120;
const int NUMBER_OF_MODES = 5;
const std::string GAME_TITLE = "Turtix";
const std::string RESOURCES_DIR = "resources";
const std::string FONTS_DIR = "fonts";
const std::string FONTS_NAME = "coffe-cake.ttf";
enum IT_MODE{IT_MENU, IT_PLAY, IT_SHOP, IT_OUTRO, IT_EXIT};
using namespace sf;
using namespace std;

const Color colors[NUMBER_OF_MODES] = {Color::Black, Color(36, 3, 28), Color::Black, Color::Black, Color::Black };

class Game{
    private:
        Menu* menu;
        Clock clock;
        bool endGame;
        RenderWindow *window;
        VideoMode videoMode;
        View* view;
        Color windowColor;
        Vector2f viewOffset;
        string path;
        Event sfmlEvent;
        Font* font;
        IT_MODE mode;
        Level* level;
        void initVariables();
        void close();
        void pollEvents();
        bool hasTimePassed();
    public:
        bool keyPressed;
        Game();
        virtual ~Game();
        bool isRunning();
        void update();
        void render();
        void turnOnKeyPress();
        void turnOffKeyPress();
        bool isTicked();
        void menuHandleEvent();
        void menuRender();
        void levelHandleEvent();
        void levelUpdate();
        void levelRender();
};


#endif // GAME_H_
