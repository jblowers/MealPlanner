#include "mealplanner.h"

MealPlanner::MealPlanner(QWidget *parent)
	: QMainWindow(parent)
{
	
	qRegisterMetaType<QList<Recipe>>("QList<Recipe>");
	qRegisterMetaType<Recipe>("Recipe");
	
	ui.setupUi(this);

	// set up controller thread
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


	// gui connections
	connect(ui.CreateRecipeButton, SIGNAL(clicked()), this, SLOT(onCreateRecipe())); // pops up the create recipe window
	connect(ui.EditSelectedRecipeButton, SIGNAL(clicked()), this, SLOT(onEditRecipe())); // pops up the create recipe window and populates it with the selected index in the table
	connect(ui.RemoveSelectedRecipeButton, SIGNAL(clicked()), this, SLOT(onRemoveSelectedRecipe()));
	connect(ui.AddRecipesFromFileButton, SIGNAL(clicked()), this, SLOT(onAddRecipesFromFileClicked()));
	connect(ui.BrowseForRecipeFileButton, SIGNAL(clicked()), this, SLOT(onBrowseForRecipeFileClicked()));
	m_pCreateRecipeWin = new CreateRecipeWindow(this);
	connect(ui.ToggleCalendarButton, SIGNAL(clicked()), this, SLOT(onToggleCalendar()));

	connect(m_pController, SIGNAL(logRecipe(Recipe)), this, SLOT(onLogRecipe(Recipe)));
	connect(this, SIGNAL(AddRecipesFromFileSignal(QString)), m_pController, SLOT(onAddRecipesFromFile(QString)));


	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onNewRecClicked(QListWidgetItem*)));

	// setting up create recipe window connects
	connect(m_pCreateRecipeWin, SIGNAL(NewRecipeSignal(Recipe)), m_pController, SLOT(onNewRecipeAdded(Recipe))); // only send new recipes to controller, the controller will pass them back to main gui to populate listwidget

	connect(this, SIGNAL(PopulateCreateRecWindow(Recipe)), m_pCreateRecipeWin, SLOT(onPopulateWithRecipe(Recipe)));

	connect(this, SIGNAL(RemoveRecipeAtSignal(int)), m_pController, SLOT(onRemoveRecipeAt(int)));

	//connect(m_pController, SIGNAL(UpdateGuiSignal(Recipe*, int)), this, SLOT(onUpdateGui(Recipe*, int)));
	connect(m_pController, SIGNAL(UpdateGuiSignal(QList<Recipe>)), this, SLOT(onUpdateGui(QList<Recipe>)));

	

	//connect(this, SIGNAL(closeEvent()), m_pDetailsWidget, SLOT(deleteLater()));
	//connect(this, SIGNAL(closeEvent()), m_pCreateRecipeWin, SLOT(deleteLater()));




	//connect(m_pCreateRecipeWin, SIGNAL(NewRecipeSignal(Recipe)), this, SLOT(onSaveNewRecipe(Recipe)));




	addDefaultRecipes();



}

MealPlanner::~MealPlanner()
{
	//m_pDetailsWidget->deleteLater();
	m_pDetailsWidget->close();
	m_pCreateRecipeWin->close();

}

void MealPlanner::onBrowseForRecipeFileClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Recipe File"), "", tr("xml files (*.xml)"));
	ui.AddRecipesFromFileLineEdit->setText(fileName);

}

void MealPlanner::onAddRecipesFromFileClicked()
{
	QString path = ui.AddRecipesFromFileLineEdit->text();
	if (!path.isEmpty()) {
		emit AddRecipesFromFileSignal(path);
	}

}

void MealPlanner::onRemoveSelectedRecipe()
{
	int nSelected = ui.listWidget->currentRow();
	emit RemoveRecipeAtSignal(nSelected);
}


void MealPlanner::onEditRecipe()
{
	int nSelection = ui.listWidget->currentRow();
	Recipe rec = m_pController->GetRecAt(nSelection);
	emit PopulateCreateRecWindow(rec);

}

void MealPlanner::onLogRecipe(Recipe rec)
{
#if (0)
	QString str;
	str = "------- RECIPE -------";
	ui.LogTextBrowser->append(str);
	str = "Title: " + rec.getTitle();
	ui.LogTextBrowser->append(str);
	str = "Ingredient Count: " + QString::number(rec.getNumberOfIngredients());
	ui.LogTextBrowser->append(str);
	if (rec.CheckWhole30()) {
		str = "Whole30 Compliant: TRUE";
	}
	else {
		str = "Whole30 Compliant: FALSE";
	}
	ui.LogTextBrowser->append(str);
	str = "----------------------";
	ui.LogTextBrowser->append(str);
#else
	QString str;
	str = "------- RECIPE -------\n";
	str += "Title: " + rec.getTitle();
	str += "\tIngredient Count: " + QString::number(rec.getNumberOfIngredients());
	if (rec.CheckWhole30()) {
		str += "\tWhole30 Compliant: TRUE";
	}
	else {
		str += "\tWhole30 Compliant: FALSE";
	}
	str += "\n----------------------";
	ui.LogTextBrowser->append(str);
#endif


}

void MealPlanner::addDefaultRecipes()
{

	Recipe rec;
	Ingredient* ing;
	rec.m_bWhole30 = true;
	rec.m_dTimeToCook = 20;
	rec.m_strName = "Eggs";
	rec.m_strRecipeDescription = "Cook the eggs in the oil and add salt to taste";

	ing = new Ingredient();
	ing->m_dQuantity = 3;
	ing->m_strName = "Eggs";
	ing->m_bWhole30 = true;
	ing->m_Unit = Ingredient::Units::Quant;
	rec.addIngredient(*ing);

	ing = new Ingredient();
	ing->m_dQuantity = 1;
	ing->m_strName = "oil";
	ing->m_bWhole30 = true;
	ing->m_Unit = Ingredient::Units::Tablespoon;
	rec.addIngredient(*ing);

	ing = new Ingredient();
	ing->m_dQuantity = 1;
	ing->m_strName = "salt";
	ing->m_bWhole30 = true;
	ing->m_Unit = Ingredient::Units::Teaspoon;
	rec.addIngredient(*ing);

	m_pController->onNewRecipeAdded(rec);

	// Next recipe
	Recipe rec2;
	rec2.m_bWhole30 = true;
	rec2.m_dTimeToCook = 20;
	rec2.m_strName = "Eggs2";
	rec2.m_strRecipeDescription = "Cook the eggs in the oil and add salt to taste";

	ing = new Ingredient();
	ing->m_dQuantity = 6;
	ing->m_strName = "Eggs";
	ing->m_bWhole30 = true;
	ing->m_Unit = Ingredient::Units::Quant;
	rec2.addIngredient(*ing);

	ing = new Ingredient();
	ing->m_dQuantity = 2;
	ing->m_strName = "oil";
	ing->m_bWhole30 = true;
	ing->m_Unit = Ingredient::Units::Tablespoon;
	rec2.addIngredient(*ing);

	ing = new Ingredient();
	ing->m_dQuantity = 2;
	ing->m_strName = "salt";
	ing->m_bWhole30 = true;
	ing->m_Unit = Ingredient::Units::Teaspoon;
	rec2.addIngredient(*ing);

	m_pController->onNewRecipeAdded(rec2);

	m_pController->UpdateGuiRecipes();
}


void MealPlanner::onToggleCalendar()
{
	m_bCalendarVisible = !m_bCalendarVisible;

	ui.CalendarTable->setVisible(m_bCalendarVisible);
	


}


// not being used right now
void MealPlanner::onSaveNewRecipe(Recipe rec)
{
	//int nNum = rec.getNumberOfIngredients();

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

	//m_pDetailsWidget->ui.IngredientListWidget->clear();
	m_pDetailsWidget->ui.IngredientTableWidget->clear();
	//m_pDetailsWidget->ui.IngredientsPlainTextEdit->clear();
	m_pDetailsWidget->ui.RecipeDetailsPlainTextEdit->clear();
	m_pDetailsWidget->ui.RecipeDetailsPlainTextEdit->setPlainText(rec.m_strRecipeDescription);
	Ingredient currIng;

	QTableWidget* table = m_pDetailsWidget->ui.IngredientTableWidget;
	QTableWidgetItem *item;
	QDoubleSpinBox* quantSpinBox;
	QComboBox* unitComboBox;
	Ingredient* ing;
	table->setRowCount(rec.getNumberOfIngredients());
	for (int i = 0; i < rec.getNumberOfIngredients(); i++) {
		
		ing = rec.getIngredient(i);

		m_pDetailsWidget->AddIngredientToList(i, ing->getName(), ing->getQuantity(), ing->m_Unit);
		


	}
	m_pDetailsWidget->SetEditableMode(false);

	//QListWidgetItem* item;
	//for (int i = 0; i < rec.m_IngredientList.length(); i++) {
	//	currIng = rec.m_IngredientList.at(i);
	//	item = new QListWidgetItem(currIng.getName());
	//	m_pDetailsWidget->ui.IngredientListWidget->addItem(item);
	//}
	m_pDetailsWidget->ui.Whole30CheckBox->setChecked(rec.m_bWhole30);

}

void MealPlanner::onCreateRecipe()
{
	if ( !m_pCreateRecipeWin )
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
			item = new QListWidgetItem(QString(RecList[i].m_strName));
		item->setText(QString(RecList[i].m_strName));

		ui.listWidget->addItem(item);
	}

}

void MealPlanner::onUpdateGui(Recipe* pRec, int nNumRec)
{
	////Not being used right now
	//ui.listWidget->clear();

	//Recipe currRec;
	//QListWidgetItem* item;
	//for (int i = 0; i < nNumRec; i++) {
	//	currRec = pRec[i];
	//	item = ui.listWidget->item(i);
	//	if ( !item ) 
	//		item = new QListWidgetItem(currRec.m_strName);
	//	item->setText(currRec.m_strName);

	//	ui.listWidget->addItem(item);


	//}


}







