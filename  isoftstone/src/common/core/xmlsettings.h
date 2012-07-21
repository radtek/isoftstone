#ifndef SETTINGS_H
#define SETTINGS_H

#include "escore.h"
#include "iestypedef.h"
#include <qstring.h>
#include <qstringlist.h>
#include "interface.h"
#include <qdom.h> 

#include "objects.h"

struct SXmlEntryFactor
{
	virtual void operator()( QDomNode& node) = 0;
};

struct SNodeValueFactor : public SXmlEntryFactor
{
	virtual void operator()( QDomNode& node)
	{
		QDomText domValue = node.firstChild().toText();
		// ������Լ�û��ֵ����᷵�� QString::null
		ret = domValue.data();
	}

	QString ret;
};

struct SNodePropertyFactor : public SXmlEntryFactor
{
	virtual void operator()( QDomNode& node)
	{
		QStringList::const_iterator it = attribute.begin();
		QString value = "";
		for (;it != attribute.end();it++)
		{
			const QString& attr = *it;
			value = node.toElement().attribute(attr);
			ret.push_back(value);
		}
	}

	QStringList ret;
	QStringList attribute;
};


class LIBCORE_EXPORT CXmlSettings
{
public:
	// bFile=JTRUE ʱ string ���ļ���
	// bFile=JFALSE ʱ string �� xml Ƭ���ַ���
	// bNoThrowException=JTRUE ���������ļ�ʧ�ܻ��� xml Ƭ�ϷǷ������쳣
	// bNoThrowException=JFALSE ���������ļ�ʧ�ܻ��� xml Ƭ�ϷǷ��������쳣
	CXmlSettings(const QString& string, bool bFile=JTRUE, bool bThrowException=JFALSE);

	CXmlSettings();

	void open(const QString& string, bool bFile=JTRUE, bool bThrowException=JFALSE);

	virtual ~CXmlSettings();

	// �����ļ��Ƿ���سɹ�
	bool isReady() const;

	//## ��������Ϣд���ļ�
	bool flush();

	//���������ļ���Ȼ���ȡ�ļ��ַ�����
	QString getXmlSettings();

	//�����ļ��ַ����ݣ�Ȼ�����������ļ�
	void setXmlSettings( const QString& xml );

	//��ճ�root�ڵ������нڵ�
	bool clear();

	bool writeEntry(const QString& key, const QString& attribute, const QString& value);

    bool writeNumEntry(const QString& key, const QString& attribute, Jint32 value );

    bool writeBoolEntry(const QString& key, const QString& attribute, bool value);

    bool writeDoubleEntry(const QString& key, const QString& attribute, Jdouble value);

	QString readEntryByPath(const QString& path);

	Juint32 readIntByPath(const QString& path);

	Jdouble readDoubleByPath(const QString& path);

	bool readBoolByPath(const QString& path);

	QStringList readEntryByPath(const QString& path, const QStringList& attribute);

	void locateEntryAndOper(const QString& path,SXmlEntryFactor* factor);

	QString readEntry(const QString& key, const QString& attribute, const QString& defaultValue = QString::null, bool* ok = NULL);

    Jint32 readNumEntry(const QString& key, const QString& attribute, Jint32 defaultValue = 0, bool* ok = NULL);

    bool readBoolEntry(const QString& key, const QString& attribute, bool defaultValue = JFALSE, bool* ok = NULL);

    Jdouble readDoubleEntry(const QString& key, const QString& attribute, Jdouble defaultValue = 0.0, bool* ok = NULL);


	bool removeEntry(const QString& key);

	bool removeEntry(const QString& key, const QString& attribute);

protected:
	//## �������ļ��ж�ȡ������Ϣ
	bool readSetting();

	//## ��ȡ���������û�����ȴ���
	QDomNode getRootKey(const QString& rootName);

	// �Ӽ�ֵ�б����ҳ� key �Ľڵ�
	QDomElement getKeyElement(const QString& key);

	//## �����ļ����سɹ�
	bool m_bReady;

	//## ������Ϣ�Ƿ��޸�
	bool m_bDirty;

	//## �����ļ���
	QString m_strFileName;

	//xml�ַ���
	QString m_xmlString;

	//�ļ�����xmlƬ��
	bool m_bFile;

	//## �����ļ����ڴ��еĻ���
	QDomDocument m_domDocument;
};

typedef CSigleton<CXmlSettings> CSettingSigleton;

class LIBCORE_EXPORT CFileTransformer : public CXmlSettings
{
public:

	void transform(const QString& csvfile,const QString& xmlfile );

	virtual void transformAction(const QString& csvfile) = 0;

};

#endif // SETTINGS_H
