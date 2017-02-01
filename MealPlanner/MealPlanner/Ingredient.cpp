#include "Ingredient.h"


Ingredient::Ingredient()
{
	UnitsList = { "None", "Quant", "Pinch", "Teaspoon", "Tablespoon", "Cups", "Quart", "Gallon" };

	m_Unit = Units::None;
	m_strName = "No Name";
	m_dQuantity = -1;
	m_bWhole30 = false;

}


Ingredient::~Ingredient()
{
}
