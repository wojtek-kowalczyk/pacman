#include "headers/collectible.h"
Collectible::Collectible(int value, QPixmap sprite)
{
    this->points = value;
    setPixmap(sprite.scaled(sprite.rect().width() * SCALE_FACTOR, sprite.rect().height() * SCALE_FACTOR));
}

#include "headers/game.h"
#include <iostream>
void Collectible::collect()
{
    // todo - start from here:
    // deleting this collectible is fine here, but as of now it gets deleted 2nd time
    // in Game::removePoints(). this specific object instance must be removed from game->points
    // vector before deleting it.
    // idea 1: serach the vector for "this" pointer
    // idea 2: get rid of the vector, find a better way.
    //          (I need the vector for removing lefotovers on restart and winning the game)
    //          (winning - easy - can be solved with a counter)
    emit collected(points); // I hope this is passed by value since I'm deleting the object
                            // todo - I have to remove it from game->points list before deleting
                            //? is there a better way than just scan, find and remove?

    // https://stackoverflow.com/questions/30191586/qt-graphics-view-find-item-in-scene
    // for (QGraphicsItem* item : game->scene->items())
    // {
    //     Collectible* col = qgraphicsitem_cast<Collectible*>(item);
    //     if (!col)
    //         continue;
    //     std::cout << "found a collectible\n";
    // }

    delete this;
}