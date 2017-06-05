#-------------------------------------------------
#
# Project created by QtCreator 2017-06-03T15:04:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoolFarm
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    windownuevapartida.cpp \
    arbolbinario.cpp \
    avl.cpp \
    heap.cpp \
    mercadoplataforma.cpp \
    controladorhilos.cpp \
    hiloabb.cpp \
    hiloavl.cpp \
    hiloheap.cpp \
    hilorojinegro.cpp \
    hiloplagas.cpp \
    generadorplagas.cpp \
    hilocuervos.cpp \
    hiloovejas.cpp

HEADERS  += mainwindow.h \
    windownuevapartida.h \
    arbolbinario.h \
    arbolescomprados.h \
    avl.h \
    estructurastablero.h \
    heap.h \
    mercadoplataforma.h \
    controladorhilos.h \
    hiloabb.h \
    hiloavl.h \
    hiloheap.h \
    hilorojinegro.h \
    hiloplagas.h \
    generadorplagas.h \
    hilocuervos.h \
    hiloovejas.h

FORMS    += mainwindow.ui \
    windownuevapartida.ui

RESOURCES += \
    imagenes.qrc
