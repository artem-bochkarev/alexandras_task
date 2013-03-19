TEMPLATE = app
TARGET = Policlinic
DESTDIR = ../Debug
QT += core gui
CONFIG += debug
DEFINES += QT_LARGEFILE_SUPPORT
INCLUDEPATH += ./GeneratedFiles \
    ./GeneratedFiles/Debug \
    .
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
TRANSLATIONS += translate_en.ts \
	translate_ru.ts
include(../Policlinic.pri)
