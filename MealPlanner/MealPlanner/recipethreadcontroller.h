#ifndef RECIPETHREADCONTROLLER_H
#define RECIPETHREADCONTROLLER_H

#include <QObject>
#include "Recipe.h"
#include "CreateRecipeWindow.h"

class RecipeThreadController : public QObject
{
	Q_OBJECT

public:
	RecipeThreadController(QObject *parent);
	~RecipeThreadController();

	QWidget* m_Parent;

public slots:

	void onStartController();
	void onCreateRecipe();

signals:
	void finished();


private:
	
};

#endif // RECIPETHREADCONTROLLER_H
