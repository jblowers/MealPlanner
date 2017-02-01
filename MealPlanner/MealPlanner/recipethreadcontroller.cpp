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
	Recipe rec;
	rec.m_dTimeToCook = 60;
	rec.m_strName = "Fried Eggs";
	Ingredient ing;
	ing.m_bWhole30 = true;
	ing.m_Unit = Ingredient::Units::Quant;
	ing.m_strName = "Egg";
	ing.m_dQuantity = 4;

	//CreateRecipeWindow* win = new CreateRecipeWindow(this);
	//win->show();





}
