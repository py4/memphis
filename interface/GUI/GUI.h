#ifndef GUI_H_
#define GUI_H_
#include <map>

#include <QWidget>
#include <string>
#include <QApplication>
#include "../../responder/responder.h"
#include "../../libs/db.h"
#include <QString>
class User;
class Login;

class GUI
{

public:
	int start(int, char* []);
	void sign_in();
	void sign_up();
	std::map<std::string,std::string> params;
	
private:
	User* current_user;
	void show_sign_in_form();
	void set_status(std::string);

};
#endif
