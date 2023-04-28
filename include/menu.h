#ifndef MENU_H_
#define MENU_H_

#include "general.h"
const int NUMBER_OF_ITEMS = 4;
const int FONT_SZ = 60;
const int OUTLINE_THICKNESS = 2;
const int SELECTED_THICKNESS = 4;
const Color FILL_COLOR = Color(250, 210, 67, 255);
const Color OUTLINE_COLOR = Color::White;
const string ITEMS_STR[NUMBER_OF_ITEMS] = {"PLAY", "SHOP", "OUTRO", "EXIT"};

class Menu{
    private:
    int index;
    Font* font;
    Text* items[NUMBER_OF_ITEMS];
    public:
    Menu(Font* gameFont);
    virtual ~Menu();
    void focusItem(int pre);
    void moveUp();
    void moveDown();
    int getItem();
    void draw(RenderWindow *window);
};

#endif // MENU_H_
