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
	int m_nNumIngredients;

	int getNumberOfIngredients() { return m_nNumIngredients; }
	QString getTitle() { return m_strName; }
	bool CheckWhole30();
	QString getDescription() { return m_strRecipeDescription; }
	QString getTimeRequiredString() { return QString::number(m_dTimeToCook); }

	// methods
	int addIngredient(Ingredient ing);
	void RemoveAllIngredients() { m_IngredientList.clear(); m_nNumIngredients = 0; }
	Ingredient* getIngredient(int nIndex) { return &m_IngredientList[nIndex]; }
	QString m_strRecipeDescription;

};

