#pragma once
#include "headers/player.h"
#include <QGraphicsPixmapItem>
#include <QObject>

class Collectible : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    int points;
    Collectible(int value, QPixmap sprite);
    // having destructor only to invoke the event seems wrong...
    ~Collectible(); // violation of rule of three
  public slots:
    void collect();
  signals:
    void collected(int value);
};