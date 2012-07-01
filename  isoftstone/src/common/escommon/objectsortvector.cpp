#include "objectsortvector.h"

// 实例化一次，以检测类编写的正确
template class escommon::CObjectSortVector< Juint32, Juint32, std::less<Juint32>, escommon::CNullFree<Juint32>, IceUtil::RWRecMutex >;
typedef escommon::CObjectSortVector< Juint32, Juint32, std::less<Juint32>, escommon::CNullFree<Juint32>, IceUtil::RWRecMutex > a;
