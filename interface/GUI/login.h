#ifndef LOGIN_H_
#define LOGIN_H_

#include <QWidget>
#include <string>
#include <QLineEdit>
class GUI;

class Login : public QWidget
{
	Q_OBJECT
	
public:
	Login(GUI*, QWidget* = 0);
	~Login();
	private slots:
		void on_sign_in();
		void on_sign_up();
	
private:
	std::string username;
	std::string password;
	QLineEdit* user_field;
	QLineEdit* password_field;

	GUI* gui;
};
#endif
