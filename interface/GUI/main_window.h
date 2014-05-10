#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "login.h"
#include <string>
class MainWindow : public QMainWindow
{
 private:
   static MainWindow* instance;
 	 MainWindow(QWidget* = NULL);
// protected:
   //MainWindow(QWidget* = NULL);
 public:
   static MainWindow* getInstance();

	 void render_login(GUI*);
	 void closeEvent(QCloseEvent*);
   static void set_status(std::string);
};


#endif
