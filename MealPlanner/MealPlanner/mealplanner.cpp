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

	m_pDetailsWidget = new RecipeDetailsWidget();
	ui.RecipeDetailsVerticalLayout->addWidget(m_pDetailsWidget);


	connect(m_pController, SIGNAL(UpdateGuiSignal(Recipe*, int)), this, SLOT(onUpdateGui(Recipe*, int)));
	connect(m_pController, SIGNAL(UpdateGuiSignal(QList<Recipe>)), this, SLOT(onUpdateGui(QList<Recipe>)));

	//m_pDetailsWidget->ui.RecipeTitleLabel->setText("Test Recipe");

	// gui connections
	connect(ui.CreateRecipeButton, SIGNAL(clicked()), this, SLOT(onCreateRecipe()));
	
	connect(this, SIGNAL(closeEvent()), m_pDetailsWidget, SLOT(deleteLater()));
	connect(this, SIGNAL(closeEvent()), m_pCreateRecipeWin, SLOT(deleteLater()));


	connect(ui.UpdateGuiButton, SIGNAL(clicked()), m_pController, SLOT(onCreateRecipe()));

	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onNewRecClicked(QListWidgetItem*)));

	m_pController->UpdateGuiRecipes();
	//onCreateRecipe();

	qRegisterMetaType<QList<Recipe>>("QList<Recipe>");

}

MealPlanner::~MealPlanner()
{
	//m_pDetailsWidget->deleteLater();
	m_pDetailsWidget->close();
	m_pCreateRecipeWin->close();

}

void MealPlanner::onNewRecClicked(QListWidgetItem* it)
{
	QString strName = it->text();
	int nInd = ui.listWidget->currentRow();

	Recipe currRec = m_pController->GetRecAt(nInd);

	populateGuiWithRecipeData(currRec);

}


void MealPlanner::populateGuiWithRecipeData(Recipe rec)
{

	m_pDetailsWidget->ui.RecipeTitleLineEdit->setText(rec.m_strName);
	m_pDetailsWidget->ui.TimeRequiredLineEdit->setText(QString::number(rec.m_dTimeToCook));

	m_pDetailsWidget->ui.IngredientListWidget->clear();
	//m_pDetailsWidget->ui.IngredientsPlainTextEdit->clear();
	m_pDetailsWidget->ui.RecipeDetailsPlainTextEdit->clear();
	Ingredient currIng;
	QListWidgetItem* item;
	for (int i = 0; i < rec.m_IngredientList.length(); i++) {
		currIng = rec.m_IngredientList.at(i);
		item = new QListWidgetItem(currIng.getName());
		m_pDetailsWidget->ui.IngredientListWidget->addItem(item);
	}
	m_pDetailsWidget->ui.Whole30CheckBox->setChecked(rec.m_bWhole30);

}

void MealPlanner::onCreateRecipe()
{

	m_pCreateRecipeWin = new CreateRecipeWindow(this);
	m_pCreateRecipeWin->ui.RecDetailsWidget->SetEditableMode(true);
	m_pCreateRecipeWin->show();

	

}


void MealPlanner::onUpdateGui(QList<Recipe> RecList)
{
	ui.listWidget->clear();

	QListWidgetItem* item;
	for (int i = 0; i < RecList.length(); i++) {
		
		item = ui.listWidget->item(i);
		if (!item)
			item = new QListWidgetItem(RecList[i].m_strName);
		item->setText(RecList[i].m_strName);

		ui.listWidget->addItem(item);
	}

}

void MealPlanner::onUpdateGui(Recipe* pRec, int nNumRec)
{

	ui.listWidget->clear();

	Recipe currRec;
	QListWidgetItem* item;
	for (int i = 0; i < nNumRec; i++) {
		currRec = pRec[i];
		item = ui.listWidget->item(i);
		if ( !item ) 
			item = new QListWidgetItem(currRec.m_strName);
		item->setText(currRec.m_strName);

		ui.listWidget->addItem(item);


	}


}







