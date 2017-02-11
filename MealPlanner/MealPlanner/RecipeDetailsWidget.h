#pragma once

#include <QWidget>
#include "ui_RecipeDetailsWidget.h"

class RecipeDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	RecipeDetailsWidget(QWidget *parent = Q_NULLPTR);
	~RecipeDetailsWidget();



	bool m_bEditableMode;
	bool SetEditableMode(bool bEditable) {
		m_bEditableMode = bEditable;
		ui.RecipeTitleLineEdit->setReadOnly(!bEditable);
		return true;
	}


public:  // making this public to be able to access from main GUI
	Ui::RecipeDetailsWidget ui;
};
