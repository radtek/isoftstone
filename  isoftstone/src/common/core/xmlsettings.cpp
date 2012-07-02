#include <qfile.h> 
#include <qtextstream.h> 
#include <qtextcodec.h> 
#include <qobject.h>
#include "xmlsettings.h"
#include <qstringlist.h>
#include "exceptions.h"


CXmlSettings::CXmlSettings(const QString& string, bool bFile, bool bThrowException)
{
	open(string,bFile,bThrowException);
}

CXmlSettings::CXmlSettings()
{
}

CXmlSettings::~CXmlSettings()
{
	flush();
}

void CXmlSettings::open(const QString& string, bool bFile, bool bThrowException)
{
	m_bFile = bFile;
	m_bReady = JFALSE;
	m_bDirty = JFALSE;
	if ( m_bFile )
	{
		m_strFileName = string;
	}
	else
	{
		m_xmlString = string;
	}

	readSetting();
	if (!m_bReady && bThrowException)
	{
		if ( bFile )
		{
			// ���������ļ�ʧ��
			throw core::CFileException(QObject::tr("�����ļ���%1 ����ʧ��").arg(m_strFileName).toStdString());
		}
		else
		{
			// ���� xml Ƭ��ʧ��
			throw core::CCommonException(QObject::tr("xml Ƭ�ϣ�%1 ����ʧ��").arg(m_xmlString).toStdString());
		}
	}
}

bool CXmlSettings::readSetting()
{
	m_bReady = JFALSE;

	if ( m_bFile )
	{
		QFile f(m_strFileName);
		if (f.exists())
		{
			if (f.open(QIODevice::ReadOnly))
			{
				// �������������ļ�
				m_bReady = m_domDocument.setContent(&f, false);
				f.close();

				m_bDirty = JFALSE;
			}
		}
		else
		{
			// �����û�д������ļ�������Ϊ���سɹ����� flush �д���
			m_bDirty = JFALSE;
		}
	}
	else
	{
		if ( m_xmlString.isEmpty() )
		{
			// ����ǿ��ַ���������Ϊ���سɹ����� flush �д���
			m_bDirty = JFALSE;
			m_bReady = JTRUE;
		}
		else
		{
			// ��ȡ����
			m_bReady = m_domDocument.setContent( m_xmlString, false );
			m_bDirty = JFALSE;
		}
	}

	return m_bReady;
}

bool CXmlSettings::isReady() const
{
	return m_bReady;
}

bool CXmlSettings::flush()
{
	bool bRet = JFALSE;

	if (m_bReady && m_bDirty)
	{
		if ( m_bFile )
		{
			// ��������Ϣд���ļ�
			QFile f(m_strFileName);
			if (f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
			{
				QTextStream s(&f);
				QTextCodec *codec = QTextCodec::codecForName("utf8");
				s.setCodec(codec);
				m_domDocument.save(s, 4);
				f.close();

				m_bDirty = JFALSE;
				bRet = JTRUE;
			}
		}
		else
		{
			// ��������Ϣд���ļ�
			QTextStream s( &m_xmlString, QIODevice::ReadWrite );
			m_domDocument.save( s, 4 );

			m_bDirty = JFALSE;
			bRet = JTRUE;
		}
	}
	return bRet;
}

QDomNode CXmlSettings::getRootKey(const QString& rootName)
{
	QDomNode root = m_domDocument.firstChild();
	if (root.nodeName() != rootName)
	{
		root = root.nextSibling();
	}
	if (root.nodeName() != rootName)
	{
		// û�и��������ȴ�������
		root = m_domDocument.createElement("root");
		m_domDocument.appendChild(root);
	}
	return root;
}

QDomElement CXmlSettings::getKeyElement(const QString& key)
{
	QDomElement domKey;
	QDomNode root = getRootKey("root");
	QDomNodeList keyList = root.childNodes();
	for (Juint32 i=0; i<keyList.count(); ++i)
	{
		if (keyList.item(i).nodeName() == key)
		{
			domKey = keyList.item(i).toElement();
			break;
		}
	}
	return domKey;
}

bool CXmlSettings::writeEntry(const QString& key, const QString& attribute, const QString& value)
{
	bool bRet = JFALSE;

	// �ж��Ƿ����д˼�ֵ
	QDomElement domKey = getKeyElement(key);
	if (domKey.isNull())	// �޴˼�ֵ������keyԪ��
	{
		QDomNode root = getRootKey("root");
		domKey = m_domDocument.createElement(key);
		root.appendChild(domKey);
	}

	// �ж��Ƿ����д����Լ�
	// (��QDom�У���ʹdomKey��Ϊ�գ�����ĵ���Ҳ�᷵����ȷ�Ŀ�Element)
	QDomElement domAttrEle = 
		domKey.elementsByTagName(attribute).item(0).toElement();
	if (domAttrEle.isNull())	// �޴����ԣ�����attributeԪ��
	{
		domAttrEle = m_domDocument.createElement(attribute);
		domKey.appendChild(domAttrEle);
	}

	QDomText domValue = domAttrEle.firstChild().toText();
	if (domValue.isNull())
	{
		domValue = m_domDocument.createTextNode(value);
		domAttrEle.appendChild(domValue);
	}
	else
	{
		domValue.setNodeValue(value);
	}

	m_bReady = JTRUE;
	m_bDirty = JTRUE;
	bRet = JTRUE;

	return bRet;
}

QString CXmlSettings::readEntryByPath(const QString& path)
{
	SNodeValueFactor factor;
	locateEntryAndOper(path,&factor);
	return factor.ret;
}

Juint32 CXmlSettings::readIntByPath(const QString& path)
{
	return readEntryByPath(path).toInt();
}

Jdouble CXmlSettings::readDoubleByPath(const QString& path)
{
	return readEntryByPath(path).toDouble();
}

bool CXmlSettings::readBoolByPath(const QString& path)
{
	bool ret = false;
	QString value = readEntryByPath(path);
	if (value.toUpper() == "TRUE" || value.toInt() > 0)
	{
		ret = true;
	}
	return ret;
}

QStringList CXmlSettings::readEntryByPath(const QString& path, const QStringList& attribute)
{
	SNodePropertyFactor factor;
	factor.attribute = attribute;
	locateEntryAndOper(path,&factor);
	return factor.ret;
}

void CXmlSettings::locateEntryAndOper(const QString& path,SXmlEntryFactor* factor)
{
	QStringList keyNodes = path.simplified().split("/");
	QString ret = "";
	int count = keyNodes.count();
	if (count > 1)
	{
		const QString& keyName = keyNodes[0];
		QDomNode node = getRootKey(keyName);
		const QString& nodeName = node.nodeName();
		if (nodeName == keyName)
		{
			count--;

			QStringList::const_iterator iter = keyNodes.begin();
			iter++;
			for (; iter != keyNodes.end();iter++ ,count--)
			{
				QDomNodeList keyList = node.childNodes();
				for (Juint32 i=0; i < keyList.count(); ++i)
				{
					const QString& nodeName = keyList.item(i).nodeName();
					const QString& keyName = *iter;
					if ( nodeName == keyName)
					{
						node = keyList.item(i);
						if (count == 1)
						{
							(*factor)(node);
						}
						break;
					}
				}
			}
		}
	}
}

QString CXmlSettings::readEntry(const QString& key, const QString& attribute, const QString& defaultValue, bool* ok)
{
	QString value;
	bool bRet = JFALSE;

	if (m_bReady)
	{
		QDomElement domKey = getKeyElement(key);
		if (!domKey.isNull())
		{
			QDomNodeList attributeList = domKey.elementsByTagName(attribute);
			// �ж��Ƿ����д����Լ�
			if (attributeList.count() > 0)
			{
				QDomElement domAttribute = attributeList.item(0).toElement();
				QDomText domValue = domAttribute.firstChild().toText();
				// ������Լ�û��ֵ����᷵�� QString::null
				value = domValue.data();

				bRet = (value != QString::null);
			}
		}
	}
	if (ok)
	{
		*ok = bRet;
	}
	if (!bRet)
	{
		value = defaultValue;
	}

	return value;
}

bool CXmlSettings::removeEntry(const QString& key)
{
	bool bRet = JFALSE;

	if (m_bReady)
	{
		QDomElement domKey = getKeyElement(key);
		if (!domKey.isNull())
		{
			QDomNode root = getRootKey("root");
			root.removeChild(domKey);

			m_bDirty = JTRUE;
			bRet = JTRUE;
		}
	}

	return bRet;
}

bool CXmlSettings::removeEntry(const QString& key, const QString& attribute)
{
	bool bRet = JFALSE;

	if (m_bReady)
	{
		QDomElement domKey = getKeyElement(key);
		if (!domKey.isNull())
		{
			QDomNodeList attributeList = domKey.elementsByTagName(attribute);
			for (Juint32 i=0; i<attributeList.count(); ++i)
			{
				domKey.removeChild(attributeList.item(i));
			}

			m_bDirty = JTRUE;
			bRet = JTRUE;
		}
	}

	return bRet;
}

bool CXmlSettings::writeNumEntry(const QString& key, const QString& attribute, Jint32 value)
{
	return writeEntry(key, attribute, QString::number(value));
}

bool CXmlSettings::writeBoolEntry(const QString& key, const QString& attribute, bool value)
{
	return writeEntry(key, attribute, value ? "true" : "false");
}

bool CXmlSettings::writeDoubleEntry(const QString& key, const QString& attribute, Jdouble value)
{
	return writeEntry(key, attribute, QString::number(value));
}

Jint32 CXmlSettings::readNumEntry(const QString& key, const QString& attribute, Jint32 defaultValue, bool* ok)
{
	QString value = readEntry(key, attribute, QString::number(defaultValue), ok);
	// �ж�ȡ�ص��Ƿ�Ϊ��ֵ
    bool conv_ok;
    Jint32 retval = value.toInt( &conv_ok );
    if ( !conv_ok )
	{
		retval = defaultValue;
		if ( ok )
		{
			*ok = JFALSE;
		}
	}
	return retval;
}

bool CXmlSettings::readBoolEntry(const QString& key, const QString& attribute, bool defaultValue, bool* ok)
{
	QString value = readEntry(key, attribute, defaultValue ? "true" : "false", ok);
	// �ж�ȡ�ص��Ƿ�Ϊ������
	bool retval;
    if (value.toLower() == "true" || value == "1")
	{
		retval = JTRUE;
	}
    else if (value.toLower() == "false" || value == "0")
	{
		retval = JFALSE;
	}
	else
	{
		retval = defaultValue;
		if ( ok )
		{
			*ok = JFALSE;
		}
	}
	return retval;
}

Jdouble CXmlSettings::readDoubleEntry(const QString& key, const QString& attribute, Jdouble defaultValue, bool* ok)
{
	QString value = readEntry(key, attribute, QString::number(defaultValue), ok);
	// �ж�ȡ�ص��Ƿ�Ϊ��ֵ
    bool conv_ok;
	Jdouble retval = value.toDouble( &conv_ok );
    if ( !conv_ok )
	{
		retval = defaultValue;
		if ( ok )
		{
			*ok = JFALSE;
		}
	}
	return retval;
}

QString CXmlSettings::getXmlSettings()
{
	flush();
	return m_domDocument.toString( 4 );
}

bool CXmlSettings::clear()
{
	bool bRet = JFALSE;

	m_bReady = m_domDocument.setContent( QString("<root></root>"), false );
	m_bDirty = JTRUE;
	bRet = JTRUE;
	flush();

	return bRet;
}

void CXmlSettings::setXmlSettings( const QString& xml )
{
	if ( !xml.isEmpty() )
	{
		m_bReady = m_domDocument.setContent( xml, false );
		m_bDirty = JTRUE;
		flush();
	}
}

void CFileTransformer::transform(const QString& csvfile,const QString& xmlfile )
{
	open(xmlfile,true,false);

	clear();

	transformAction(csvfile);
	
	m_bDirty = true;

	flush();
}
