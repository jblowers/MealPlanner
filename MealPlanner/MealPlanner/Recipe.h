#pragma once

#include "qlist.h"
#include "Ingredient.h"

class Recipe
{
public:
	Recipe();
	~Recipe();


private:


public:
	QString m_strName;
	QList<Ingredient> m_IngredientList;
	bool m_bWhole30;
	double m_dTimeToCook; // minutes

	int getNumberOfIngredients() { return m_IngredientList.length(); }
	QString getTitle() { return m_strName; }
	bool CheckWhole30();
	QString getDescription() { return m_strRecipeDescription; }
	QString getTimeRequiredString() { return QString::number(m_dTimeToCook); }

	// methods
	int addIngredient(Ingredient ing);
	Ingredient* getIngredient(int nIndex) { return &m_IngredientList[nIndex]; }
	QString m_strRecipeDescription;

};

