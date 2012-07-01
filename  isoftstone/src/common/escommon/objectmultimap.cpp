
#include "objectmultimap.h"

// 实例化一次，以检测类编写的正确
template class escommon::CObjectMultiMap< int, int*, escommon::CNullFree<int*>, JTRUE, IceUtil::RWRecMutex >;
