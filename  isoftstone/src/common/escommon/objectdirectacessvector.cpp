#include "objectdirectacessvector.h"

// 实例化一次，以检测类编写的正确
template class escommon::CObjectDirectAcessVector< Juint32, escommon::CCommonKey2Id<Juint32>, int, escommon::CNullFree<int>, IceUtil::RWRecMutex >;
typedef escommon::CObjectDirectAcessVector< Juint32, escommon::CCommonKey2Id<Juint32>, int, escommon::CNullFree<int>, IceUtil::RWRecMutex > a;
