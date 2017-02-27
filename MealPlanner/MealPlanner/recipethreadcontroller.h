#ifndef RECIPETHREADCONTROLLER_H
#define RECIPETHREADCONTROLLER_H

#include <QObject>
#include "QList.h"
#include "qtimer.h"
#include "Recipe.h"
#include "CreateRecipeWindow.h"
#include "StdXmlReg.h"

class RecipeThreadController : public QObject
{
	Q_OBJECT

public:
	RecipeThreadController(QObject *parent);
	~RecipeThreadController();

	QWidget* m_Parent;


	QList<Recipe> m_RecipeList; // This is where all the recipes actually exist
	QString m_strSavePath;

	// methods

	void UpdateGuiRecipes();

	Recipe GetRecAt(int nInd) {
		return Recipe(m_RecipeList.at(nInd));
	}

	bool m_bRecipesChanged;

	QTimer m_SaveTimer;

public slots:

void onSaveToFile(QString strFilePath = "");

	void onStartController();
	void onCreateRecipe();

	void onNewRecipeAdded(Recipe rec);
	void onNewRecipesAdded(QList<Recipe> recList);
	void onRemoveRecipeAt(int nInd);
	void onAddRecipesFromFile(QString strFilePath);


signals:
	void finished();
	void UpdateGuiSignal(Recipe*,int);
	void UpdateGuiSignal(QList<Recipe>);

	void logRecipe(Recipe rec);

private:
	
};

#endif // RECIPETHREADCONTROLLER_H
