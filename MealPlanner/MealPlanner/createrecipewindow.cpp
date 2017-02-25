#include "createrecipewindow.h"

CreateRecipeWindow::CreateRecipeWindow(QWidget *parent)
	//: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.SaveRecipeButton, SIGNAL(clicked()), this, SLOT(onSaveRecipeClicked()));

	connect(ui.AddIngredientRowButton, SIGNAL(clicked()), this, SLOT(onAddIngredientRowClicked()));
	connect(ui.RemoveSelectedRowButton, SIGNAL(clicked()), this, SLOT(onRemoveSelectedRowClicked()));

}

CreateRecipeWindow::~CreateRecipeWindow()
{

}

void CreateRecipeWindow::onAddIngredientRowClicked()
{

	ui.RecDetailsWidget->AddIngredientToList(ui.RecDetailsWidget->ui.IngredientTableWidget->rowCount(), "", 0, Ingredient::Units::None);

}

void CreateRecipeWindow::onRemoveSelectedRowClicked()
{
	int nSelected = ui.RecDetailsWidget->ui.IngredientTableWidget->currentRow();
	ui.RecDetailsWidget->ui.IngredientTableWidget->removeRow(nSelected);

}

void CreateRecipeWindow::onSaveRecipeClicked()
{
	Recipe rec;

	rec.m_bWhole30 = ui.RecDetailsWidget->ui.Whole30CheckBox->isChecked();
	rec.m_dTimeToCook = ui.RecDetailsWidget->ui.TimeRequiredLineEdit->text().toDouble();
	rec.m_strName = ui.RecDetailsWidget->ui.RecipeTitleLineEdit->text();
	rec.m_strRecipeDescription = ui.RecDetailsWidget->ui.RecipeDetailsPlainTextEdit->toPlainText();
	Ingredient ing;
	QTableWidgetItem* item;
	QWidget* widg;
	for (int i = 0; i < ui.RecDetailsWidget->ui.IngredientTableWidget->rowCount(); i++) {
		item = ui.RecDetailsWidget->ui.IngredientTableWidget->item(i,0);
		ing.m_strName = item->text();
		widg = ui.RecDetailsWidget->ui.IngredientTableWidget->cellWidget(i, 1);

		ing.m_dQuantity = ((QDoubleSpinBox*)widg)->value();

		widg = ui.RecDetailsWidget->ui.IngredientTableWidget->cellWidget(i, 2);
		ing.m_Unit = (Ingredient::Units)((UnitComboBox*)widg)->currentIndex();
		rec.addIngredient(ing);

	}

	emit NewRecipeSignal(rec);

}


void CreateRecipeWindow::onPopulateWithRecipe(Recipe rec)
{
	ui.RecDetailsWidget->ui.RecipeTitleLineEdit->setText(rec.getTitle());
	ui.RecDetailsWidget->ui.Whole30CheckBox->setChecked(rec.CheckWhole30());
	ui.RecDetailsWidget->ui.RecipeDetailsPlainTextEdit->setPlainText(rec.getDescription());
	ui.RecDetailsWidget->ui.TimeRequiredLineEdit->setText(rec.getTimeRequiredString());
	// ingredients
	ui.RecDetailsWidget->ui.IngredientTableWidget->clear();
	ui.RecDetailsWidget->ui.IngredientTableWidget->setRowCount(0);
	Ingredient *pIng;
	for (int i = 0; i < rec.getNumberOfIngredients(); i++) {
		pIng = rec.getIngredient(i);
		ui.RecDetailsWidget->AddIngredientToList(i, pIng->getName(), pIng->getQuantity(), pIng->getUnit());
	}

}