#include "mealplanner.h"

MealPlanner::MealPlanner(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	
	m_pController = new RecipeThreadController(NULL);
	QThread *ControllerThread = new QThread;

	m_pController->moveToThread(ControllerThread);

	// setting up controller thread connections
	connect(ControllerThread, SIGNAL(started()), m_pController, SLOT(onStartController()));
	connect(m_pController, SIGNAL(finished()), ControllerThread, SLOT(quit()));
	connect(m_pController, SIGNAL(finished()), m_pController, SLOT(deleteLater()));
	connect(ControllerThread, SIGNAL(finished()), ControllerThread, SLOT(deleteLater()));
	ControllerThread->start();



	// gui connections
	connect(ui.CreateRecipeButton, SIGNAL(clicked()), this, SLOT(onCreateRecipe()));
	



}

MealPlanner::~MealPlanner()
{

}

void MealPlanner::onCreateRecipe()
{

	CreateRecipeWindow* win = new CreateRecipeWindow(this);
	//QWindow* wind = new QWindow();
	
	win->show();

}











