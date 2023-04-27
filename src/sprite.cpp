#include "../include/sprite.h"

void fitTextureInSprite(Sprite* sprite, Texture* texture){
    sprite -> setTexture(*texture);
    Vector2u textureSz = texture -> getSize();
    sprite -> setTextureRect(IntRect(0, 0, textureSz.x, textureSz.y));
}
