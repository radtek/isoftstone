/********************************************************************
*	��Ȩ���� (C) 2001-2008 ���ɵ��ӹɷ����޹�˾
*	�������а�Ȩ
*	
*	ժҪ��	�ο� zlib/contrib/minizip �޸Ķ��ɵ� zip �ļ���ѹ������ѹ������
*
*			���ļ���Դ���£�
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
*	����Ҫ�������ܵ� zip ѹ���㷨����ֱ��ʹ�� zziplib���Ƽ��� ���� libzip �������⡣
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

// ���ļ�ѹ��
// strZipFileName ѹ�����ļ���ȫ·����
// strPath ָ����ѹ���ļ���Ŀ¼��Ŀ¼������ '/' ����
// strFileNameList ��ѹ���ļ����б�����Ϊ��� strPath ��·���������·��һ������
// nOverWrite ����ѡ�ȡֵ [0, 2]��������ڴ˷�Χ����ȡ 0
//		0 ���ѹ���ļ��Ѿ����ڣ���ʧ��
//		1 �������е�ѹ���ļ�
//		2 ׷�ӵ����е�ѹ���ļ�
// nCompressLevel ѹ������ȡֵ [0�� 9]��������ڴ˷�Χ����ȡ zlib �㷨�ڲ�ȱʡֵ
//		0 ֻ���д洢��û��ѹ��
//		1 ���ѹ��
//		9 ���ѹ��
// strPassword ѹ�����룬ȡֵ QString::null ��ʾ������
QTSOLUTIONS_EXPORT bool zip_files_compress(const QString& strZipFileName,
										   const QString& strPath,
										   const QStringList& strFileNameList,
										   int nOverWrite = 1,
										   int nCompressLevel = 6,
										   const QString& strPassword = QString::null);
// strNameFilter ָ����ѹ���ļ�����������ʹ�� QDir �����ļ������ˣ��������﷨�ɲο� QDir::setNameFilter
// �ڲ�ʹ�� QDir::Files �����ļ������� QDir::Name|QDir::IgnoreCase ����
// bIncludeSubDir �����Ƿ�ѹ����Ŀ¼�µ��ļ�
QTSOLUTIONS_EXPORT bool zip_files_compress(const QString& strZipFileName,
										   const QString& strPath,
										   const QString& strNameFilter,
										   bool bIncludeSubDir = false,
										   int nOverWrite = 1,
										   int nCompressLevel = 6,
										   const QString& strPassword = QString::null);
// �����ļ�ѹ��
// strFileName ��ѹ���ļ���ȫ·����
QTSOLUTIONS_EXPORT bool zip_file_compress(const QString& strFileName,
										  bool autodel,
										  int nOverWrite = 1,
										  int nCompressLevel = 6,
										  const QString& strPassword = QString::null);

// �ļ���ѹ��
// strZipFileName ��ѹ���ļ���ȫ·����
// strPath ָ����ѹ����Ŀ¼��Ŀ¼������ '/' ������ȡֵ QString::null ��ʾ��ǰ����Ŀ¼��ѹ��
// strExtractFileName ����ѹ��ָ�����ļ�����ȡֵ QString::null ��ʾȫ���ļ���ѹ��
// bExtractWithPathname true = ������ѹ���ļ������·����false = ���������·��
// nOverWrite ����ѡ�ȡֵ [0, 2]��������ڴ˷�Χ����ȡ 0
//		0 �����ѹ���ļ��Ѿ����ڣ���ʧ��
//		1 �������еĽ�ѹ���ļ�
//		2 �Թ����еĽ�ѹ���ļ�
// strPassword ѹ�����룬ȡֵ QString::null ��ʾ������
QTSOLUTIONS_EXPORT bool zip_file_uncompress(const QString& strZipFileName,
											const QString& strPath = QString::null,
											const QString& strExtractFileName = QString::null,
											bool bExtractWithPathname = true,
											int nOverWrite = 1,
											const QString& strPassword = QString::null);

// ѹ����ʽ
enum ECompressionMethod
{
	// �洢
	eCompressionMethod_Stored,
	// ��׼ѹ��
	eCompressionMethod_Defl_N,
	// ���ѹ��
	eCompressionMethod_Defl_X,
	// ����ѹ��
	eCompressionMethod_Defl_F,
	// δ֪
	eCompressionMethod_Unknown
};

// ѹ���ļ���Ϣ�ṹ
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

	// �ļ���
	QString m_file_name;
	// �ļ�����
	QDateTime m_file_time;
	// �ļ�ԭ�д�С
	Juint64 m_uncompressed_size;
	// �ļ�ѹ�����С
	Juint64 m_compressed_size;
	// ѹ����ʽ
	ECompressionMethod m_compression_method;
	// ѹ���ʣ��ٷ���ǰ��ֵ
	Juint32 m_ratio;
	// �Ƿ����
	bool m_is_crypt;
	// �ļ�ԭ�е� CRC32 ֵ
	Juint32 m_crc;
};
typedef std::vector<SZipFileInfo> CZipFileInfoVector;

// �г�ѹ���ļ��е��ļ���Ϣ
QTSOLUTIONS_EXPORT bool zip_file_list(const QString& strZipFileName, CZipFileInfoVector& zipFileInfos);

#endif // MINIZIP_H_20081217
