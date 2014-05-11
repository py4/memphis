#include "GUI.h"
#include <iostream>
#include "login.h"
#include "../../libs/user.h"
#include <QStatusBar>
#include "tabs/tab_widget.h"
using namespace std;

GUI* GUI::ins = 0;

GUI::GUI()
{

}

int GUI::start(int argc, char* argv[])
{
    DB::db()->current_user = 0;
	QApplication app(argc, argv);
    window = new MainWindow;
    window->show();
    window->setWindowTitle("Memphis");

    //if(!DB::db()->current_user)-
      //  window->ui()->Form->show();
//	MainWindow* window = MainWindow::getInstance();
//	window->move(200,200);
//	window->setWindowTitle("Memphis");
//	window->setFixedSize(500,500);

//	if(!DB::db()->current_user)
//		window->render_login(this);
//	else
//		window->setCentralWidget(new TabWidget);
			
//	window->show();
	int a = app.exec();
	return a;
}

void GUI::sign_in()
{
	User* user = DB::db()->find_user(params["username"]);
	if(user == NULL)
	{
		set_status(RespondTo::Failure::user_not_found());
		return;
	}
	if(user->password != params["password"])
	{
		set_status(RespondTo::Failure::wrong_credentials());
		return;
	}

	DB::db()->current_user = user;
	set_status(RespondTo::Success::ok_login());
    window->render_explore_form();
    //MainWindow::getInstance()->setCentralWidget(new TabWidget);
}

void GUI::sign_up()
{

	User* user = DB::db()->find_user(params["username"]);
	if(user != NULL)
	{
		set_status(RespondTo::Failure::in_use());
		return;
	}

	user = new User(params["username"],params["password"]);
	DB::db()->add_user(user);
	DB::db()->current_user = user;

	set_status(RespondTo::Success::ok_signup());
    window->render_explore_form();
    //MainWindow::getInstance()->setCentralWidget(new TabWidget);
}

void GUI::set_status(string status)
{
    window->statusBar()->showMessage(QString::fromStdString((status)));
}

void GUI::set_status_for_book_selection(string name)
{
	
}

GUI* GUI::instance()
{
    return GUI::ins;
}

bool GUI::create_instance()
{
    if(!ins)
    {
        ins = new GUI;
        return true;
    }
    return false;
}
