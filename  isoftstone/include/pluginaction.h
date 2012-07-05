
#ifndef PLUGIN_ACTION_H
#define PLUGIN_ACTION_H

#include "pluginbase.h"

class IPluginAction : public IPluginBase
{
public:

	virtual void onClick() = 0;
};

#endif