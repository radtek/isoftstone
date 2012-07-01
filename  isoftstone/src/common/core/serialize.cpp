
#include "serialize.h"
#include "llogger.h"

QDataStream& operator<<(QDataStream& dataStream, const SFileHeader& right)
{
	dataStream << right.m_version;
	dataStream << right.m_createTime;
	dataStream << right.m_fileType;
	dataStream << right.m_lastRecordMinute;
	for (int i = 0; i< sizeof(right.m_tmFileOffset)/sizeof(right.m_tmFileOffset[0]); ++i)
	{
		dataStream << (quint64)right.m_tmFileOffset[i];
	}
	return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, SFileHeader& right)
{
	int fileType;
	dataStream >> right.m_version;
	dataStream >> right.m_createTime;
	dataStream >> fileType;
	dataStream >> right.m_lastRecordMinute;

	quint64 tmp;
	for (int i = 0; i< sizeof(right.m_tmFileOffset)/sizeof(right.m_tmFileOffset[0]); ++i)
	{
		dataStream >> tmp;
		right.m_tmFileOffset[i] = tmp;
	}
	right.m_fileType = static_cast<ESerializeType>(fileType);
	return dataStream;
}

QDataStream& operator>>(QDataStream& dataStream, std::string& right)
{
	QString tmp;
	dataStream >> tmp;
	right = tmp.toStdString();
	return dataStream;
}


// void CDataWriteSerialize::open(const std::string& strtime,bool btime)
// {
// 	IceUtil::WLockT<IceUtil::RWRecMutex> guard( m_fileMutex );
// 	std::string fileName = m_fileName;
// 	if (btime)
// 	{
// 		fileName = strtime;
// 	}
// 	m_file.setName(fileName);
// 	m_file.open( IO_WriteOnly | IO_ReadOnly );
// 	if ( m_file.isOpen() )
// 	{
// 		m_file_stream.setDevice( &m_file );
// 
// 		// 输入文件支持的版本号，如果文件为新建文件内容为空的话就输入版本号信息，否则读出文件里面的头信息
// 		if (m_file.size() == 0)
// 		{
// 			m_file_stream << m_fileHeader;
// 			m_fileHeader.m_tmFileOffset[60] = m_file.at();
// 			m_file.at(0);
// 			m_file_stream << m_fileHeader;
// 
// 			m_file.flush();
// 		}
// 		else
// 		{
// 			QFile::Offset offset = m_file.at();
// 			m_file_stream >> m_fileHeader;
// 			m_file.at(m_file.size());
// 			offset = m_file.at();
// 
// 		}
// 
// 	}
// 	m_opened = true;
// }

void CDataWriteSerialize::close()
{
	if (m_closed)
	{
		return ;
	}
	IceUtil::WLockT<IceUtil::RWRecMutex>  guard( m_fileMutex );
	if ( m_file.isOpen() )
	{
		m_file_stream.unsetDevice();
		m_file.close();
	}
	m_closed = true;
	m_opened = false;
}

void CDataWriteSerialize::refreshHeader(int minute)
{
	quint64 lastoffset = m_file.pos();
	m_file.seek(0);
	if (m_fileHeader.m_tmFileOffset[minute] == 0)
	{
		m_fileHeader.m_tmFileOffset[minute] = static_cast<unsigned long>(lastoffset);
	}

	m_file_stream << m_fileHeader;
	m_file.seek(lastoffset);

}

void CDataWriteSerialize::writeData(CSerializeInterface* dataSerial)
{
	try
	{
		IceUtil::WLockT<IceUtil::RWRecMutex>  guard( m_fileMutex );
		dataSerial->init();
		std::pair<bool,std::string> bTime;
		do
		{
			//bTime = dataSerial->getNextTime();
			if (bTime.first)
			{
				//open(bTime.second,true);
				dataSerial->setFileSerialize(this);
				//序列化
				dataSerial->write( m_file_stream, true );
				m_file.flush();
				close();
			}
			else
			{
				break;
			}

		}while(true);
	}
	catch ( const std::exception& e )
	{
		HI_LOG4CPLUS_DEBUG("事项写入文件时出现异常: " << e.what());
	}
	catch (...)
	{
		HI_LOG4CPLUS_DEBUG("事项写入文件时出现未知异常");
	}
}


void CDataReadSerialize::open()
{
	if (m_opened)
	{
		return;
	}
	IceUtil::RLockT<IceUtil::RWRecMutex>  guard( m_fileMutex );
	m_file.open( QIODevice::ReadOnly );
	if ( m_file.isOpen() )
	{
		m_file_stream.setDevice( &m_file );

		if (m_file.size() > 0)
		{
			m_file_stream >> m_fileHeader;
		}
	}
	m_opened = true;
}

void CDataReadSerialize::close()
{
	if (m_closed)
	{
		return ;
	}
	 
	IceUtil::RLockT<IceUtil::RWRecMutex>  guard( m_fileMutex );
	if ( m_file.isOpen() )
	{
		m_file_stream.unsetDevice();
		m_file.close();
	}
	m_closed = true;
}

void CDataReadSerialize::readData(CSerializeInterface* dataSerial)
{
	try
	{
		//序列化
		dataSerial->read( m_file_stream );
	}
	catch ( const std::exception& e )
	{
		HI_LOG4CPLUS_DEBUG("事项写入文件时出现异常: " << e.what());
	}
	catch (...)
	{
		HI_LOG4CPLUS_DEBUG("事项写入文件时出现未知异常");
	}
}

qint64 CDataReadSerialize::getOffset(void)
{
	qint64 offset = 0;
	if ( m_file.isOpen() )
	{
		offset = m_file.pos();
	}
	return offset;
}

bool CDataReadSerialize::setOffset( qint64 offset )
{
	if ( m_file.isOpen() && offset >= 0 && offset < m_file.size())
	{
		m_file.seek(offset);
		return true;
	}
	return false;
}

bool CDataReadSerialize::next()
{
	if ( m_file.isOpen() )
	{
		return !m_file_stream.atEnd();
	}

	return false;
}

bool CDataReadSerialize::next(int size,CSerializeInterface* serialData)
{
	IceUtil::RLockT<IceUtil::RWRecMutex>  guard( m_fileMutex );
	if ( m_file.isOpen() )
	{
		int i = 0;
		while (next() && i++ < size)
		{
			readData( serialData);
		}
	}
	return true;
}

void CDataReadSerialize::removeFile()
{
	if ( m_file.isOpen() )
	{
		m_file_stream.unsetDevice();
		m_file.close();
	}

	m_file.remove();
}