/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun May 11 20:08:58 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stack;
    QWidget *login_form;
    QPushButton *pushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *user_field;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *password_field;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QWidget *explore_form;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *all_table;
    QWidget *tab_2;
    QTableWidget *shelf_books_table;
    QPushButton *add_shelf_button;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *shelves_box;
    QWidget *tab_3;
    QWidget *tab_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(488, 434);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stack = new QStackedWidget(centralwidget);
        stack->setObjectName(QString::fromUtf8("stack"));
        stack->setGeometry(QRect(0, 0, 471, 361));
        stack->setContextMenuPolicy(Qt::ActionsContextMenu);
        login_form = new QWidget();
        login_form->setObjectName(QString::fromUtf8("login_form"));
        pushButton = new QPushButton(login_form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(130, 130, 99, 27));
        widget = new QWidget(login_form);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(80, 50, 223, 29));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        user_field = new QLineEdit(widget);
        user_field->setObjectName(QString::fromUtf8("user_field"));

        horizontalLayout->addWidget(user_field);

        widget1 = new QWidget(login_form);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(80, 90, 220, 29));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        password_field = new QLineEdit(widget1);
        password_field->setObjectName(QString::fromUtf8("password_field"));

        horizontalLayout_2->addWidget(password_field);

        widget2 = new QWidget(login_form);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(100, 170, 168, 29));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        pushButton_2 = new QPushButton(widget2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        stack->addWidget(login_form);
        explore_form = new QWidget();
        explore_form->setObjectName(QString::fromUtf8("explore_form"));
        tabWidget = new QTabWidget(explore_form);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 481, 381));
        tabWidget->setFocusPolicy(Qt::ClickFocus);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        all_table = new QTableWidget(tab);
        all_table->setObjectName(QString::fromUtf8("all_table"));
        all_table->setGeometry(QRect(10, 10, 451, 331));
        all_table->setContextMenuPolicy(Qt::CustomContextMenu);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        shelf_books_table = new QTableWidget(tab_2);
        shelf_books_table->setObjectName(QString::fromUtf8("shelf_books_table"));
        shelf_books_table->setGeometry(QRect(0, 40, 371, 301));
        shelf_books_table->setContextMenuPolicy(Qt::CustomContextMenu);
        add_shelf_button = new QPushButton(tab_2);
        add_shelf_button->setObjectName(QString::fromUtf8("add_shelf_button"));
        add_shelf_button->setGeometry(QRect(360, 0, 99, 27));
        widget3 = new QWidget(tab_2);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(0, 0, 321, 29));
        horizontalLayout_4 = new QHBoxLayout(widget3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        shelves_box = new QComboBox(widget3);
        shelves_box->setObjectName(QString::fromUtf8("shelves_box"));

        horizontalLayout_4->addWidget(shelves_box);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());
        stack->addWidget(explore_form);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 488, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(user_field, password_field);
        QWidget::setTabOrder(password_field, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        retranslateUi(MainWindow);

        stack->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Sign in", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Username", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Not a user?", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Sign up", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Explore", 0, QApplication::UnicodeUTF8));
        add_shelf_button->setText(QApplication::translate("MainWindow", "Add Shelf", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Select Shelf", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Shelves", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Friends", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Notifications", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
