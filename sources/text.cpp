#include "headers/text.h"
#include <QFont>

// QGrapchisTextItem will take care of assigning the parent
Text::Text(QGraphicsItem* parent) : QGraphicsTextItem(parent)
{
    setPlainText(QString("Score: ") + QString::number(15)); // use this to update the text
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}