
#include "objectmultimap.h"

// ʵ����һ�Σ��Լ�����д����ȷ
template class escommon::CObjectMultiMap< int, int*, escommon::CNullFree<int*>, JTRUE, IceUtil::RWRecMutex >;
