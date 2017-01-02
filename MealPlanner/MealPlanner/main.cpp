#include "mealplanner.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MealPlanner w;
	w.show();
	return a.exec();
}
