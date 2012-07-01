
#ifndef UNARYPROCINTERFACE_H_HEADER_INCLUDED_BF556637
#define UNARYPROCINTERFACE_H_HEADER_INCLUDED_BF556637

#include "escore.h"
#include "iestypedef.h"

namespace escommon {

// ÔËËã½Ó¿Ú
template <class TYPE>
class CUnaryProcInterface
{
public:
	virtual ~CUnaryProcInterface(){};

	virtual void operator()(const TYPE& type) = 0;

protected:
	CUnaryProcInterface(){};

private:
	CUnaryProcInterface(const CUnaryProcInterface& right);

	CUnaryProcInterface& operator=(const CUnaryProcInterface& right);

};

} // namespace 



#endif /* UNARYPROCINTERFACE_H_HEADER_INCLUDED_ */
