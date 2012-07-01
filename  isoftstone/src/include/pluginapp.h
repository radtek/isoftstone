
#ifndef PLUGIN_APPLICATION_H
#define PLUGIN_APPLICATION_H

#include "pluginbase.h"
#include "ialgorithm.h"

// Ӧ�ò��
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

	// ����menuBar,���²˵�
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

		// ���ص�MenuBar�Ӳ˵�
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
		// ���ص�MenuBar
		else if(actPair.first != NULL)
		{		
			m_ToolAction = m_MenuBar->insertMenu(actPair.first, m_ToolMenu);
			m_ToolAction->setParent(m_MenuBar);
		}
	}

	// ж�ز˵� ,ֻ��Ҫ��Ӧ�ò��ʹ�ü��ɣ��Ҽ��˵�����Ҫ����Ϊ�Ҽ��˵����Ƕ�̬ȥ��ȡ�Ĳ˵���
	virtual void unload() 
	{
		m_ToolMenu->clear();
		//��MenuBar�µ�Menuɾ��
		if(m_ParentMenu != NULL)	
		{
			m_ParentMenu->removeAction(m_ToolAction);
		}
		//ֱ�Ӵ�MenuBarɾ��
		else						
		{
			m_MenuBar->removeAction(m_ToolAction);
		}
	}

	// �����Ӳ˵��б�
	virtual QList<QAction*>  getMenuToolActions(bool* p_bHasMenu) 
	{
		return m_Actions;
	}

	// ���˵��ִ��ʱ���Ķ��������в�����������������Ϊ�۽�������
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