#include "Recipe.h"


Recipe::Recipe()
{
	//m_IngredientList.append
	m_strName = "No Name";
	m_bWhole30 = false;


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

	return 1;

}