#include "RecipeDetailsWidget.h"

RecipeDetailsWidget::RecipeDetailsWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

RecipeDetailsWidget::~RecipeDetailsWidget()
{
}



void RecipeDetailsWidget::AddIngredientToList(int nRow, QString strName, double dQuant, Ingredient::Units nUnit)
{
	QTableWidget* table = ui.IngredientTableWidget;

	table->insertRow(nRow);

	QTableWidgetItem* item = new QTableWidgetItem(strName);
	
	QDoubleSpinBox* quantSpinBox = new QDoubleSpinBox(table);

	quantSpinBox->setMinimum(0);
	quantSpinBox->setMaximum(100);
	quantSpinBox->setValue(dQuant);
	quantSpinBox->setFixedWidth(65);

	UnitComboBox* unitBox = new UnitComboBox(table);
	unitBox->setCurrentIndex(nUnit);

	table->setItem(nRow, 0, item);
	table->setCellWidget(nRow, 1, quantSpinBox);
	table->setCellWidget(nRow, 2, unitBox);


}

bool RecipeDetailsWidget::SetRecipeDetails(QString strDetails)
{
	ui.RecipeDetailsPlainTextEdit->setPlainText(strDetails);
	return true;
}


bool RecipeDetailsWidget::SetEditableMode(bool bEditable)
{
	m_bEditableMode = bEditable;

	ui.RecipeTitleLineEdit->setReadOnly(!bEditable);
	ui.RecipeDetailsPlainTextEdit->setReadOnly(!bEditable);

	SetTableEditable(bEditable);

	return true;
}

// Working questionably... Doesn't make combo or spinbox non-editable right now
bool RecipeDetailsWidget::SetTableEditable(bool bEditable)
{
	Qt::ItemFlags flags;
	QTableWidgetItem* item;
	for (int i = 0; i < ui.IngredientTableWidget->rowCount(); i++) {
		for (int j = 0; j < ui.IngredientTableWidget->columnCount(); j++) {
			Qt::ItemFlag::ItemIsEditable;
			item = ui.IngredientTableWidget->item(i, j);
			if (!item) {
				item = new QTableWidgetItem();
			}
				flags = item->flags();
				if (bEditable)
					flags &= Qt::ItemIsEditable;
				else
					flags &= ~Qt::ItemIsEditable;
				item->setFlags(flags);
				ui.IngredientTableWidget->setItem(i, j,item);
		}
	}
	return true;
}