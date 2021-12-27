#pragma once
#include "headers/player.h"
#include <QGraphicsPixmapItem>
#include <QObject>

class Collectible : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  protected:
    int points;

  public:
    Collectible(int value, QPixmap sprite);
  public slots:
    void collect();
  signals:
    void collected(int value);
};