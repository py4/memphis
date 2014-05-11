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
#include "log.h"

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
    rerender_people = true;

    if(DB::db()->user())
    {

    }
   // else
    //    ui->menubar->hide();
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

    //ui->menubar->show();
    cerr << "actions size:  " << ui->menubar->actions().size() << endl;
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
    book_name = ui->all_table->selectedItems()[0]->text().toStdString();
    selected_row = ui->all_table->selectedItems()[0];
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
    }
    else
        set_status(RespondTo::Failure::have_book());
    ui->all_table->selectedItems()[0]->setData(Qt::BackgroundRole, Qt::red);

    rerender_shelves = true;
}

void MainWindow::like()
{
    //string book_name = ui->all_table->selectedItems()[0]->text().toStdString();
    Book* book = DB::db()->find_book(book_name);
    DB::db()->user()->get_library()->star_book(book);
    DB::db()->user()->add_log(Logger::liked(book_name));
    set_status(RespondTo::Success::liked());
    //ui->all_table->selectedItems()[0]->setData(Qt::BackgroundRole, Qt::blue);
    selected_row->setData(Qt::BackgroundRole,Qt::blue);
}

void MainWindow::add_to_shelf()
{
    vector<Shelf*> shelves = DB::db()->user()->get_library()->get_shelves();
    //string book_name = ui->all_table->selectedItems()[0]->text().toStdString();
    QStringList items;
    for(int i = 0; i < shelves.size(); i++)
    {
        if(shelves[i]->get_name() == "default")
            continue;
        if(shelves[i]->has_book(book_name))
            continue;
        items << QString::fromStdString(shelves[i]->get_name());
    }

    QString name = QInputDialog::getItem(this,tr("Choose shelf"),tr("Shelf:"),items,0,FALSE);
    string shelf_name = name.toStdString();
    Shelf* shelf = DB::db()->user()->get_library()->get_shelf(shelf_name);
    shelf->add_book(book_name);
    DB::db()->user()->add_log(Logger::added_to_shelf(book_name,shelf_name));
    set_status(RespondTo::Success::book_added_to_shelf());
}

void MainWindow::set_status(string status)
{
    statusBar()->showMessage(QString::fromStdString(status));
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
    if(index == 2)
        if(rerender_people)
        {
            cout << "rerendering people" << endl;
            render_people_form();
            rerender_people = false;
        }
    if(index == 3)
        if(rerender_notifications)
        {
            cout << "rerendering notifications" << endl;
            render_notifications_form();
            rerender_notifications = false;
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


void MainWindow::on_shelves_box_currentIndexChanged(int index)
{
    string shelf_name = ui->shelves_box->itemText(index).toStdString();
    Shelf* shelf = DB::db()->user()->get_library()->get_shelf(shelf_name);
    if(shelf == NULL)
        return;

    vector<Book*> books = shelf->get_books();
    ui->shelf_books_table->clear();
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

void MainWindow::on_shelf_books_table_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->shelf_books_table->indexAt(pos);
    if(!index.isValid())
        return;
    book_name = ui->shelf_books_table->selectedItems()[0]->text().toStdString();
    selected_row = ui->shelf_books_table->selectedItems()[0];
    QMenu* menu = new QMenu(this);
    QAction* action = 0;
    if(DB::db()->user()->get_library()->is_in_library(book_name))
    {
        if(!DB::db()->user()->get_library()->is_in_starred(book_name))
        {
            action = new QAction("Like this", this);
            menu->addAction(action);
            connect(action,SIGNAL(triggered()),this,SLOT(like()));
        }

        vector<Shelf*> shelves = DB::db()->user()->get_library()->get_shelves();
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

    menu->popup(ui->shelf_books_table->viewport()->mapToGlobal(pos));
}

void MainWindow::render_people_form()
{
    ui->listWidget->clear();
    vector<User*> users = DB::db()->get_users();
    vector<User*> non_friends;
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i] == DB::db()->user())
            continue;
        if(DB::db()->user()->does_follow(users[i]))
            continue;
        non_friends.push_back(users[i]);
    }
    for(int i = 0; i < non_friends.size(); i++)
        ui->listWidget->addItem(QString::fromStdString(non_friends[i]->get_username()));
}

void MainWindow::follow()
{
    string username = ui->listWidget->currentItem()->text().toStdString();
    User* user = DB::db()->find_user(username);
    DB::db()->user()->follow(user);
    set_status(RespondTo::Success::followed());
    render_people_form();
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu* menu = new QMenu(this);
    QAction* action = new QAction("Follow",this);
    menu->addAction(action);
    connect(action,SIGNAL(triggered()),this,SLOT(follow()));
    menu->popup(ui->listWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::render_notifications_form()
{
    ui->listWidget_2->clear();
    vector<Log*> logs = DB::db()->user()->get_activity_logs();
    for(int i = 0; i < logs.size(); i++)
    {
        string message = logs[i]->username + " " + logs[i]->message;
        ui->listWidget_2->addItem(QString::fromStdString(message));
    }
}

void MainWindow::clear_notifications()
{
    ui->listWidget_2->clear();
    DB::db()->user()->activity_logs.clear();
    DB::db()->user()->logs_node->delete_children();
}

void MainWindow::on_pushButton_3_clicked()
{
    clear_notifications();
}

void MainWindow::logout()
{
    DB::db()->current_user = NULL;
    set_status(RespondTo::Success::ok_logout());
    //ui->tabWidget->setCurrentWidget(ui->all_table);
    //ui->tabWidget->setCurrentWidget(ui->tab);
    ui->menubar->clear();
    ui->stack->setCurrentWidget(ui->login_form);
    ui->user_field->clear();
    ui->password_field->clear();
    ui->all_table->clear();
    ui->shelf_books_table->clear();
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    rerender_explore = true;
    rerender_shelves = true;
    rerender_notifications = true;
    rerender_people = true;

}

void MainWindow::exit()
{
    cerr << "saving to file" << endl;
    DB::db()->save_to_disk();
    DB::free_db();
    qApp->exit();
}

void MainWindow::update()
{
    cerr << "updating" << endl;
    DB::db()->load_new_books();
    set_status(RespondTo::Success::updated());
    rerender_explore = true;
    render_explore_form();
}

void MainWindow::reset_tab()
{
    ui->tabWidget->setCurrentWidget(ui->tab);
}

/*void MainWindow::closeEvent(QCloseEvent* event)
{
        DB::db()->save_to_disk();
        DB::free_db();
}*/
