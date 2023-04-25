#ifndef GAME_H_
#define GAME_H_


#include "general.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int FRAME_RATE_LIMIT = 120;
const std::string GAME_TITLE = "Turtix";
using namespace sf;
using namespace std;

class Game{
    private:
        bool endGame;
        RenderWindow *window;
        Clock clock;
        VideoMode videoMode;
        Event sfmlEvent;
        void initVariables();
        void initWindow();
        void close();
        void pollEvents();
        void draw(RenderTarget *target, Sprite sprite);
        bool hasTimePassed();
    public:
        Game();
        virtual ~Game();
        bool isRunning();
        void update();
        void render();
};


#endif // GAME_H_
