# -------------------------------------------------
# Project created by QtCreator 2009-12-03T12:16:29
# -------------------------------------------------

QT       += core gui
TARGET = ../bin/editor
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    editorarea.cpp \
    editortilepallete.cpp \
    mediator.cpp \
    addwizard.cpp \
    npcpreviewarea.cpp \
    loadgamepicker.cpp \
    dialognpcedit.cpp \
    dialogobjectedit.cpp
HEADERS += mainwindow.h \
    editorarea.h \
    editortilepallete.h \
    mediator.h \
    format/file_map.h \
    format/file_game.h \
    defines.h \
    addwizard.h \
    ../common/format/file_game.h \
    ../common/format/file_map.h \
    addwizard.h \
    ../common/format/file_npc.h \
    ../common/shared.h \
    npcpreviewarea.h \
    loadgamepicker.h \
    ../game/include/types.h \
    dialognpcedit.h \
    ../game/include/sound_ps2.h \
    ../game/include/sound_nds.h \
    ../game/include/config.h \
    ../common/format/file_npc.h \
    ../common/format/file_map.h \
    ../common/format/file_game.h \
    ../common/format/file_object.h \
    dialogobjectedit.h
FORMS += mainwindow.ui \
    addwizard.ui \
    loadgamepicker.ui \
    dialognpcedit.ui \
    dialogobjectedit.ui
LIBS = -lmingw32 -lSDLmain -lSDL -mwindows -lqtmaind

RESOURCES += resources/icons/icons.qrc
CONFIG += console
INCLUDEPATH += ../common
OTHER_FILES += ../docs/RoadMap \
    ../docs/ChangeLog.txt
