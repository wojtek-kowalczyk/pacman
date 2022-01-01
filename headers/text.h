#pragma once
#include <QGraphicsTextItem>

class CustomText : public QGraphicsTextItem
{
    Q_OBJECT
  public:
    CustomText(QGraphicsItem* parent = nullptr);
  public slots:
    void set(int score);
};