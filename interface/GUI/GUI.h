#ifndef GUI_H_
#define GUI_H_
#include <map>

#include <QWidget>
#include <string>
#include <QApplication>
#include "../../responder/responder.h"
#include "../../libs/db.h"
#include <QString>
#include "mainwindow.h"

class User;
class Login;

class GUI : public QObject
{
    Q_OBJECT
public:
    static GUI* instance();
	int start(int, char* []);
	void sign_in();
	void sign_up();
	std::map<std::string,std::string> params;
    static bool create_instance();
    ~GUI();
private:
    MainWindow* window;
    GUI();
  GUI(GUI const&);
  void operator=(GUI const&);

  static GUI* ins;

	void show_sign_in_form();
	void set_status(std::string);
	void set_status_for_book_selection(std::string);

    void prepare_menu();
};
#endif
