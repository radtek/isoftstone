
#include "qualitywrapper.h"

#if defined(MSVCNEWDLL_BUG)
//##ModelId=3ED46AE302C6
void *escommon::CQualityWrapper::operator new(size_t ts)
{
	return ::operator new(ts);
}
//##ModelId=3F554E0401C2
void escommon::CQualityWrapper::operator delete(void *p)
{
	::operator delete(p);
}
#endif // MSVCNEWDLL_BUG

escommon::CQualityWrapper::CQualityWrapper()
{
	clear();
}

void escommon::CQualityWrapper::clear()
{
	opc_quality = 0;
	user_quality = 0;
}

void escommon::clearQuality(LCSH::Quality& left)
{
	left.opc_quality = 0;
	left.user_quality = 0;
}

bool escommon::operator==(const LCSH::Quality& left, const LCSH::Quality& right)
{
	return (left.opc_quality == right.opc_quality &&
		left.user_quality == right.user_quality);
}

QDataStream& escommon::operator<<(QDataStream& dataStream, const LCSH::Quality& right)
{
	dataStream << static_cast<Juint32>(right.opc_quality);
	dataStream << static_cast<Juint32>(right.user_quality);
	return dataStream;
}

QDataStream& escommon::operator>>(QDataStream& dataStream, LCSH::Quality& right)
{
	Juint32 temp;
	dataStream >> temp;
	right.opc_quality = temp;
	dataStream >> temp;
	right.user_quality = temp;
	return dataStream;
}


QString escommon::quality2string(const LCSH::Quality& value)
{
	return QString::number(value.opc_quality) + "\t" + QString::number(value.user_quality);
}


LCSH::Quality escommon::string2quality(const QString& strValue)
{
	LCSH::Quality quality;
	clearQuality(quality);

	Jint32 nPos = strValue.indexOf("\t");
	if (nPos != -1)
	{
		QString strOPCQuality = strValue.left(nPos);
		QString strUserQuality = strValue.right(strValue.length()-nPos-1);
		quality.opc_quality = strOPCQuality.toInt();
		quality.user_quality = strUserQuality.toInt();
	}

	return quality;
}
