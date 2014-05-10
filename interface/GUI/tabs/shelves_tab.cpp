#include "shelves_tab.h"
#include <iostream>
#include "../../../libs/db.h"
#include "../../../libs/user.h"
#include "../../../libs/library.h"
#include "../../../libs/shelf.h"
#include "../../../libs/book.h"
using namespace std;

ShelvesTab::ShelvesTab(QWidget* parent) : QWidget(parent)
{
	QHBoxLayout* hbox = new QHBoxLayout(this);

	left = new QFrame(this);
	left->setFrameShape(QFrame::StyledPanel);

	right = new QFrame(this);
	right->setFrameShape(QFrame::StyledPanel);

	QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(left);
	splitter->addWidget(right);

	lw = new QListWidget(this);
	//vector<Book*> books = DB::db()->user()->get_library()->get_stared_books();
	vector<Shelf*> shelves = DB::db()->user()->get_library()->get_shelves();
	for(int i = 0; i < shelves.size(); i++)
		lw->addItem(QString::fromStdString(shelves[i]->get_name()));
		//for(int i = 0; i < DB::db()->current_user
	QHBoxLayout* box = new QHBoxLayout(right);
	box->addWidget(lw);

	connect(lw, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(shelf_selected(QListWidgetItem*)));
	hbox->addWidget(splitter);
	setLayout(hbox);

	table = new QTableWidget(500,500,left);
}


void ShelvesTab::shelf_selected(QListWidgetItem* item)
{
	string shelf_name = item->text().toStdString();
	vector<Book*> books = DB::db()->user()->get_library()->get_shelf(shelf_name)->get_books();
	//QHBoxLayout* layout = new QHBoxLayout(this);

	cerr << "fuck0" << endl;
	table->clear();
	cerr << "fuck1" << endl;
	table->setRowCount(books.size());
	table->setColumnCount(4);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	table->setHorizontalHeaderItem(1, new QTableWidgetItem("Author"));
	table->setHorizontalHeaderItem(2, new QTableWidgetItem("Publisher"));
	table->setHorizontalHeaderItem(3, new QTableWidgetItem("Year"));

	cerr << "fuck that shit" << endl;
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

	//layout->addWidget(table);
	//setLayout(layout);
	//cerr << item->text().toStdString() << endl;
}
