
#ifndef PREDICATEINTERFACE_H_HEADER_INCLUDED_
#define PREDICATEINTERFACE_H_HEADER_INCLUDED_

#include "escore.h"
#include "iestypedef.h"

namespace escommon {

// еп╤ой╫╫с©з
template <class TYPE>
class CPredicateInterface
{
public:
	virtual ~CPredicateInterface(){};

	virtual bool operator()(const TYPE& type) const = 0;

protected:
	CPredicateInterface(){};

	CPredicateInterface(const CPredicateInterface& right);

	CPredicateInterface& operator=(const CPredicateInterface& right);

};

} // namespace 



#endif /* PREDICATEINTERFACE_H_HEADER_INCLUDED_ */
