#ifndef CREATERECIPEWINDOW_H
#define CREATERECIPEWINDOW_H

#include <QWidget>
#include <qdialog.h>
#include "ui_createrecipewindow.h"
#include "Recipe.h"


class CreateRecipeWindow : public QDialog
{
	Q_OBJECT

public:
	CreateRecipeWindow(QWidget *parent = 0);
	~CreateRecipeWindow();

signals:

	void NewRecipeSignal(Recipe rec);

	public slots :

		void onSaveRecipeClicked();
		void onAddIngredientRowClicked();
		void onPopulateWithRecipe(Recipe);
		void onRemoveSelectedRowClicked();


public:
	Ui::CreateRecipeWindow ui;
};

#endif // CREATERECIPEWINDOW_H
