#include "headers/game.h"
#include <QApplication>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Game* game = new Game();
    game->show();

    return app.exec();
}
