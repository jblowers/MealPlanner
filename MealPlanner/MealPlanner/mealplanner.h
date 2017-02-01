#ifndef MEALPLANNER_H
#define MEALPLANNER_H

#include <QtWidgets/QMainWindow>
#include <qthread.h>
#include "ui_mealplanner.h"
#include "recipethreadcontroller.h"

class MealPlanner : public QMainWindow
{
	Q_OBJECT

public:
	MealPlanner(QWidget *parent = 0);
	~MealPlanner();

	RecipeThreadController* m_pController;


	public slots:
	void onCreateRecipe();

private:
	Ui::MealPlannerClass ui;
};

#endif // MEALPLANNER_H
