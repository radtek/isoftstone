#include "objectdirectacessvector.h"

// ʵ����һ�Σ��Լ�����д����ȷ
template class escommon::CObjectDirectAcessVector< Juint32, escommon::CCommonKey2Id<Juint32>, int, escommon::CNullFree<int>, IceUtil::RWRecMutex >;
typedef escommon::CObjectDirectAcessVector< Juint32, escommon::CCommonKey2Id<Juint32>, int, escommon::CNullFree<int>, IceUtil::RWRecMutex > a;
