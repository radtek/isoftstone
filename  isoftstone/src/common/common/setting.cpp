
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>

#include "setting.h"

CSettings::CSettings(const QString& strFile):m_FileName(strFile)
{
	load();
}

void CSettings::setIniCodec ( QTextCodec *)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb2312"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));
}

void CSettings::load()
{
	QFile file(m_FileName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QStringList keyvalue;
		QTextStream in(&file);
		QString strGroup;
		while (!in.atEnd()) 
		{
			QString line = in.readLine().simplified();
			if (!line.isEmpty())
			{
				if (line.contains('[') && line.contains(']'))
				{
					QMap<QString,QVariant> keyValueMap;
					strGroup = line.remove("[").remove("]");
					m_IniMap.insert(strGroup,keyValueMap);
					m_SeqGroups.append(strGroup);
				}
				else if (line.split('=').count() == 2)
				{
					QStringList lst = line.split('=');
					//qDebug() << lst[0] << " = "<< lst[1] << "\n";
					m_IniMap[strGroup].insert(lst[0].simplified(),lst[1].simplified());
					m_SeqKeys[strGroup].append(lst[0].simplified());
				}
				else
				{
					//qDebug() << line << "\n";
				}
			}
		}
		file.close();
	}
}

void CSettings::beginGroup(const QString &prefix)
{
	m_CurrentGroup = prefix;
}

void CSettings::endGroup()
{
	m_CurrentGroup = "";
}

QString CSettings::group()
{
	return m_CurrentGroup;
}

void CSettings::addGroups(const QString &group)
{
	if(m_SeqGroups.contains(group) == false)
	{
		m_SeqGroups.append(group);
		m_SeqKeys.insert(group,QStringList());
		m_IniMap.insert(group,QMap<QString,QVariant>());
	}
}

void CSettings::removeGroups(const QString &group)
{
	if(m_SeqGroups.contains(group) == true)
	{
		m_SeqGroups.removeAt(m_SeqGroups.indexOf(group));
		m_SeqKeys.remove(group);
		m_IniMap.remove(group);
	}
}

QStringList CSettings::allKeys() const
{
	return m_SeqKeys[m_CurrentGroup];
}

QStringList CSettings::childGroups() const
{
	return m_SeqGroups;
}

void CSettings::setValue(const QString &key, const QVariant &defaultValue)
{
	if(!m_SeqKeys[m_CurrentGroup].contains(key))
	{
		m_SeqKeys[m_CurrentGroup].append(key);
	}	
	m_IniMap[m_CurrentGroup][key] = defaultValue;
}

QString	CSettings::getValue(const QString &key, const QVariant &defaultValue)
{
	return value(key,defaultValue).toString();
}

QString	CSettings::getValue(const QString& group,const QString &key, const QVariant &defaultValue)
{
	QString ret = "";
	beginGroup(group);
	QVariant var = value(key,defaultValue);
	ret = var.toString();
	endGroup();
	return ret;
}

void CSettings::saveValue(const QString& group,const QString &key, const QVariant &value)
{
	m_CurrentGroup = group;
	setValue(key,value);
	sync();
}

void CSettings::remove(const QString &key)
{
	m_SeqKeys[m_CurrentGroup].removeOne(key);
	m_IniMap[m_CurrentGroup].remove(key);
}

bool CSettings::contains(const QString &key) const
{
	if (m_IniMap[m_CurrentGroup].contains(key))
	{
		return true;
	}
	return false;
}

QVariant CSettings::value( const QString & key, const QVariant & defaultValue  ) const
{
	return m_IniMap[m_CurrentGroup][key];
}

QString CSettings::fileName () const
{
	return m_FileName;
}

void CSettings::sync()
{
	QFile file(m_FileName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&file);
		for (QStringList::Iterator iter = m_SeqGroups.begin() ; iter != m_SeqGroups.end() ; iter ++)
		{
			QString strGroup = *iter;
			out << "[" << strGroup << "]" << "\n";
			for (QStringList::Iterator it = m_SeqKeys[strGroup].begin() ; it != m_SeqKeys[strGroup].end() ; it++)
			{
				QString strKey = *it;
				out << strKey <<"=" << m_IniMap[strGroup][strKey].toString()<<"\n";
			}
			out<<"\n";
		}
		file.close();
	}
}

void CSettings::clear ()
{
	m_IniMap.clear();
}

QMap<QString,QMap<QString,QVariant> > CSettings::getIniMap()
{
	return m_IniMap;
}