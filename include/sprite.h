#ifndef SPRITE_H_
#define SPRITE_H_

#include "general.h"
using namespace sf;

void loadTrimmedTexture(Texture* texture, string fileName);
void fitTextureInSprite(Sprite* sprite, Texture* texture);
void flipSprite(Sprite* sprite);
Vector2i getPosWindow(Sprite* sprite);
Vector2i getPosGrid(Sprite* sprite);
Vector2f getPosView(Sprite* sprite, RenderWindow* window);

#endif // SPRITE_H_
