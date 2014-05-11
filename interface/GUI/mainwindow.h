#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QTableWidgetItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void set_status(std::string status);
    void render_explore_form();
    void render_shelves_form();
    void render_people_form();

    bool rerender_explore;
    bool rerender_shelves;
    bool rerender_notifications;
    bool rerender_people;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_all_table_customContextMenuRequested(const QPoint &pos);

    void add_to_library();
    void like();
    void add_to_shelf();
    void follow();

    void on_tabWidget_currentChanged(int index);

    void on_add_shelf_button_clicked();

    void on_shelves_box_currentIndexChanged(int index);

    void on_shelf_books_table_customContextMenuRequested(const QPoint &pos);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent*);
    std::string book_name;
    QTableWidgetItem* selected_row;
};

#endif // MAINWINDOW_H
