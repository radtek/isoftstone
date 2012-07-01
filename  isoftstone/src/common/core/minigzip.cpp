/********************************************************************
*
*********************************************************************/

#include "minigzip.h"
#include <stdio.h>
#include <string.h>

#ifndef WIN32 /* unlink already in stdio.h for WIN32 */
#include <unistd.h>
#endif

#include <zlib.h>

#define BUFLEN      16384
#define MAX_NAME_LEN 1024

bool gz_compress(FILE *in, gzFile out);
bool gz_uncompress(gzFile in, FILE *out);
bool file_compress(const char *file, const char *mode, bool autodel);
bool file_uncompress(const char *file, bool autodel);

/* ===========================================================================
 * Compress input to output.
 */

bool gz_compress(FILE *in, gzFile out)
{
    char buf[BUFLEN];
    int len;

    for (;;)
	{
        len = (int)fread(buf, 1, sizeof(buf), in);
        if (ferror(in))
		{
            return false;
        }
        if (len == 0)
		{
			break;
		}

		if (gzwrite(out, buf, (unsigned)len) != len)
		{
			return false;
		}
    }
	return true;
}

/* ===========================================================================
 * Uncompress input to output.
 */
bool gz_uncompress(gzFile in, FILE *out)
{
    char buf[BUFLEN];
    int len;

    for (;;)
	{
        len = gzread(in, buf, sizeof(buf));
        if (len < 0)
		{
			return false;
		}
        if (len == 0) break;

        if ((int)fwrite(buf, 1, (unsigned)len, out) != len)
		{
			return false;
        }
    }
	return true;
}


/* ===========================================================================
 * Compress the given file: create a corresponding .gz file.
 */
bool file_compress(const char *file, const char *mode, bool autodel)
{
	// 生成压缩文件名
    char outfile[MAX_NAME_LEN];
    strcpy(outfile, file);
    strcat(outfile, GZ_SUFFIX);

	// 打开原始文件、压缩文件
	FILE  *in = NULL;
	gzFile out = NULL;
    in = fopen(file, "rb");
	out = gzopen(outfile, mode);

	bool bRet = false;
	if (NULL != in && NULL != out)
	{
		// 压缩文件
		bRet = gz_compress(in, out);
    }

	// 关闭文件
	if (NULL != in)
	{
		bRet = (fclose(in) == 0) && bRet;
	}
	if (NULL != out)
	{
		bRet = (gzclose(out) == Z_OK) && bRet;
	}

	// 生成压缩文件成功，且设置自动删除标志，才能删除原始文件
	if (bRet && autodel)
	{
		unlink(file);
	}

	return bRet;
}


/* ===========================================================================
 * Uncompress the given file.
 */
bool file_uncompress(const char *file, bool autodel)
{
	char buf[MAX_NAME_LEN];
	strcpy(buf, file);
	const char* infile = NULL;
	const char* outfile = NULL;
	uInt len = (uInt)strlen(file);

	// 生成解压缩文件名
    if (len > GZ_SUFFIX_LEN && strcmp(file+len-GZ_SUFFIX_LEN, GZ_SUFFIX) == 0)
	{
        buf[len-GZ_SUFFIX_LEN] = '\0';
		infile = file;
		outfile = buf;
    }
	else
	{
        strcat(buf, GZ_SUFFIX);
		infile = buf;
		outfile = file;
    }

	// 打开压缩文件、解压缩文件
	FILE  *out = NULL;
	gzFile in = NULL;
	in = gzopen(infile, "rb");
	out = fopen(outfile, "wb");
 
	bool bRet = false;
	if (NULL != in && NULL != out)
	{
		// 解压缩文件
		bRet = gz_uncompress(in, out);
	}

	// 关闭文件
	if (NULL != in)
	{
		bRet = (gzclose(in) == Z_OK) && bRet;
	}
	if (NULL != out)
	{
		bRet = (fclose(out) == 0) && bRet;
	}

	// 生成压缩文件成功，且设置自动删除标志，才能删除原始文件
	if (bRet && autodel)
	{
		unlink(file);
	}

	return bRet;
}

bool gzip_file_compress(const char *file, bool autodel)
{
	char outmode[20] = "wb6f";
	// 第 3 个字符
	// 1 to 9 : compression level
	// 第 4 个字符（区分大小写）
	// f : compress with Z_FILTERED（目前看来压缩效果最好）
	// h : compress with Z_HUFFMAN_ONLY
	// R : compress with Z_RLE
	return file_compress(file, outmode, autodel);
}

bool gzip_file_compress(const char *file, const char *mode, bool autodel)
{
	return file_compress(file, mode, autodel);
}

bool gzip_file_uncompress(const char *file, bool autodel)
{
	return file_uncompress(file, autodel);
}
