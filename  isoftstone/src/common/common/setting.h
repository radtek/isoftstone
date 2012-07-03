
#ifndef SETTING_H
#define SETTING_H

#include <QMap>
#include <QString>
#include <QVariant>
#include <QStringList>

#include "common.h"

class EXPORT_COMMON CSettings
{
public:

	CSettings(const QString& strFile);

	void load();
	void setIniCodec ( QTextCodec * codec );

	void beginGroup(const QString &prefix);
	void endGroup();
	QString group();

	QStringList allKeys() const;
	QStringList childGroups() const;
	void addGroups(const QString &group);
	void removeGroups(const QString &group);

	void setValue(const QString &key, const QVariant &value);
	QString	getValue(const QString &key, const QVariant &value);
	QString	getValue(const QString& group,const QString &key, const QVariant &value);
	void saveValue(const QString& group,const QString &key, const QVariant &value);
	void remove(const QString &key);
	bool contains(const QString &key) const;

	QVariant value( const QString & key, const QVariant & defaultValue = QVariant() ) const;
	QString fileName () const;
	void clear ();
	void sync ();

	QMap<QString,QMap<QString,QVariant> > getIniMap();

private:

	QMap<QString,QMap<QString,QVariant> >	m_IniMap;
	QMap<QString,QStringList>				m_SeqKeys;
	QStringList								m_SeqGroups;

	QString m_FileName;
	QString m_CurrentGroup;
};

#endif