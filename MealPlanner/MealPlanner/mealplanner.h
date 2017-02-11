#ifndef MEALPLANNER_H
#define MEALPLANNER_H

#include <QtWidgets/QMainWindow>
#include <qthread.h>
#include "ui_mealplanner.h"
#include "recipethreadcontroller.h"
#include "RecipeDetailsWidget.h"

class MealPlanner : public QMainWindow
{
	Q_OBJECT

public:
	MealPlanner(QWidget *parent = 0);
	~MealPlanner();

	RecipeThreadController* m_pController;

	RecipeDetailsWidget* m_pDetailsWidget;
	CreateRecipeWindow* m_pCreateRecipeWin;

	// methods


protected:

	void populateGuiWithRecipeData(Recipe rec);

	public slots:
	void onCreateRecipe();
	void onUpdateGui(Recipe*, int);
	void onUpdateGui(QList<Recipe> RecList);

	void onNewRecClicked(QListWidgetItem*);


private:
	Ui::MealPlannerClass ui;
};

#endif // MEALPLANNER_H
