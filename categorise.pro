#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T00:09:34
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = categorise
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -L/usr/include/taglib/ -ltag
