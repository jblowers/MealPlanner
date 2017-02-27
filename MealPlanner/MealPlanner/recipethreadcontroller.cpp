#include "recipethreadcontroller.h"

RecipeThreadController::RecipeThreadController(QObject *parent)
	: QObject(parent)
{

	m_SaveTimer.setInterval(5000);// every five seconds save the info to disk
	connect(&m_SaveTimer, SIGNAL(timeout()), this, SLOT(onSaveToFile()));
	//m_SaveTimer.start();
	m_bRecipesChanged = true;

	m_strSavePath = "S:\\Git Repos\\MealPlanner\\MealPlanner\\TestRecipes.xml";

}

RecipeThreadController::~RecipeThreadController()
{

}


void RecipeThreadController::onSaveToFile(QString strFilePath)
{
	if (strFilePath.isEmpty()) {
		strFilePath = m_strSavePath;
	}
	else {
		m_bRecipesChanged = true;
	}
	// want to save the recipes to file
	if (m_bRecipesChanged) {
		CStdXmlReg reg;
		reg.Set(m_RecipeList.length(), "MealPlanner.NumberOfRecipes");
		Recipe CurrRec;
		Ingredient* ing;
		string str;
		QList<Recipe> list(m_RecipeList);
		for (int i = 0; i < m_RecipeList.length(); i++) {
			CurrRec = list.takeFirst();
			str = CurrRec.getTitle().toStdString();
			reg.Set(str, "MealPlanner.Recipe[].title", i);
			reg.Set(CurrRec.getNumberOfIngredients(), "MealPlanner.Recipe[].numIngredients",i);
			for (int j = 0; j < CurrRec.getNumberOfIngredients(); j++) {
				ing = CurrRec.getIngredient(j);
				reg.Set(ing->getName().toStdString().c_str(), "MealPlanner.Recipe[].IngredientList.Ingredient[].name", i, j);
				reg.Set(ing->getQuantity(), "MealPlanner.Recipe[].IngredientList.Ingredient[].quantity", i, j);
				reg.Set((int)ing->m_bWhole30, "MealPlanner.Recipe[].IngredientList.Ingredient[].whole30flag", i, j);
				//reg.Set(ing->getUnitString().toStdString().c_str(), "Recipe[].IngredientList.Ingredient[].unitString", i, j);
				reg.Set(ing->getUnit(), "MealPlanner.Recipe[].IngredientList.Ingredient[].unit", i, j);
			}
			reg.Set(CurrRec.m_dTimeToCook, "MealPlanner.Recipe[].cooktime", i);
			str = CurrRec.m_strRecipeDescription.toStdString();
			reg.Set(str.c_str(), "MealPlanner.Recipe[].description", i);
			reg.Set(CurrRec.CheckWhole30(), "MealPlanner.Recipe[].whole30flag", i);

		}

		bool bRet = reg.SaveXml(strFilePath.toStdString().c_str());

		m_bRecipesChanged = false;

	}
	else {

	}
}


void RecipeThreadController::onStartController()
{

	// set up connections
	


}

void RecipeThreadController::onNewRecipesAdded(QList<Recipe> recList)
{
	m_RecipeList.append(recList);
	for (int i = 0; i < recList.length(); i++) {
		emit logRecipe(recList.at(i));
	}
	m_bRecipesChanged = true;
	onSaveToFile();
	UpdateGuiRecipes();
}

void RecipeThreadController::onNewRecipeAdded(Recipe rec)
{
	/// TODO: do some checks to see if it is the same as one already in the list
	if (rec.getTitle().isEmpty()){
		printf("Error: No title for recipe.\n");
		return;
	}
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

	CStdXmlReg reg;
	if (reg.LoadXml(strFilePath.toStdString().c_str())) {
		string strVal;
		Recipe rec;
		QList<Recipe> recList;
		Ingredient ing;
		int nNumRecs = 0;
		int nNumIngredients;
		reg.Get<int>(nNumRecs, "MealPlanner.NumberOfRecipes");
		for (int i = 0; i < nNumRecs; i++) {
			rec.RemoveAllIngredients();
			reg.Get(strVal, "MealPlanner.Recipe[].title", i);
			rec.m_strName = QString(strVal.c_str());
			reg.Get(strVal, "MealPlanner.Recipe[].numIngredients", i);
			nNumIngredients = QString(strVal.c_str()).toInt();
			for (int j = 0; j < nNumIngredients; j++) {
				reg.Get(strVal, "MealPlanner.Recipe[].IngredientList.Ingredient[].name",i,j);
				ing.m_strName = QString(strVal.c_str());
				reg.Get(strVal, "MealPlanner.Recipe[].IngredientList.Ingredient[].quantity", i, j);
				ing.m_dQuantity = QString(strVal.c_str()).toDouble();
				reg.Get(strVal, "MealPlanner.Recipe[].IngredientList.Ingredient[].unit", i, j);
				ing.m_Unit = (Ingredient::Units)QString(strVal.c_str()).toInt();
				reg.Get(strVal, "MealPlanner.Recipe[].IngredientList.Ingredient[].whole30flag", i, j);
				ing.m_bWhole30 = (bool)QString(strVal.c_str()).toInt();
				rec.addIngredient(ing);
			}
			reg.Get(strVal, "MealPlanner.Recipe[].whole30flag", i);
			rec.m_bWhole30 = (bool)QString(strVal.c_str()).toInt();
			reg.Get(strVal, "MealPlanner.Recipe[].cooktime",i);
			rec.m_dTimeToCook = QString(strVal.c_str()).toDouble();
			reg.Get(strVal, "MealPlanner.Recipe[].description", i);
			rec.m_strRecipeDescription = QString(strVal.c_str());

			recList.append(rec);
		}
		onNewRecipesAdded(recList);
	}

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


