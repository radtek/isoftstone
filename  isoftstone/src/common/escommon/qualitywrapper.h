

#ifndef QUALITYWRAPPER_H_HEADER_INCLUDED_C12B9792
#define QUALITYWRAPPER_H_HEADER_INCLUDED_C12B9792

#include "escore.h"
#include "iestypedef.h"
#include <qdatastream.h>
#include <qstring.h>

namespace LCSH
{
	struct Quality
	{
		int opc_quality;
		int user_quality;
	};
}

namespace escommon 
{

class LIBESCOMMON_EXPORT CQualityWrapper : public LCSH::Quality
{
public:
	CQualityWrapper();

	void clear();

#if defined(MSVCNEWDLL_BUG)
	void *operator new(size_t ts);
	void operator delete(void* p);
	void *operator new(size_t, void* pMem){return pMem;};
	void operator delete(void*, void*){};
#endif // MSVCNEWDLL_BUG
};

LIBESCOMMON_EXPORT void clearQuality(LCSH::Quality& left);

LIBESCOMMON_EXPORT bool operator==(const LCSH::Quality& left, const LCSH::Quality& right);
inline bool operator!=(const LCSH::Quality& left, const LCSH::Quality& right)
{
	return !(left == right);
};

LIBESCOMMON_EXPORT QDataStream& operator<<(QDataStream& dataStream, const LCSH::Quality& right);
LIBESCOMMON_EXPORT QDataStream& operator>>(QDataStream& dataStream, LCSH::Quality& right);

LIBESCOMMON_EXPORT QString quality2string(const LCSH::Quality& value);

LIBESCOMMON_EXPORT LCSH::Quality string2quality(const QString& strValue);

} // namespace escommon



#endif /* QUALITYWRAPPER_H_HEADER_INCLUDED_C12B9792 */
