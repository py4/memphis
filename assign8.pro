######################################################################
# Automatically generated by qmake (2.01a) Thu May 8 00:33:47 2014
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . interface libs logger parser responder
INCLUDEPATH += . libs parser interface responder logger

# Input
HEADERS += interface/API.h \
           libs/book.h \
           libs/db.h \
           libs/library.h \
           libs/log.h \
           libs/shelf.h \
           libs/user.h \
           logger/logger.h \
           parser/node.h \
           parser/parser.h \
           parser/XML.h \
           responder/failure.h \
           responder/responder.h \
           responder/success.h
SOURCES += main.cpp \
           interface/API.cpp \
           libs/book.cpp \
           libs/db.cpp \
           libs/library.cpp \
           libs/log.cpp \
           libs/shelf.cpp \
           libs/user.cpp \
           parser/node.cpp \
           parser/parser.cpp \
           parser/XML.cpp
