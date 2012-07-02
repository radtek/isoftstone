
#include "dllplugin.h"

CDllPluginProxy* CDllPluginProxy::s_dllPlugin = NULL;

CDllPluginProxy* CDllPluginProxy::instance(void)
{
	if (s_dllPlugin == NULL)
	{
		s_dllPlugin = new CDllPluginProxy();
	}
	return s_dllPlugin;
}