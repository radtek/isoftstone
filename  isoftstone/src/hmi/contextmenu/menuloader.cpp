
#include <QDebug>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QStyleOption>

#include "menuloader.h"
#include "macro.h"
#include "enum.h"
#include "setting.h"

/*
	每类菜单的code不能重复，否则会造成部分不能显示
*/
CMenuLoader::CMenuLoader(QObject* receiver):m_Receiver(receiver)
{
	initAppMap();
	loadMenu();
}

void CMenuLoader::initAppMap()
{
	QByteArray qbr = qgetenv(PROJECT_HOME);
	QString confDir = QString(qbr.data()) + "/config/popup/";
	QSettings st(confDir + "mng_app_num_name.ini",QSettings::IniFormat);
	st.beginGroup("ALLAPP");

	QStringList lstApp = st.allKeys();
	foreach(QString app,lstApp)
	{
		quint64 appID = st.value(app).toLongLong();
		m_AppMap.insert(app,appID);
	}
	st.endGroup();
}

void CMenuLoader::loadMenu()
{
	QByteArray qbr = qgetenv(PROJECT_HOME);
	QString confDir = QString(qbr.data()) + "/config/popup/";

	QString relationFile = confDir + "popup_menu_relation.ini";
	
	CSettings st(relationFile);
	QStringList lstClass = st.childGroups();
	foreach (QString strApp,lstClass)
	{
		quint64 appID = m_AppMap[strApp];

		st.beginGroup(strApp);
		QStringList lstItem = st.allKeys();
		QMap<int,QString> itemMap;
		foreach(QString strItem,lstItem)
		{
 			QString str = st.value(strItem).toString();
 			int eType = stringToType(strItem);
 			itemMap.insert(eType,str);
		}

		m_RelationMap.insert(appID,itemMap);
		st.endGroup();
	}
	

	QFileInfoList lstPopup = QDir(confDir).entryInfoList(QStringList() << ("*_popup_menu.ini"),QDir::Files);
	foreach(QFileInfo info,lstPopup)
	{
		if (info.isFile())
		{
			QString absPath = info.absoluteFilePath();
			QMap<QString,QVector<SMenuInfo> > menuMap;
			
			QString baseName = QFileInfo(absPath).baseName();
			QString strApp = baseName.remove("_popup_menu");
			loadMenu(absPath,strApp,menuMap);
			quint64 appID = m_AppMap[strApp];

			m_PopupMenuMap.insert(appID,menuMap);
		}
	}
}

void CMenuLoader::loadMenu(const QString& strFile,const QString& strApp,QMap<QString,QVector<SMenuInfo> >& menuMap)
{
	menuMap.clear();

	if (m_AppMap.contains(strApp))
	{
		quint64 appID = m_AppMap[strApp];
		CSettings st(strFile);
		QStringList lstClass = st.childGroups();
		foreach (QString strMenu,lstClass)
		{
			st.beginGroup(strMenu);
			QStringList lstAction = st.allKeys();

			QVector<SMenuInfo> vecMenus;
			foreach(QString strAction,lstAction)
			{
				SMenuInfo sInfo;
				if (strAction.contains("LABEL_NAME"))
				{
					sInfo.eMenuType = eLabelName;
					sInfo.strText = st.value(strAction).toString();
				}
				else if (strAction.contains("SEPARATOR"))
				{
					sInfo.eMenuType = eSeparator;
				}
				else if (strAction.contains("NORMAL_MENU"))
				{
					sInfo.eMenuType = eNormalMenu;
					QString txt = st.value(strAction).toString();
					QStringList lst = txt.split('/');
					if (lst.count() > 0)
					{
						sInfo.strText = lst[0];
					}
					if (lst.count() > 1)
					{
						sInfo.nCommand = lst[1].toInt();
					}
				}
				else if (strAction.contains("SUB_MENU"))
				{
					sInfo.eMenuType = eSubMenu;
					sInfo.strText = st.value(strAction).toString();
				}
				else
				{
					sInfo.eMenuType = eSeparator;
				}

				vecMenus.append(sInfo);
			}
			st.endGroup();

			menuMap.insert(strMenu,vecMenus);
		}
	}
}

QMenu* CMenuLoader::createMenu(quint64 appID,const QString& group)
{
	QMenu* pMenu = new QMenu();

	QVector<SMenuInfo> vecMenus;
	if (!group.isEmpty())
	{
		vecMenus = m_PopupMenuMap[appID][group];
	}
	for (int i = 0 ; i < vecMenus.count() ; i++)
	{
		const SMenuInfo& sMenu = vecMenus[i];
		if (sMenu.eMenuType == eLabelName)
		{
			pMenu->addMenu(sMenu.strText);
		}
		else if (sMenu.eMenuType == eSeparator)
		{
			QAction* pSep = new QAction(pMenu);
			pSep->setSeparator(true);
			pMenu->addAction(pSep);
		}
		else if (sMenu.eMenuType == eNormalMenu)
		{
			QAction* pAction = pMenu->addAction(sMenu.strText);
			pAction->setData(sMenu.nCommand);
			QObject::connect(pAction, SIGNAL(triggered()), m_Receiver, SLOT(onActionClick()));
		}
		else if (sMenu.eMenuType == eSubMenu)
		{
			QMenu* subMenu = createMenu(appID,sMenu.strText);
			subMenu->setTitle(sMenu.strText);
			pMenu->addMenu(subMenu);
		}
	}
	return pMenu;
}


QMenu* CMenuLoader::getMenu(quint64 appID,int itemType)
{
	if (m_MenuMap.contains(appID))
	{
		if (m_MenuMap[appID].contains(itemType))
		{
			return m_MenuMap[appID][itemType];
		}
	}

	QString group = m_RelationMap[appID][itemType];
	QMenu* pMenu = createMenu(appID,group);
	m_MenuMap[appID][itemType] = pMenu;
	return pMenu;
}


void CMenuLoader::destory()
{
	m_RelationMap.clear();
	m_PopupMenuMap.clear();
	m_MenuMap.clear();
}

int CMenuLoader::stringToType(const QString& strType)
{
	if(strType == "CIMGBusDis") return CIMGBusDis ;
	if(strType == "CIMGCircle") return CIMGCircle ;
	if(strType == "CIMGLine") return CIMGLine ;
	if(strType == "CIMGTriangle") return CIMGTriangle ;
	if(strType == "CIMGPolyLine") return CIMGPolyLine ;
	if(strType == "CIMGRoundRect") return CIMGRoundRect ;
	if(strType == "CIMGPolygon") return CIMGPolygon ;
	if(strType == "CIMGImage") return CIMGImage ;
	if(strType == "CIMGDiamond") return CIMGDiamond ;
	if(strType == "CIMGEllipse") return CIMGEllipse ;
	if(strType == "CIMGFeedLine") return CIMGFeedLine ;
	if(strType == "CIMGLoadDisPloy") return CIMGLoadDisPloy ;
	if(strType == "CIMGCube") return CIMGCube ;
	if(strType == "CIMGHandgon") return CIMGHandgon ;
	if(strType == "CIMGLogconductorDis") return CIMGLogconductorDis ;
	if(strType == "CIMGRect") return CIMGRect ;
	if(strType == "CIMGCirclearc") return CIMGCirclearc ;
	if(strType == "CIMGHandLine") return CIMGHandLine ;
	if(strType == "CIMGEllipsearc") return CIMGEllipsearc ;
	if(strType == "CIMGParallelrect") return CIMGParallelrect ;
	if(strType == "CIMGText") return CIMGText ;
	if(strType == "CIMGDText") return CIMGDText ;
	if(strType == "CIMGPoke") return CIMGPoke ;
	if(strType == "CIMGDisconnector") return CIMGDisconnector ;
	if(strType == "CIMGConnectLine") return CIMGConnectLine ;
	if(strType == "CIMGCBreaker") return CIMGCBreaker ;
	if(strType == "CIMGGenerator") return CIMGGenerator ;
	if(strType == "CIMGTransformer2") return CIMGTransformer2 ;
	if(strType == "CIMGTransformer3") return CIMGTransformer3 ;
	if(strType == "CIMGRcBreaker") return CIMGRcBreaker ;
	if(strType == "CIMGAcline") return CIMGAcline ;
	if(strType == "CIMGACLineEnd") return CIMGACLineEnd ;
	if(strType == "CIMGDcLine") return CIMGDcLine ;
	if(strType == "CIMGDcDot") return CIMGDcDot ;
	if(strType == "CIMGEnergyConsumer") return CIMGEnergyConsumer ;
	if(strType == "CIMGGroundDisconnector") return CIMGGroundDisconnector ;
	if(strType == "CIMGCT") return CIMGCT ;
	if(strType == "CIMGDollyBreaker") return CIMGDollyBreaker ;
	if(strType == "CIMGTerminal") return CIMGTerminal ;
	if(strType == "CIMGAscoil") return CIMGAscoil ;
	if(strType == "CIMGProtect") return CIMGProtect ;
	if(strType == "CIMGArrester") return CIMGArrester ;
	if(strType == "CIMGPT") return CIMGPT ;
	if(strType == "CIMGFuse") return CIMGFuse ;
	if(strType == "CIMGCapacitor_P") return CIMGCapacitor_P ;
	if(strType == "CIMGReactor_P") return CIMGReactor_P ;
	if(strType == "CIMGClock") return CIMGClock ;
	if(strType == "CIMGCurve") return CIMGCurve ;
	if(strType == "CIMGPie") return CIMGPie ;
	if(strType == "CIMGBar") return CIMGBar ;
	if(strType == "CIMGHisTable") return CIMGHisTable ;
	if(strType == "CIMGDial") return CIMGDial ;
	if(strType == "CIMGWDM") return CIMGWDM ;
	if(strType == "CIMGBay") return CIMGBay ;
	if(strType == "CIMGTable") return CIMGTable ;
	if(strType == "CIMGSensitive") return CIMGSensitive ;
	if(strType == "CIMGStatus") return CIMGStatus ;
	if(strType == "CIMGGzp") return CIMGGzp ;
	if(strType == "CIMGState") return CIMGState ;
	if(strType == "CIMGOther") return CIMGOther ;
	if(strType == "CIMGPowerFlow") return CIMGPowerFlow ;
	if(strType == "CIMGDynamicText") return CIMGDynamicText ;
	if(strType == "CIMGState") return CIMGState ;

	return CIMGCommon;
}