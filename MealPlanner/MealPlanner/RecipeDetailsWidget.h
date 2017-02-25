#pragma once

#include <QWidget>
#include "ui_RecipeDetailsWidget.h"
#include "qcombobox.h"
#include "Ingredient.h"
#include "qspinbox.h"


class UnitComboBox : public QComboBox
{
public:
	UnitComboBox(QTableWidget* parent = 0) {
		this->setParent(parent);
		for (int i = 0; i < Ingredient::nNumUnits; i++) {
			Ingredient ing;
			this->addItem(ing.UnitsList[i]);

		}
	}


};


class RecipeDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	RecipeDetailsWidget(QWidget *parent = Q_NULLPTR);
	~RecipeDetailsWidget();

	bool SetRecipeDetails(QString strDetails);

	bool m_bEditableMode;
	bool SetEditableMode(bool bEditable);


	void AddIngredientToList(int nRow, QString strName, double dQuant, Ingredient::Units);
	bool SetTableEditable(bool bEditable);


public:  // making this public to be able to access from main GUI
	Ui::RecipeDetailsWidget ui;
};
