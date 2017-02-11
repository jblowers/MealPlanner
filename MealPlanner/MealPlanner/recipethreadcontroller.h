#ifndef RECIPETHREADCONTROLLER_H
#define RECIPETHREADCONTROLLER_H

#include <QObject>
#include "QList.h"
#include "Recipe.h"
#include "CreateRecipeWindow.h"

class RecipeThreadController : public QObject
{
	Q_OBJECT

public:
	RecipeThreadController(QObject *parent);
	~RecipeThreadController();

	QWidget* m_Parent;


	QList<Recipe> m_RecipeList;


	// methods

	void UpdateGuiRecipes();

	Recipe GetRecAt(int nInd) {
		return m_RecipeList.at(nInd);
	}




public slots:

	void onStartController();
	void onCreateRecipe();


signals:
	void finished();
	void UpdateGuiSignal(Recipe*,int);
	void UpdateGuiSignal(QList<Recipe>);


private:
	
};

#endif // RECIPETHREADCONTROLLER_H
