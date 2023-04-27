#ifndef SPRITE_H_
#define SPRITE_H_

#include "general.h"
using namespace sf;

void fitTextureInSprite(Sprite* sprite, Texture* texture);
Vector2i getPosWindow(Sprite* sprite);
Vector2f getPosView(Sprite* sprite, RenderWindow* window);

#endif // SPRITE_H_
