#include "headers/collectible.h"
Collectible::Collectible(int value, QPixmap sprite)
{
    this->points = value;
    setPixmap(sprite.scaled(sprite.rect().width() * SCALE_FACTOR, sprite.rect().height() * SCALE_FACTOR));
}
Collectible::~Collectible()
{
    collect();
}

void Collectible::collect()
{
    emit collected(points); // I hope this is passed by value since I'm deleting the object
}