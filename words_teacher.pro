#-------------------------------------------------
#
# Project created by QtCreator 2015-04-13T09:55:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../bin/words_teacher
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    wordwt.cpp \
    word_teacher.cpp

HEADERS  += window.h \
    wordwt.h \
    word_teacher.h

FORMS    += window.ui
