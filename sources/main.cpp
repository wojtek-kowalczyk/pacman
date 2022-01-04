#include "headers/game.h"
#include <QApplication>

// this app leaks about 5-7 MB, most of which still reachable so I assume it's mostly Qt
// * might want to read up on this:
// https://stackoverflow.com/questions/14073483/how-to-make-qt-gui-apps-in-c-without-memory-leaks
// also, sort out parenting issues
// also, I encountered: "Floating point exception (core dumped)" // ? probly fixed?

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Game* game = new Game();
    game->show();

    return app.exec();
}
