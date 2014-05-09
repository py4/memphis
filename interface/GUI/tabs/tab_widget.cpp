#include "tab_widget.h"
#include "../main_window.h"
#include <QSize>
#include "all_tab.h"
TabWidget::TabWidget(QWidget* parent) : QTabWidget(parent)
{
	setFixedSize(500,500);
	addTab(new AllTab(),"Explore");
	addTab(new QWidget(),"Tab 2");
}
