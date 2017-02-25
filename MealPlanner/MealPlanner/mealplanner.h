#ifndef MEALPLANNER_H
#define MEALPLANNER_H

#include <QtWidgets/QMainWindow>
#include <qthread.h>
#include "ui_mealplanner.h"
#include "recipethreadcontroller.h"
#include "RecipeDetailsWidget.h"

#include "qspinbox.h"
#include "qfiledialog.h"







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

	bool m_bCalendarVisible;


	// debug methods
	void addDefaultRecipes();


protected:

	void populateGuiWithRecipeData(Recipe rec);

	public slots:
	void onCreateRecipe();
	void onUpdateGui(Recipe*, int);
	void onUpdateGui(QList<Recipe> RecList);
	void onSaveNewRecipe(Recipe rec);
	void onNewRecClicked(QListWidgetItem*);
	void onToggleCalendar();
	void onLogRecipe(Recipe rec);
	void onEditRecipe();
	void onRemoveSelectedRecipe();
	void onAddRecipesFromFileClicked();
	void onBrowseForRecipeFileClicked();

signals:
	void PopulateCreateRecWindow(Recipe);
	void RemoveRecipeAtSignal(int);

	void AddRecipesFromFileSignal(QString);


private:
	Ui::MealPlannerClass ui;
};

#endif // MEALPLANNER_H
