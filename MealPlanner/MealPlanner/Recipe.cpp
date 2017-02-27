#include "Recipe.h"


Recipe::Recipe()
{
	//m_IngredientList.append
	m_strName = "";
	m_bWhole30 = false;
	m_dTimeToCook = 0;
	m_IngredientList.clear();
	m_nNumIngredients = 0;
}


Recipe::~Recipe()
{
}


bool Recipe::CheckWhole30()
{
	bool bCompliant = true;
	for (int i = 0; i < m_IngredientList.length(); i++) {
		bCompliant &= m_IngredientList[i].m_bWhole30;
	}
	return bCompliant;
}



int Recipe::addIngredient(Ingredient ing)
{
	m_IngredientList.append(ing);
	m_nNumIngredients = m_IngredientList.length();
	return 1;

}