#pragma once



#include <QString>
#include <qstringlist.h>



class Ingredient
{
public:
	Ingredient();
	~Ingredient();

	enum Units {
		None,
		Quant,
		Pinch, 
		Teaspoon,
		Tablespoon,
		Cups,
		Quart,
		Gallon
	};


private:

	QString getUnitString(Units nUnit) { return UnitsList.at(nUnit); }


public:
	QStringList UnitsList;

	QString m_strName;
	double m_dQuantity;
	Units m_Unit;
	bool m_bWhole30;

	// methods
	QString getUnitString() { return getUnitString(m_Unit); }
	double getQuantity() { return m_dQuantity; }
	QString getName() { return m_strName; }

};

