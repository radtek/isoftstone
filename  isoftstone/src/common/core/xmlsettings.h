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
		// 如果属性键没有值，则会返回 QString::null
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
	// bFile=JTRUE 时 string 是文件名
	// bFile=JFALSE 时 string 是 xml 片断字符串
	// bNoThrowException=JTRUE 加载配置文件失败或者 xml 片断非法，抛异常
	// bNoThrowException=JFALSE 加载配置文件失败或者 xml 片断非法，不抛异常
	CXmlSettings(const QString& string, bool bFile=JTRUE, bool bThrowException=JFALSE);

	CXmlSettings();

	void open(const QString& string, bool bFile=JTRUE, bool bThrowException=JFALSE);

	virtual ~CXmlSettings();

	// 配置文件是否加载成功
	bool isReady() const;

	//## 把配置信息写入文件
	bool flush();

	//主动保存文件，然后获取文件字符内容
	QString getXmlSettings();

	//设置文件字符内容，然后主动保存文件
	void setXmlSettings( const QString& xml );

	//清空除root节点外所有节点
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
	//## 从配置文件中读取配置信息
	bool readSetting();

	//## 获取根键，如果没有则先创建
	QDomNode getRootKey(const QString& rootName);

	// 从键值列表中找出 key 的节点
	QDomElement getKeyElement(const QString& key);

	//## 配置文件加载成功
	bool m_bReady;

	//## 配置信息是否被修改
	bool m_bDirty;

	//## 配置文件名
	QString m_strFileName;

	//xml字符串
	QString m_xmlString;

	//文件或者xml片断
	bool m_bFile;

	//## 配置文件在内存中的缓存
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
