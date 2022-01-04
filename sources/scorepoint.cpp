#include "headers/collectible.h"
#include "headers/game.h"

Collectible::Collectible(int value, QPixmap sprite)
{
    this->points = value;
    setPixmap(sprite.scaled(sprite.rect().width() * SCALE_FACTOR, sprite.rect().height() * SCALE_FACTOR));
}

void Collectible::collect()
{
    emit collected(points);
    destroy();
}

void Collectible::destroy()
{
    delete this;
}