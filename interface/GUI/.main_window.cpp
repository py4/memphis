#include "main_window.h"
#include <iostream>
#include <QPushButton>
#include <QStatusBar>
#include "../../libs/db.h"
using namespace std;

MainWindow* MainWindow::instance = 0;

MainWindow* MainWindow::getInstance()
{
	if(!instance) 
	{
		instance = new MainWindow();
	}
	return instance;
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
}

void MainWindow::render_login(GUI* gui)
{
	statusBar()->showMessage("You are not logged in!");
	Login* window = new Login(gui,instance);
	QWidget* layout = window;
	setCentralWidget(window);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	DB::db()->save_to_disk();
	DB::free_db();
}

void MainWindow::set_status(string status)
{
	instance->statusBar()->showMessage(QString::fromStdString(status));
}
