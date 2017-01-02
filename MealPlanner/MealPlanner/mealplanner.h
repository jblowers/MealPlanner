#ifndef MEALPLANNER_H
#define MEALPLANNER_H

#include <QtWidgets/QMainWindow>
#include "ui_mealplanner.h"

class MealPlanner : public QMainWindow
{
	Q_OBJECT

public:
	MealPlanner(QWidget *parent = 0);
	~MealPlanner();

private:
	Ui::MealPlannerClass ui;
};

#endif // MEALPLANNER_H
