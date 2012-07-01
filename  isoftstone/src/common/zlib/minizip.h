/********************************************************************
*	版权所有 (C) 2001-2008 积成电子股份有限公司
*	保留所有版权
*	
*	摘要：	参考 zlib/contrib/minizip 修改而成的 zip 文件的压缩、解压缩方法
*
*			各文件来源如下：
*				minizip.h
*				zip.h		<--	zlib/contrib/minizip/zip.h
*				unzip.h		<--	zlib/contrib/minizip/unzip.h
*				ioapi.h		<--	zlib/contrib/minizip/ioapi.h
*				iowin32.h	<--	zlib/contrib/minizip/iowin32.h
*				crypt.h		<--	zlib/contrib/minizip/crypt.h
*				minizip.cpp	<--	zlib/contrib/minizip/minizip.c miniunz.c
*				zip.cpp		<--	zlib/contrib/minizip/zip.c
*				unzip.cpp	<--	zlib/contrib/minizip/unzip.c
*				ioapi.cpp	<--	zlib/contrib/minizip/ioapi.c
*				iowin32.cpp	<--	zlib/contrib/minizip/iowin32.c
*
*	如需要完整功能的 zip 压缩算法，请直接使用 zziplib（推荐） 或者 libzip 第三方库。
*
*********************************************************************/
#ifndef MINIZIP_H_20081217
#define MINIZIP_H_20081217

#ifdef WIN32		// windows platform
#  ifndef QTSOLUTIONS
#    define QTSOLUTIONS_EXPORT __declspec(dllexport)
#  else
#    define QTSOLUTIONS_EXPORT __declspec(dllimport)
#  endif
#  pragma warning( disable : 4251 4275) 
#else	// other platform
#  define QTSOLUTIONS_EXPORT
#endif // WIN32


#include "iestypedef.h"
#include <vector>
#include <qstring.h>
#include <qstringlist.h>
#include <qdatetime.h>

#define ZIP_SUFFIX ".zip"
#define ZIP_SSUFFIX_LEN (sizeof(ZIP_SUFFIX)-1)

// 多文件压缩
// strZipFileName 压缩后文件的全路径名
// strPath 指定被压缩文件的目录，目录必须以 '/' 结束
// strFileNameList 被压缩文件名列表，保存为相对 strPath 的路径名，相对路径一并保存
// nOverWrite 覆盖选项，取值 [0, 2]，如果不在此范围，则取 0
//		0 如果压缩文件已经存在，则失败
//		1 覆盖已有的压缩文件
//		2 追加到已有的压缩文件
// nCompressLevel 压缩级别，取值 [0， 9]，如果不在此范围，则取 zlib 算法内部缺省值
//		0 只进行存储，没有压缩
//		1 最快压缩
//		9 最大压缩
// strPassword 压缩密码，取值 QString::null 表示空密码
QTSOLUTIONS_EXPORT bool zip_files_compress(const QString& strZipFileName,
										   const QString& strPath,
										   const QStringList& strFileNameList,
										   int nOverWrite = 1,
										   int nCompressLevel = 6,
										   const QString& strPassword = QString::null);
// strNameFilter 指定被压缩文件名过滤器，使用 QDir 进行文件名过滤，过滤器语法可参考 QDir::setNameFilter
// 内部使用 QDir::Files 过滤文件、按照 QDir::Name|QDir::IgnoreCase 排序
// bIncludeSubDir 决定是否压缩子目录下的文件
QTSOLUTIONS_EXPORT bool zip_files_compress(const QString& strZipFileName,
										   const QString& strPath,
										   const QString& strNameFilter,
										   bool bIncludeSubDir = false,
										   int nOverWrite = 1,
										   int nCompressLevel = 6,
										   const QString& strPassword = QString::null);
// 单个文件压缩
// strFileName 被压缩文件的全路径名
QTSOLUTIONS_EXPORT bool zip_file_compress(const QString& strFileName,
										  bool autodel,
										  int nOverWrite = 1,
										  int nCompressLevel = 6,
										  const QString& strPassword = QString::null);

// 文件解压缩
// strZipFileName 解压缩文件的全路径名
// strPath 指定解压缩的目录，目录必须以 '/' 结束，取值 QString::null 表示当前工作目录解压缩
// strExtractFileName 仅解压缩指定的文件名，取值 QString::null 表示全部文件解压缩
// bExtractWithPathname true = 创建解压缩文件的相对路径，false = 不创建相对路径
// nOverWrite 覆盖选项，取值 [0, 2]，如果不在此范围，则取 0
//		0 如果解压缩文件已经存在，则失败
//		1 覆盖已有的解压缩文件
//		2 略过已有的解压缩文件
// strPassword 压缩密码，取值 QString::null 表示空密码
QTSOLUTIONS_EXPORT bool zip_file_uncompress(const QString& strZipFileName,
											const QString& strPath = QString::null,
											const QString& strExtractFileName = QString::null,
											bool bExtractWithPathname = true,
											int nOverWrite = 1,
											const QString& strPassword = QString::null);

// 压缩方式
enum ECompressionMethod
{
	// 存储
	eCompressionMethod_Stored,
	// 标准压缩
	eCompressionMethod_Defl_N,
	// 最大压缩
	eCompressionMethod_Defl_X,
	// 快速压缩
	eCompressionMethod_Defl_F,
	// 未知
	eCompressionMethod_Unknown
};

// 压缩文件信息结构
struct SZipFileInfo
{
	SZipFileInfo(void)
	{
		m_uncompressed_size = 0;
		m_compressed_size = 0;
		m_compression_method = eCompressionMethod_Unknown;
		m_ratio = 0;
		m_is_crypt = false;
		m_crc = 0;
	};

	// 文件名
	QString m_file_name;
	// 文件日期
	QDateTime m_file_time;
	// 文件原有大小
	Juint64 m_uncompressed_size;
	// 文件压缩后大小
	Juint64 m_compressed_size;
	// 压缩方式
	ECompressionMethod m_compression_method;
	// 压缩率，百分数前数值
	Juint32 m_ratio;
	// 是否加密
	bool m_is_crypt;
	// 文件原有的 CRC32 值
	Juint32 m_crc;
};
typedef std::vector<SZipFileInfo> CZipFileInfoVector;

// 列出压缩文件中的文件信息
QTSOLUTIONS_EXPORT bool zip_file_list(const QString& strZipFileName, CZipFileInfoVector& zipFileInfos);

#endif // MINIZIP_H_20081217
