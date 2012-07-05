
#ifndef PLUGIN_APPLICATION_H
#define PLUGIN_APPLICATION_H

#include "pluginbase.h"
#include "ialgorithm.h"

// 应用插件
class IPluginApplication : public IPluginBase
{
public:

	IPluginApplication()
	{
		m_ToolMenu = new QMenu();
		m_ActionGroup = new QActionGroup(NULL);
		m_Enabled  = false;
	}

	virtual EPluginType getPluginType()
	{
		return eApplicationPlugin;
	}

	bool isPluginEnabled()
	{
		return m_Enabled;
	}

	void setPluginEnabled(bool bEnabled) 
	{
		if (m_Enabled == bEnabled)
		{
			return;
		}


		if(!bEnabled)
		{
			unload();
		}
		else
		{
			if (!m_Enabled)
			{
				load(m_MenuBar);
			}		
		}
		m_Enabled = bEnabled;
	}

	virtual QPair<QString,QStringList> getMenuInfo() = 0;

	// 加载menuBar,更新菜单
	virtual void load(QMenuBar* menuBar) 
	{
		m_ParentMenu = NULL;
		m_MenuBar = menuBar;
		m_Enabled = true;		

		QPair<QString,QStringList> menuPair = getMenuInfo();

		QString strToolMenu = menuPair.first;
		QStringList lstMenu = menuPair.second;

		QPair<QAction*,bool> actPair = CAlgorithm::getParentMenu(lstMenu,menuBar->actions() );

		bool bHasMenu = true;

		QList<QAction*> lstAction = getMenuToolActions(&bHasMenu);

		m_ToolMenu->setTitle(strToolMenu);
		m_ToolMenu->addActions(lstAction);

		// 加载到MenuBar子菜单
		if(actPair.second == TRUE && actPair.first != NULL)
		{		
			m_ParentMenu = actPair.first->menu();
			if (bHasMenu)
			{
				m_ToolAction = m_ParentMenu->addMenu(m_ToolMenu);
			}
			else
			{
				m_ParentMenu->addAction(lstAction[0]);
				m_ToolAction = lstAction[0];
			}

			m_ToolAction->setParent(m_ParentMenu);
		}
		// 加载到MenuBar
		else if(actPair.first != NULL)
		{		
			m_ToolAction = m_MenuBar->insertMenu(actPair.first, m_ToolMenu);
			m_ToolAction->setParent(m_MenuBar);
		}
	}

	// 卸载菜单 ,只需要在应用插件使用即可，右键菜单不需要，因为右键菜单都是动态去获取的菜单项
	virtual void unload() 
	{
		m_ToolMenu->clear();
		//从MenuBar下的Menu删除
		if(m_ParentMenu != NULL)	
		{
			m_ParentMenu->removeAction(m_ToolAction);
		}
		//直接从MenuBar删除
		else						
		{
			m_MenuBar->removeAction(m_ToolAction);
		}
	}

	// 所有子菜单列表
	virtual QList<QAction*>  getMenuToolActions(bool* p_bHasMenu) 
	{
		return m_Actions;
	}

	// 当菜单项被执行时做的动作，所有插件必须派生，最好作为槽进行派生
	virtual void onActionExecute(bool) = 0;

	virtual ~IPluginApplication(){};

protected:

	QAction* createAction(const QString& strName)
	{
		QAction* action = new QAction(strName,NULL);
		action->setCheckable(true);
		m_ActionGroup->addAction(action);
		m_Actions.append(action);

		return action;
	}

protected:

	QList<QAction*>		   m_Actions;
	QMenuBar*			   m_MenuBar;
	QMenu*				   m_ToolMenu;
	QActionGroup*		   m_ActionGroup;
	QAction*			   m_ToolAction;
	QMenu*				   m_ParentMenu;
	bool				   m_Enabled;
};
#endif