#include "../include/menu.h"

Menu::Menu(Font* gameFont){
    font = gameFont;
    index = 0;
    for(int i = 0; i < NUMBER_OF_ITEMS; i++){
        items[i] = new Text;
        items[i] -> setFont(*font);
        items[i] -> setCharacterSize(FONT_SZ);
        items[i] -> setString(ITEMS_STR[i]);
        items[i] -> setFillColor(FILL_COLOR);
        items[i] -> setOutlineColor(OUTLINE_COLOR);
        items[i] -> setOutlineThickness(OUTLINE_THICKNESS);
        FloatRect rect = items[i] -> getLocalBounds();
        items[i] -> setPosition((WIDTH - rect.width) / 2, ((float)HEIGHT / (NUMBER_OF_ITEMS + 1) * (i + 1)));
    }
}

Menu::~Menu(){
    for(int i = 0; i < NUMBER_OF_ITEMS; i++){
        delete items[i];
    }
}

void Menu::focusItem(int pre){
    items[pre] -> setOutlineThickness(OUTLINE_THICKNESS);
    items[index] -> setOutlineThickness(SELECTED_THICKNESS);
}

void Menu::moveUp(){
    int pre = index;
    index = calMod(index - 1, NUMBER_OF_ITEMS);
    focusItem(pre);
}

void Menu::moveDown(){
    int pre = index;
    index = calMod(index + 1, NUMBER_OF_ITEMS);
    focusItem(pre);
}

int Menu::getItem(){
    return index + 1;
}

void Menu::draw(RenderWindow *window){
    for(int i = 0; i < NUMBER_OF_ITEMS; i++){
        window -> draw(*(items[i]));
    }
}
