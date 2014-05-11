#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    bool rerender_explore;
    bool rerender_shelves;
    bool rerender_notifications;
    bool rerender_friends;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_all_table_customContextMenuRequested(const QPoint &pos);

    void add_to_library();
    void like();
    void add_to_shelf();

    void on_tabWidget_currentChanged(int index);

    void on_add_shelf_button_clicked();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent*);
};

#endif // MAINWINDOW_H
