#include "login.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QRegExp rx("[a-zA-Z0-9_]+");
    ui->lineEdit->setValidator(new QRegExpValidator(rx, this ));
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

Form::~Form()
{
    delete ui;
}
