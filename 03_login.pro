#-------------------------------------------------
#
# Project created by QtCreator 2023-09-26T16:04:04
#
#-------------------------------------------------

QT       += core gui sql  multimedia
QT += multimedia
#LIBS += -lssl -lcrypto

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 03_login
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    login.cpp \
    function.cpp \
    weather.cpp \
    mydata.cpp \
    music.cpp \
    game.cpp \
    game_minesweeping.cpp \
    array.cpp \
    dialog.cpp

HEADERS += \
    MyPlaylist.h \
        widget.h \
    login.h \
    function.h \
    weather.h \
    mydata.h \
    music.h \
    game.h \
    game_minesweeping.h \
    array.h \
    dialog.h \
    data.h

FORMS += \
        widget.ui \
    login.ui \
    function.ui \
    weather.ui \
    mydata.ui \
    music.ui \
    game.ui \
    game_minesweeping.ui

RESOURCES += \
    music.qrc \
    picture.qrc \
    mine_sp_picture.qrc \
    weather.qrc \
