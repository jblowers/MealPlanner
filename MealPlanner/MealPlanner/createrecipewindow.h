#ifndef CREATERECIPEWINDOW_H
#define CREATERECIPEWINDOW_H

#include <QWidget>
#include <qdialog.h>
#include "ui_createrecipewindow.h"

class CreateRecipeWindow : public QDialog
{
	Q_OBJECT

public:
	CreateRecipeWindow(QWidget *parent = 0);
	~CreateRecipeWindow();

//private:
	Ui::CreateRecipeWindow ui;
};

#endif // CREATERECIPEWINDOW_H
