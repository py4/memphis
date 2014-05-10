#include "notification_tab.h"
#include "../../../libs/db.h"
#include "../../../libs/user.h"
#include "../../../libs/log.h"
#include <iostream>
using namespace std;
//updating notifications
NotificationTab::NotificationTab(QWidget* parent) : QWidget(parent)
{
	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->setMargin(0);
	vector <Log*> logs = DB::db()->user()->get_activity_logs();
	int height = 0;
	for(int i = 0; i < logs.size(); i++)
	{
		string log = logs[i]->username + " " + logs[i]->message;
		QLabel* label = new QLabel(QString::fromStdString(log),this);
		label->setGeometry(0,height,100,100);
		height += 50;
		//box->addWidget(label);
	}
	//setLayout(vbox);
}

