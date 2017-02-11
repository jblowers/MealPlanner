#include "recipethreadcontroller.h"

RecipeThreadController::RecipeThreadController(QObject *parent)
	: QObject(parent)
{

	


}

RecipeThreadController::~RecipeThreadController()
{

}


void RecipeThreadController::onStartController()
{

	// set up connections



}



void RecipeThreadController::onCreateRecipe()
{
	m_RecipeList.clear();

	Recipe rec;
	rec.m_dTimeToCook = 60;
	rec.m_strName = "Fried Eggs";
	Ingredient ing;
	ing.m_bWhole30 = true;
	ing.m_Unit = Ingredient::Units::Quant;
	ing.m_strName = "Egg";
	ing.m_dQuantity = 4;

	rec.addIngredient(ing);

	ing.m_Unit = Ingredient::Units::Tablespoon;
	ing.m_strName = "Oil";
	ing.m_dQuantity = 1;

	rec.addIngredient(ing);

	m_RecipeList.append(rec);

	rec.m_IngredientList.clear();
	rec.m_dTimeToCook = 20;
	rec.m_strName = "Baked Potato";
	ing.m_bWhole30 = true;
	ing.m_Unit = Ingredient::Units::Quant;
	ing.m_strName = "Potato";
	ing.m_dQuantity = 2;
	rec.addIngredient(ing);

	m_RecipeList.append(rec);

	UpdateGuiRecipes();

	//CreateRecipeWindow* win = new CreateRecipeWindow(this);
	//win->show();





}


void RecipeThreadController::UpdateGuiRecipes()
{
	// emit signals to GUI to update the list
	// perhaps use a pointer to an array of Recipe objects?
	int nNumRecs = m_RecipeList.length();
	Recipe* recPointer = new Recipe[nNumRecs];

	for (int i = 0; i < nNumRecs; i++) {
		recPointer[i] = m_RecipeList.at(i);
	}


		emit UpdateGuiSignal(m_RecipeList);
	//emit UpdateGuiSignal(recPointer, nNumRecs);

}


