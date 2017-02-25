#pragma once



#include <QString>
#include <qstringlist.h>



class Ingredient
{
public:
	Ingredient();
	~Ingredient();

	const static int nNumUnits = 8;
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
	QStringList const UnitsList = QStringList() << QString("None") << QString("Quant") << QString("Pinch") << QString("Teaspoon") << QString("Tablespoon") << QString("Cups") << QString("Quart") << QString("Gallon");

	QString m_strName;
	double m_dQuantity;
	Units m_Unit;
	bool m_bWhole30;

	// methods
	QString getUnitString() { return getUnitString(m_Unit); }
	Ingredient::Units getUnit() { return m_Unit; }
	double getQuantity() { return m_dQuantity; }
	QString getName() { return m_strName; }

};

