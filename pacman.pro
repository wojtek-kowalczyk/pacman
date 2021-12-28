######################################################################
# Automatically generated by qmake (3.1) Tue Dec 28 16:38:47 2021
######################################################################

QT+=widgets
QT+=gui
TEMPLATE = app
TARGET = pacman
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += headers/board.h \
           headers/collectible.h \
           headers/config.h \
           headers/enemy.h \
           headers/enemyRed.h \
           headers/entity.h \
           headers/game.h \
           headers/player.h
SOURCES += sources/board.cpp \
           sources/enemy.cpp \
           sources/enemyRed.cpp \
           sources/entity.cpp \
           sources/game.cpp \
           sources/main.cpp \
           sources/player.cpp \
           sources/scorepoint.cpp
