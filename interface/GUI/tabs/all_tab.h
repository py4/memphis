#ifndef ALL_TAB_H
#define ALL_TAB_H
#include <QWidget>
#include <QTableWidget>
#include <QPoint>
#include <QMenu>
class AllTab : public QWidget
{
	Q_OBJECT
public:
	AllTab(QWidget* = 0);
private slots:
	void cellSelected(int,int);
	void customMenuRequested(QPoint);
	void add_to_library();
private:
	QTableWidget* table;
};
#endif
