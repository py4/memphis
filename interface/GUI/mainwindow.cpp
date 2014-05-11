#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"
#include "login.h"
#include "GUI.h"
#include "book.h"
#include "responder.h"
#include "logger.h"
#include "user.h"
#include "library.h"
#include <QInputDialog>
#include <QStringList>
#include "shelf.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp rx("[a-zA-Z0-9_]+");
    ui->user_field->setValidator(new QRegExpValidator(rx, this ));
    ui->password_field->setEchoMode(QLineEdit::Password);

    rerender_explore = false;
    rerender_shelves = true;
    rerender_notifications = true;
    rerender_friends = true;
    if(!DB::db()->user())
    {

        //Form* login = new Form(this);
        //setCentralWidget(login);
        //this->setVisible(false);
        //login->show();
        //this->setVisible(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    GUI::instance()->params["username"] = ui->user_field->text().toStdString();
    GUI::instance()->params["password"] = ui->password_field->text().toStdString();
    GUI::instance()->sign_in();
    //render_explore_form();
}

void MainWindow::on_pushButton_2_clicked()
{
    GUI::instance()->params["username"] = ui->user_field->text().toStdString();
    GUI::instance()->params["password"] = ui->password_field->text().toStdString();
    GUI::instance()->sign_up();
    //render_explore_form();
}

void MainWindow::render_explore_form()
{
    vector<Book*> books = DB::db()->get_books();
    ui->all_table->setRowCount(books.size());
    ui->all_table->setColumnCount(4);
    ui->all_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->all_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->all_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->all_table->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->all_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Author"));
    ui->all_table->setHorizontalHeaderItem(2, new QTableWidgetItem("Publisher"));
    ui->all_table->setHorizontalHeaderItem(3, new QTableWidgetItem("Year"));
    for(int i = 0; i < books.size(); i++)
    {
        ui->all_table->setItem(i,0, new QTableWidgetItem(QString::fromStdString(books[i]->get_name())));
        ui->all_table->setItem(i,1, new QTableWidgetItem(QString::fromStdString(books[i]->get_author())));
        ui->all_table->setItem(i,2, new QTableWidgetItem(QString::fromStdString(books[i]->get_publisher())));
        ui->all_table->setItem(i,3, new QTableWidgetItem(QString::fromStdString(books[i]->get_year())));

        Library* library = DB::db()->user()->get_library();
        if(library->is_in_library(books[i]->get_name()))
            if(library->is_in_starred(books[i]->get_name()))
                ui->all_table->item(i,0)->setData(Qt::BackgroundRole, Qt::blue);
            else
                ui->all_table->item(i,0)->setData(Qt::BackgroundRole, Qt::red);
    }
    ui->stack->setCurrentWidget(ui->explore_form);
}

void MainWindow::render_shelves_form()
{
    ui->shelves_box->clear();
    ui->shelf_books_table->clear();
    vector<Shelf*> shelves = DB::db()->user()->get_library()->get_shelves();
    for(int i = 0; i < shelves.size(); i++)
        ui->shelves_box->addItem(QString::fromStdString(shelves[i]->get_name()));
    string current_shelf = ui->shelves_box->currentText().toStdString();
    Shelf* shelf = DB::db()->user()->get_library()->get_shelf(current_shelf);
    vector<Book*> books = shelf->get_books();
    ui->shelf_books_table->setRowCount(books.size());
    ui->shelf_books_table->setColumnCount(4);
    ui->shelf_books_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->shelf_books_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->shelf_books_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->shelf_books_table->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->shelf_books_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Author"));
    ui->shelf_books_table->setHorizontalHeaderItem(2, new QTableWidgetItem("Publisher"));
    ui->shelf_books_table->setHorizontalHeaderItem(3, new QTableWidgetItem("Year"));
    for(int i = 0; i < books.size(); i++)
    {
        ui->shelf_books_table->setItem(i,0, new QTableWidgetItem(QString::fromStdString(books[i]->get_name())));
        ui->shelf_books_table->setItem(i,1, new QTableWidgetItem(QString::fromStdString(books[i]->get_author())));
        ui->shelf_books_table->setItem(i,2, new QTableWidgetItem(QString::fromStdString(books[i]->get_publisher())));
        ui->shelf_books_table->setItem(i,3, new QTableWidgetItem(QString::fromStdString(books[i]->get_year())));

        Library* library = DB::db()->user()->get_library();
        if(library->is_in_starred(books[i]->get_name()))
            ui->shelf_books_table->item(i,0)->setData(Qt::BackgroundRole,Qt::blue);
    }
}

void MainWindow::on_all_table_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->all_table->indexAt(pos);
    if(!index.isValid())
        return;
    string book_name = ui->all_table->selectedItems()[0]->text().toStdString();
    QMenu* menu = new QMenu(this);
    QAction* action = 0;
    if(DB::db()->user()->get_library()->is_in_library(book_name))
    {
        cerr << "1" << endl;
        if(!DB::db()->user()->get_library()->is_in_starred(book_name))
        {
            action = new QAction("Like this", this);
            menu->addAction(action);
            connect(action,SIGNAL(triggered()),this,SLOT(like()));
        }

        vector<Shelf*> shelves = DB::db()->user()->get_library()->get_shelves();
        string book_name = ui->all_table->selectedItems()[0]->text().toStdString();
        int count = 0;
        for(int i = 0; i < shelves.size(); i++)
        {
            if(shelves[i]->get_name() == "default")
                continue;
            if(shelves[i]->has_book(book_name))
                continue;
            count++;
        }
        if(count > 0)
        {
            action = new QAction("Add to Shelf", this);
            menu->addAction(action);
            connect(action,SIGNAL(triggered()),this,SLOT(add_to_shelf()));
        }
    }
    else
    {

        action = new QAction("Add To Library",this);
        menu->addAction(action);
        connect(action,SIGNAL(triggered()),this,SLOT(add_to_library()));
    }
    menu->popup(ui->all_table->viewport()->mapToGlobal(pos));
}

void MainWindow::add_to_library()
{
    string book_name = ui->all_table->selectedItems()[0]->text().toStdString();
    Book* book = DB::db()->find_book(book_name);
    if(DB::db()->user()->get_library()->add_book(book_name))
    {
        DB::db()->user()->add_log(Logger::added_to_library(book_name));
        set_status(RespondTo::Success::book_added());
        DB::db()->user()->add_log(Logger::added_to_library(book_name));
    }
    else
        set_status(RespondTo::Failure::have_book());
    ui->all_table->selectedItems()[0]->setData(Qt::BackgroundRole, Qt::red);
}

void MainWindow::like()
{
    string book_name = ui->all_table->selectedItems()[0]->text().toStdString();
    Book* book = DB::db()->find_book(book_name);
    DB::db()->user()->get_library()->star_book(book);
    DB::db()->user()->add_log(Logger::liked(book_name));
    set_status(RespondTo::Success::liked());
    ui->all_table->selectedItems()[0]->setData(Qt::BackgroundRole, Qt::blue);
}

void MainWindow::add_to_shelf()
{
    vector<Shelf*> shelves = DB::db()->user()->get_library()->get_shelves();
    string book_name = ui->all_table->selectedItems()[0]->text().toStdString();
    QStringList items;
    for(int i = 0; i < shelves.size(); i++)
    {
        if(shelves[i]->get_name() == "default")
            continue;
        if(shelves[i]->has_book(book_name))
            continue;
        items << QString::fromStdString(shelves[i]->get_name());
    }

    QString shelf_name = QInputDialog::getItem(this,tr("Choose shelf"),tr("Shelf:"),items,0,FALSE);
    cout << shelf_name.toStdString() << endl;
}

void MainWindow::set_status(string status)
{
    statusBar()->showMessage(QString::fromStdString(status));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
        DB::db()->save_to_disk();
        DB::free_db();
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0)
        if(rerender_explore)
        {
            cout << "rerendering explore form" << endl;
            render_explore_form();
            rerender_explore = false;
        }

    if(index == 1)
        if(rerender_shelves)
        {
            cout << "rerendering shelves form" << endl;
            render_shelves_form();
            rerender_shelves = false;
        }
}

void MainWindow::on_add_shelf_button_clicked()
{
    string shelf_name = QInputDialog::getText(this,tr("Enter your shelf's name"),tr("Name: "),QLineEdit::Normal).toStdString();
    Shelf* shelf = DB::db()->user()->get_library()->get_shelf(shelf_name);
    if(shelf != NULL)
    {
        set_status(RespondTo::Failure::shelf_already_exists());
        return;
    }
    DB::db()->user()->get_library()->add_shelf(shelf_name);
    set_status(RespondTo::Success::shelf_added());
    render_shelves_form();
}
