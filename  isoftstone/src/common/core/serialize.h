
#ifndef _SERIALIZE_H
#define _SERIALIZE_H

#include <qfile.h>
#include <qdatastream.h>
#include <qdatetime.h>
#include <QMutex>
#include <QMutexLocker>
#include <QWriteLocker>
#include <QReadWriteLock>
#include <QReadLocker>
#include <QSharedDataPointer>
#include <QSharedData>
#include <algorithm>
#include "container2stream.h"
#include "escore.h"

enum ESerializeType
{
	ENoneSerialize = 0,
	EXmlSerialize = 1,
	EDataSerialize = 2,
	ETextSerialize = 4,
	ESQLSerialize = 8,
	ESocketSerialize = 16
};

struct SFileHeader
{
public:

	SFileHeader()
	{
		m_version = 0;
		m_createTime = QDateTime::currentDateTime();
		m_fileType = EDataSerialize;
		m_lastRecordMinute = 0;
		memset(m_tmFileOffset,0,sizeof(m_tmFileOffset));
	}

	int				m_version;			// 版本号
	QDateTime		m_createTime;		// 创建时间
	ESerializeType  m_fileType;			// 文件类型
	int				m_lastRecordMinute; // 最后一条消息的分钟
	unsigned long   m_tmFileOffset[60]; // 根据分钟划分的时间段定位
};

class CFileSerialize;

class CSerializeInterface : public QSharedData
{
public:

	virtual ~CSerializeInterface(){};

	virtual void init() = 0;

	virtual bool write(QDataStream& stream ,bool single = false) = 0;

	virtual bool read(QDataStream& stream) = 0;

	int m_currentRecordMinute;

	virtual void setFileSerialize(CFileSerialize* sf)
	{
		m_fileSerialize = sf;
	}

protected:

	CFileSerialize* m_fileSerialize;

	CSerializeInterface(){};

	CSerializeInterface(const CSerializeInterface& right);

	CSerializeInterface& operator=(const CSerializeInterface& right);

};

typedef QSharedDataPointer<CSerializeInterface> CSerializeInterfacePtr;

LIBCORE_EXPORT QDataStream& operator<<(QDataStream& dataStream, const SFileHeader& right);

LIBCORE_EXPORT QDataStream& operator>>(QDataStream& dataStream, SFileHeader& right);

LIBCORE_EXPORT QDataStream& operator>>(QDataStream& dataStream, std::string& right);

class LIBCORE_EXPORT CBaseSerialize
{
public:

	CBaseSerialize()
	{

	}
	virtual ~CBaseSerialize()
	{

	}

	virtual void close() = 0;

	virtual void setHeader(const SFileHeader& header) = 0;

	virtual SFileHeader getHeader() = 0;

public:

	SFileHeader m_fileHeader;

};

class LIBCORE_EXPORT CFileSerialize : public CBaseSerialize
{
public:

	CFileSerialize(const std::string& fileName):m_fileName(fileName)
	{
		m_opened = false;
		m_closed = false;
	}
	virtual ~CFileSerialize()
	{

	}

	virtual void refreshHeader(int minute) = 0;

	virtual void close() = 0;

	virtual void setHeader(const SFileHeader& header)
	{
		m_fileHeader = header;
	}

	virtual SFileHeader getHeader()
	{
		return m_fileHeader;
	}

public:

	std::string m_fileName;

	QFile m_file;

protected:

	QReadWriteLock m_fileMutex;

	bool m_opened;

	bool m_closed;

};

class LIBCORE_EXPORT CDataWriteSerialize : public CFileSerialize
{
public:

	CDataWriteSerialize(const std::string& fileName):CFileSerialize(fileName)
	{

	}
	virtual ~CDataWriteSerialize()
	{
		if (!m_closed)
		{
			close();
		}
		
	}

	virtual void close();

	virtual void refreshHeader(int minute);

	void writeData(CSerializeInterface* dataSerial);

public:

	QDataStream m_file_stream;

	friend class CSerializeInterface;
};

class LIBCORE_EXPORT CDataReadSerialize : public CFileSerialize
{
public:

	CDataReadSerialize(const std::string& fileName):CFileSerialize(fileName)
	{
		open();
	}
	virtual ~CDataReadSerialize()
	{
		close();
	}

	virtual void open();

	virtual void refreshHeader(int minute){};

	virtual void close();

	void readData(CSerializeInterface* dataSerial);

	qint64 getOffset(void);

	bool setOffset(qint64 offset );

	bool next();

	bool next(int size,CSerializeInterface* serialData);

	void removeFile();

public:

	QDataStream m_file_stream;

	friend class CSerializeInterface;
};
#endif