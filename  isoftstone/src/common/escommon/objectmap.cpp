
#include "objectmap.h"

// ʵ����һ�Σ��Լ�����д����ȷ
template class escommon::CObjectMap< int, int, escommon::CNullFree<int>, IceUtil::RWRecMutex >;
typedef escommon::CObjectMap< int, int, escommon::CNullFree<int>, IceUtil::RWRecMutex > a;