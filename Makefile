#############################################################################
# Makefile for building: assign8
# Generated by qmake (2.01a) (Qt 4.8.4) on: Sun May 11 00:54:35 2014
# Project:  assign8.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -o Makefile assign8.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++ -g
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -g -m64 -pipe -O2 -D_REENTRANT $(DEFINES)
CXXFLAGS      = -g -m64 -pipe -O2 -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Ilibs -Iparser -Iinterface/CLI -Iresponder -Iinterface/GUI -Ilogger -Iinterface/GUI/tabs -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		libs/book.cpp \
		libs/db.cpp \
		libs/library.cpp \
		libs/log.cpp \
		libs/shelf.cpp \
		libs/user.cpp \
		parser/node.cpp \
		parser/parser.cpp \
		parser/XML.cpp \
		interface/CLI/CLI.cpp \
		interface/GUI/GUI.cpp \
		interface/GUI/login.cpp \
		interface/GUI/main_window.cpp \
		interface/GUI/tabs/all_tab.cpp \
		interface/GUI/tabs/notification_tab.cpp \
		interface/GUI/tabs/shelves_tab.cpp \
		interface/GUI/tabs/tab_widget.cpp moc_login.cpp \
		moc_all_tab.cpp \
		moc_notification_tab.cpp \
		moc_shelves_tab.cpp
OBJECTS       = main.o \
		book.o \
		db.o \
		library.o \
		log.o \
		shelf.o \
		user.o \
		node.o \
		parser.o \
		XML.o \
		CLI.o \
		GUI.o \
		login.o \
		main_window.o \
		all_tab.o \
		notification_tab.o \
		shelves_tab.o \
		tab_widget.o \
		moc_login.o \
		moc_all_tab.o \
		moc_notification_tab.o \
		moc_shelves_tab.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		assign8.pro
QMAKE_TARGET  = assign8
DESTDIR       = 
TARGET        = assign8

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: assign8.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile assign8.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile assign8.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/assign81.0.0 || $(MKDIR) .tmp/assign81.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/assign81.0.0/ && $(COPY_FILE) --parents libs/book.h libs/db.h libs/library.h libs/log.h libs/shelf.h libs/user.h logger/logger.h parser/node.h parser/parser.h parser/XML.h responder/failure.h responder/responder.h responder/success.h interface/CLI/CLI.h interface/GUI/GUI.h interface/GUI/login.h interface/GUI/main_window.h interface/GUI/tabs/all_tab.h interface/GUI/tabs/notification_tab.h interface/GUI/tabs/shelves_tab.h interface/GUI/tabs/tab_widget.h .tmp/assign81.0.0/ && $(COPY_FILE) --parents main.cpp libs/book.cpp libs/db.cpp libs/library.cpp libs/log.cpp libs/shelf.cpp libs/user.cpp parser/node.cpp parser/parser.cpp parser/XML.cpp interface/CLI/CLI.cpp interface/GUI/GUI.cpp interface/GUI/login.cpp interface/GUI/main_window.cpp interface/GUI/tabs/all_tab.cpp interface/GUI/tabs/notification_tab.cpp interface/GUI/tabs/shelves_tab.cpp interface/GUI/tabs/tab_widget.cpp .tmp/assign81.0.0/ && (cd `dirname .tmp/assign81.0.0` && $(TAR) assign81.0.0.tar assign81.0.0 && $(COMPRESS) assign81.0.0.tar) && $(MOVE) `dirname .tmp/assign81.0.0`/assign81.0.0.tar.gz . && $(DEL_FILE) -r .tmp/assign81.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_login.cpp moc_all_tab.cpp moc_notification_tab.cpp moc_shelves_tab.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_login.cpp moc_all_tab.cpp moc_notification_tab.cpp moc_shelves_tab.cpp
moc_login.cpp: interface/GUI/login.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) interface/GUI/login.h -o moc_login.cpp

moc_all_tab.cpp: interface/GUI/tabs/all_tab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) interface/GUI/tabs/all_tab.h -o moc_all_tab.cpp

moc_notification_tab.cpp: interface/GUI/tabs/notification_tab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) interface/GUI/tabs/notification_tab.h -o moc_notification_tab.cpp

moc_shelves_tab.cpp: interface/GUI/tabs/shelves_tab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) interface/GUI/tabs/shelves_tab.h -o moc_shelves_tab.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		interface/CLI/CLI.h \
		responder/responder.h \
		responder/failure.h \
		responder/success.h \
		interface/GUI/GUI.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

book.o: libs/book.cpp libs/book.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o book.o libs/book.cpp

db.o: libs/db.cpp libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		libs/user.h \
		libs/log.h \
		libs/book.h \
		libs/library.h \
		libs/shelf.h \
		interface/CLI/CLI.h \
		responder/responder.h \
		responder/failure.h \
		responder/success.h \
		interface/GUI/GUI.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o db.o libs/db.cpp

library.o: libs/library.cpp libs/library.h \
		libs/shelf.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		libs/book.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o library.o libs/library.cpp

log.o: libs/log.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o log.o libs/log.cpp

shelf.o: libs/shelf.cpp libs/shelf.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		libs/book.h \
		libs/library.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o shelf.o libs/shelf.cpp

user.o: libs/user.cpp libs/user.h \
		libs/log.h \
		libs/library.h \
		parser/node.h \
		parser/parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o user.o libs/user.cpp

node.o: parser/node.cpp parser/node.h \
		parser/parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o node.o parser/node.cpp

parser.o: parser/parser.cpp parser/parser.h \
		responder/responder.h \
		responder/failure.h \
		responder/success.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o parser.o parser/parser.cpp

XML.o: parser/XML.cpp parser/XML.h \
		parser/parser.h \
		parser/node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o XML.o parser/XML.cpp

CLI.o: interface/CLI/CLI.cpp interface/CLI/CLI.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		responder/responder.h \
		responder/failure.h \
		responder/success.h \
		libs/user.h \
		libs/log.h \
		libs/library.h \
		libs/book.h \
		libs/shelf.h \
		logger/logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CLI.o interface/CLI/CLI.cpp

GUI.o: interface/GUI/GUI.cpp interface/GUI/GUI.h \
		responder/responder.h \
		responder/failure.h \
		responder/success.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		interface/GUI/login.h \
		interface/GUI/main_window.h \
		libs/user.h \
		libs/log.h \
		interface/GUI/tabs/tab_widget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GUI.o interface/GUI/GUI.cpp

login.o: interface/GUI/login.cpp interface/GUI/login.h \
		interface/GUI/GUI.h \
		responder/responder.h \
		responder/failure.h \
		responder/success.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o login.o interface/GUI/login.cpp

main_window.o: interface/GUI/main_window.cpp interface/GUI/main_window.h \
		interface/GUI/login.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main_window.o interface/GUI/main_window.cpp

all_tab.o: interface/GUI/tabs/all_tab.cpp interface/GUI/tabs/all_tab.h \
		libs/book.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o all_tab.o interface/GUI/tabs/all_tab.cpp

notification_tab.o: interface/GUI/tabs/notification_tab.cpp interface/GUI/tabs/notification_tab.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		libs/user.h \
		libs/log.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o notification_tab.o interface/GUI/tabs/notification_tab.cpp

shelves_tab.o: interface/GUI/tabs/shelves_tab.cpp interface/GUI/tabs/shelves_tab.h \
		libs/db.h \
		parser/XML.h \
		parser/parser.h \
		parser/node.h \
		libs/user.h \
		libs/log.h \
		libs/library.h \
		libs/shelf.h \
		libs/book.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o shelves_tab.o interface/GUI/tabs/shelves_tab.cpp

tab_widget.o: interface/GUI/tabs/tab_widget.cpp interface/GUI/tabs/tab_widget.h \
		interface/GUI/main_window.h \
		interface/GUI/login.h \
		interface/GUI/tabs/all_tab.h \
		interface/GUI/tabs/shelves_tab.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tab_widget.o interface/GUI/tabs/tab_widget.cpp

moc_login.o: moc_login.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_login.o moc_login.cpp

moc_all_tab.o: moc_all_tab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_all_tab.o moc_all_tab.cpp

moc_notification_tab.o: moc_notification_tab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_notification_tab.o moc_notification_tab.cpp

moc_shelves_tab.o: moc_shelves_tab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_shelves_tab.o moc_shelves_tab.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

