#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "login.h"

class MainWindow : public QMainWindow
{
 private:
   static MainWindow* instance;
// protected:
   //MainWindow(QWidget* = NULL);
 public:
   static MainWindow* getInstance();
	 MainWindow(QWidget* = NULL);
	 void render_login(GUI*);
	 void closeEvent(QCloseEvent*);
};


#endif
