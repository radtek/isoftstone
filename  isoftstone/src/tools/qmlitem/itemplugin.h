
#ifndef ITEM_PLUGIN_H
#define ITEM_PLUGIN_H


#include <QDeclarativeExtensionPlugin>

class CItemPlugin : public QDeclarativeExtensionPlugin
{
	Q_OBJECT

public:

	void registerTypes(const char *uri);
};

#endif