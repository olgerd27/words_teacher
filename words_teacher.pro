#-------------------------------------------------
#
# Project created by QtCreator 2015-04-13T09:55:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ./bin/words_teacher
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    wordwt.cpp \
    word_teacher.cpp \
    results_controller.cpp \
    words_reader.cpp

HEADERS  += window.h \
    wordwt.h \
    word_teacher.h \
    results_controller.h \
    reimplemented_widgets.h \
    words_reader.h

FORMS    += window.ui

OTHER_FILES +=
