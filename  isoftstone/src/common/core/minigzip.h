/********************************************************************
*	摘要：	参考 zlib/minigzip.c 修改而成的 gzip 文件
*           的压缩、解压缩方法
*
*********************************************************************/

#ifndef _H_MINIGZIP_H_
#define _H_MINIGZIP_H_

#include "escore.h"

#define GZ_SUFFIX ".gz"
#define GZ_SUFFIX_LEN (sizeof(GZ_SUFFIX)-1)

// 文件压缩
// 使用缺省压缩参数“wb6f”
LIBCORE_EXPORT bool gzip_file_compress(const char *file, bool autodel);
LIBCORE_EXPORT bool gzip_file_compress(const char *file, const char *mode, bool autodel);

// 文件解压缩
LIBCORE_EXPORT bool gzip_file_uncompress(const char *file, bool autodel);

#endif // _H_MINIGZIP_H_
