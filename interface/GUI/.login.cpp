#include "login.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <QRegExp>
#include <QRegExpValidator>
#include "GUI.h"
#include <QFormLayout>
using namespace std;
Login::Login(GUI* gui, QWidget* parent) : QWidget(parent)
{
	if(gui == NULL or gui == 0)
		cerr << "danger! gui is null!" << endl;
	this->gui = gui;
	
	user_field = new QLineEdit(this);
	password_field = new QLineEdit(this);
	QRegExp rx("[a-zA-Z0-9_]+");
	user_field->setValidator(new QRegExpValidator(rx, this ));
	password_field->setEchoMode(QLineEdit::Password);

	QPushButton* sign_in = new QPushButton("Sign In!",this);
	sign_in->setGeometry(50,50,50,50);

	QLabel* label = new QLabel("Not a user?",this);
	label->setGeometry(100,110,100,50);
	QPushButton* sign_up = new QPushButton("Sign Up!",this);
	sign_up->setGeometry(200,110,100,50);

	QFormLayout *formLayout = new QFormLayout(this);;
	formLayout->addRow(tr("&Username:"), user_field);
	formLayout->addRow(tr("&Password:"), password_field);
	formLayout->addRow("",sign_in);
	setLayout(formLayout);
	
	connect(sign_in, SIGNAL(clicked()), this, SLOT(on_sign_in()));
	connect(sign_up, SIGNAL(clicked()), this, SLOT(on_sign_up()));
}

void Login::on_sign_in()
{
	gui->params["username"] = user_field->text().toUtf8().constData();
	gui->params["password"] = password_field->text().toUtf8().constData();
	gui->sign_in();
}

void Login::on_sign_up()
{
	gui->params["username"] = user_field->text().toUtf8().constData();
	gui->params["password"] = password_field->text().toUtf8().constData();
	gui->sign_up();
}

Login::~Login()
{
	delete user_field;
	delete password_field;
}

