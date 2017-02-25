#include "recipethreadcontroller.h"

RecipeThreadController::RecipeThreadController(QObject *parent)
	: QObject(parent)
{

	m_SaveTimer.setInterval(5000);// every five seconds save the info to disk
	connect(&m_SaveTimer, SIGNAL(timeout()), this, SLOT(onSaveToFile()));
	//m_SaveTimer.start();
	m_bRecipesChanged = true;

}

RecipeThreadController::~RecipeThreadController()
{

}


void RecipeThreadController::onSaveToFile()
{
	// want to save the recipes to file
	if (m_bRecipesChanged) {
		CStdXmlReg reg;
		Recipe CurrRec;
		Ingredient* ing;
		string str;
		QList<Recipe> list(m_RecipeList);
		for (int i = 0; i < m_RecipeList.length(); i++) {
			CurrRec = list.takeFirst();
			str = CurrRec.getTitle().toStdString();
			reg.Set(str, "Recipe[].title", i);
			int j = 1;
			for (int j = 0; j < CurrRec.getNumberOfIngredients(); j++) {
				ing = CurrRec.getIngredient(j);
				reg.Set(ing->getName().toStdString().c_str(), "Recipe[].IngredientList.Ingredient[].name", i, j);
				reg.Set(ing->getQuantity(), "Recipe[].IngredientList.Ingredient[].quantity", i, j);
				reg.Set(ing->getUnitString().toStdString().c_str(), "Recipe[].IngredientList.Ingredient[].unit", i, j);
			}
			reg.Set(CurrRec.m_dTimeToCook, "Recipe[].cooktime", i);
			str = CurrRec.m_strRecipeDescription.toStdString();
			reg.Set(str.c_str(), "Recipe[].description", i);
			reg.Set(CurrRec.CheckWhole30(), "Recipe[].whole30flag", i);

		}

		bool bRet = reg.SaveXml("S:\\Git Repos\\MealPlanner\\MealPlanner\\TestRecipes.xml");

		m_bRecipesChanged = false;

	}
	else {

	}
}


void RecipeThreadController::onStartController()
{

	// set up connections
	


}

void RecipeThreadController::onNewRecipeAdded(Recipe rec)
{
	/// TODO: do some checks to see if it is the same as one already in the list

	emit logRecipe(rec);
	// create a copy and add to the list.
	Recipe newRecipe(rec);
	m_RecipeList.append(newRecipe);
	m_bRecipesChanged = true;
	onSaveToFile();
	UpdateGuiRecipes();

}

void RecipeThreadController::onRemoveRecipeAt(int nInd)
{
	m_RecipeList.removeAt(nInd);
	m_bRecipesChanged = true;
	onSaveToFile(); // do we want to do this right away? Or wait in case it was an accident?
	UpdateGuiRecipes();
}


void RecipeThreadController::onCreateRecipe()
{
	

}

void RecipeThreadController::onAddRecipesFromFile(QString strFilePath)
{
	// open file, loop through Recipes and add each to the current list, then update the gui


}


void RecipeThreadController::UpdateGuiRecipes()
{
	// emit signals to GUI to update the list
	// perhaps use a pointer to an array of Recipe objects?
	//int nNumRecs = m_RecipeList.length();
	//Recipe* recPointer = new Recipe[nNumRecs];

	//for (int i = 0; i < nNumRecs; i++) {
	//	recPointer[i] = Recipe(m_RecipeList.at(i));
	//}

	QList<Recipe> RecListToPass = m_RecipeList;
	emit UpdateGuiSignal(RecListToPass);
	//emit UpdateGuiSignal(recPointer, nNumRecs);

}


