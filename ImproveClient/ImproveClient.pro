#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T22:58:48
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImproveClient
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
    ConnectionManager.cpp

HEADERS  += \
    ConnectionManager.h
