#include "Ingredient.h"


Ingredient::Ingredient()
{
	// filling the string list... Could do this better maybe.
	//UnitsList.append("None");
	//UnitsList.append("Quant");
	//UnitsList.append("Pinch");
	//UnitsList.append("Teaspoon");
	//UnitsList.append("Tablespoon");
	//UnitsList.append("Cups");
	//UnitsList.append("Quart");
	//UnitsList.append("Gallon");

	m_Unit = Units::None;
	m_strName = "No Name";
	m_dQuantity = -1;
	m_bWhole30 = false;

}


Ingredient::~Ingredient()
{
}
