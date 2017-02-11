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
	bool CheckWhole30();

	// methods
	int addIngredient(Ingredient ing);


};

