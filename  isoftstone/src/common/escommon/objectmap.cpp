
#include "objectmap.h"

// 实例化一次，以检测类编写的正确
template class escommon::CObjectMap< int, int, escommon::CNullFree<int>, IceUtil::RWRecMutex >;
typedef escommon::CObjectMap< int, int, escommon::CNullFree<int>, IceUtil::RWRecMutex > a;