/********************************************************************
*	ժҪ��	�ο� zlib/minigzip.c �޸Ķ��ɵ� gzip �ļ�
*           ��ѹ������ѹ������
*
*********************************************************************/

#ifndef _H_MINIGZIP_H_
#define _H_MINIGZIP_H_

#include "escore.h"

#define GZ_SUFFIX ".gz"
#define GZ_SUFFIX_LEN (sizeof(GZ_SUFFIX)-1)

// �ļ�ѹ��
// ʹ��ȱʡѹ��������wb6f��
LIBCORE_EXPORT bool gzip_file_compress(const char *file, bool autodel);
LIBCORE_EXPORT bool gzip_file_compress(const char *file, const char *mode, bool autodel);

// �ļ���ѹ��
LIBCORE_EXPORT bool gzip_file_uncompress(const char *file, bool autodel);

#endif // _H_MINIGZIP_H_
