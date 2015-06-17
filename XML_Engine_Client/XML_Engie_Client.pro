#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T22:17:06
#
#-------------------------------------------------

QT       += xml

QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

TARGET = XML_Engie_Client
TEMPLATE = lib

DEFINES += XML_ENGIE_CLIENT_LIBRARY

SOURCES += xml_engie_client.cpp

HEADERS += xml_engie_client.h\
        xml_engie_client_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
