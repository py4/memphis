#include "tab_widget.h"
#include "../mainwindow.h"
#include <QSize>
#include "all_tab.h"
#include "shelves_tab.h"
#include "notification_tab.h"
TabWidget::TabWidget(QWidget* parent) : QTabWidget(parent)
{
	setFixedSize(500,500);
	addTab(new AllTab(),"Explore");
	addTab(new ShelvesTab(),"Shelves");
	addTab(new NotificationTab(),"Notifications");
	addTab(new QWidget(),"Friends");
}
