#include "all_tab.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <iostream>
#include <QListWidget>
#include "../../../libs/book.h"
#include "../../../libs/db.h"
using namespace std;
AllTab::AllTab(QWidget* parent) : QWidget(parent)
{
	QWidget* page = new QWidget(this);
	QPushButton* pb = new QPushButton("test");
	QHBoxLayout* layout = new QHBoxLayout(this);
	pb->setGeometry(100,100,100,100);
	layout->addWidget(pb);
	//QListWidget* list = new QListWidget(this);
	vector <Book*> books = DB::db()->get_books();
	
	QTableWidget* table = new QTableWidget(this);
	table->setRowCount(books.size());
	table->setColumnCount(4);
  table->setSelectionBehavior(QAbstractItemView::SelectRows);

	for(int i = 0; i < books.size(); i++)
	{
		table->setItem(i,0, new QTableWidgetItem(QString::fromStdString(books[i]->get_name())));
		table->setItem(i,1, new QTableWidgetItem(QString::fromStdString(books[i]->get_author())));
		table->setItem(i,2, new QTableWidgetItem(QString::fromStdString(books[i]->get_publisher())));
		table->setItem(i,3, new QTableWidgetItem(QString::fromStdString(books[i]->get_year())));
	}

	layout->addWidget(table);
	
	page->setLayout(layout);
	cerr << "fuck that!" << endl;
}
