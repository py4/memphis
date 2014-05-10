#pragma once

#ifndef SHELVES_TAB_H
#define SHELVES_TAB_H
#include <QWidget>
#include <QFrame>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
class ShelvesTab : public QWidget
{
	Q_OBJECT
public:
	ShelvesTab(QWidget* = 0);
private slots:
	void shelf_selected(QListWidgetItem*);
	private:
	QListWidget* lw;
	QTableWidget* table;
	QFrame* left, *right;
};
#endif
