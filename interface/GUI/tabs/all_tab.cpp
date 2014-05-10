#include "all_tab.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <iostream>
#include <QListWidget>
#include "../../../libs/book.h"
#include "../../../libs/db.h"
#include <QHeaderView>
#include "../../../libs/user.h"
#include "../../../libs/library.h"
#include "../../../logger/logger.h"
#include "../main_window.h"
#include "../../../responder/responder.h"
using namespace std;
//TODO: clearing notifications
AllTab::AllTab(QWidget* parent) : QWidget(parent)
{
	QWidget* page = new QWidget(this);
	QHBoxLayout* layout = new QHBoxLayout(this);
	vector <Book*> books = DB::db()->get_books();
	
	table = new QTableWidget(500,500,this);
	table->setContextMenuPolicy(Qt::CustomContextMenu);
	table->setRowCount(books.size());
	table->setColumnCount(4);
  table->setSelectionBehavior(QAbstractItemView::SelectRows);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Author"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Publisher"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Year"));
	for(int i = 0; i < books.size(); i++)
	{
		table->setItem(i,0, new QTableWidgetItem(QString::fromStdString(books[i]->get_name())));
		table->setItem(i,1, new QTableWidgetItem(QString::fromStdString(books[i]->get_author())));
		table->setItem(i,2, new QTableWidgetItem(QString::fromStdString(books[i]->get_publisher())));
		table->setItem(i,3, new QTableWidgetItem(QString::fromStdString(books[i]->get_year())));
	}

	table->setVisible(false);
	table->resizeColumnsToContents();
	table->setVisible(true);

	layout->addWidget(table);
	
	page->setLayout(layout);

	connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(cellSelected(int,int)));
  connect(table, SIGNAL(customContextMenuRequested(QPoint)),SLOT(customMenuRequested(QPoint)));
}

void AllTab::cellSelected(int row, int column)
{
	cerr << table->item(row,0)->text().toStdString() << endl;
}

void AllTab::customMenuRequested(QPoint pos)
{
	QMenu* menu = new QMenu(this);
	QAction* action = new QAction("Add To Library",this);
	menu->addAction(action);
  menu->popup(table->viewport()->mapToGlobal(pos));

	connect(action,SIGNAL(triggered()),this,SLOT(add_to_library()));
}

void AllTab::add_to_library()
{
	QItemSelectionModel *select = table->selectionModel();
	QModelIndex index = select->selectedRows()[0];
	QString str = table->item(index.row(),index.column())->text(); //= table->data(index.row())->toString();
	string book_name = str.toStdString();
	cerr << "fuck2" << endl;
	Book* book = DB::db()->find_book(book_name);
	cerr << "fuck3" << endl;
	if(DB::db()->user()->get_library()->add_book(book_name))
	{
		DB::db()->user()->add_log(Logger::added_to_library(book_name));
		cerr << "6" << endl;
		MainWindow::set_status(RespondTo::Success::book_added());
	}
	else
		MainWindow::set_status(RespondTo::Failure::have_book());
}
