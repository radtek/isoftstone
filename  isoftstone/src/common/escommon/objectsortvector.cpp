#include "objectsortvector.h"

// ʵ����һ�Σ��Լ�����д����ȷ
template class escommon::CObjectSortVector< Juint32, Juint32, std::less<Juint32>, escommon::CNullFree<Juint32>, IceUtil::RWRecMutex >;
typedef escommon::CObjectSortVector< Juint32, Juint32, std::less<Juint32>, escommon::CNullFree<Juint32>, IceUtil::RWRecMutex > a;
