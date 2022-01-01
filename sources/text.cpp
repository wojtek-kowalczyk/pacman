#include "headers/text.h"
#include <QFont>

// QGrapchisTextItem will take care of assigning the parent
CustomText::CustomText(QGraphicsItem* parent) : QGraphicsTextItem(parent)
{
    set(0);
    setDefaultTextColor(Qt::white);
    setFont(QFont("times", 24));
}

void CustomText::set(int score)
{
    setPlainText(QString("Score: ") + QString::number(score));
}