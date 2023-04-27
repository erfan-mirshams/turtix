#include "../include/sprite.h"

void fitTextureInSprite(Sprite* sprite, Texture* texture){
    sprite -> setTexture(*texture);
    Vector2u textureSz = texture -> getSize();
    sprite -> setTextureRect(IntRect(0, 0, textureSz.x, textureSz.y));
}

Vector2i getPosWindow(Sprite* sprite){
    return (static_cast<Vector2i>(sprite -> getPosition()));
}

Vector2f getPosView(Sprite* sprite, RenderWindow* window){
    return window -> mapPixelToCoords(static_cast<Vector2i>(sprite -> getPosition()));
}
