#ifndef ALG_H
#define	ALG_H

#include "setting.h"

class CAlg
{
public:
	enum Mode { eInsert, eRemove};
	static void moveCommand(QString strApp, QString strItem, int iPos, Mode eType)
	{
		char* visdir = getenv("VISDIR");
		QString strFileName = QString(visdir) + "/conf/popup/" + strApp + "_popup_menu.ini";
		CSettings st(strFileName);
		st.beginGroup(strItem);

		int iMax = getMaxPos(strApp, strItem);	// ×î´óÎ»ÖÃ

		if (eInsert == eType)
		{
			for (int i = iMax; i >= iPos; i-- )
			{
				QString strPos = getStrByPos(strApp, strItem, i);
				QStringList lstPos = strPos.split("_");
				QString strCommand = st.value(strPos).toString();
				st.remove(strPos);
				strPos.clear();
				lstPos.last() = QString("%1").arg(i+1);
				foreach (QString str, lstPos)
				{
					strPos.push_back(str);
					if (str != lstPos.last())
					{
						strPos.push_back("_");
					}					
				}						
				st.setValue(strPos, strCommand);	
			}
		}

		else
		{
			for (int i = iPos + 1 ; i <= iMax; i++)
			{
				QString strPos = getStrByPos(strApp, strItem, i);
				QStringList lstPos = strPos.split("_");
				QString strCommand = st.value(strPos).toString();
				st.remove(strPos);	
				strPos.clear();
				lstPos.last() = QString("%1").arg(i - 1);
				foreach (QString str, lstPos)
				{
					strPos.push_back(str);
					if (str != lstPos.last())
					{
						strPos.push_back("_");
					}					
				}						
				st.setValue(strPos, strCommand);	
			}
		}

		st.endGroup();
		st.sync();
	}

	static int getMaxPos(QString strApp, QString strItem)
	{
		int iMax = 0;
		char* visdir = getenv("VISDIR");
		QString strFileName = QString(visdir) + "/conf/popup/" + strApp + "_popup_menu.ini";
		CSettings st(strFileName);
		st.beginGroup(strItem);
		foreach (QString str, st.allKeys())
		{
			QStringList lstPos = str.split("_");
			int iNo = lstPos.last().toInt();
			if (iNo > iMax)
			{
				iMax = iNo;
			}
		}
		st.endGroup();
		return iMax;
	}

	static QString getStrByPos(QString strApp, QString strItem, int iPos)
	{
		QString strPos;
		char* visdir = getenv("VISDIR");
		QString strFileName = QString(visdir) + "/conf/popup/" + strApp + "_popup_menu.ini";
		CSettings st(strFileName);
		st.beginGroup(strItem);
		foreach (QString str, st.allKeys())
		{
			QStringList lstPos = str.split("_");
			int iNo = lstPos.last().toInt();
			if (iNo == iPos)
			{
				strPos = str;
				break;
			}
		}
		st.endGroup();
		return strPos;
	}
	

};

#endif