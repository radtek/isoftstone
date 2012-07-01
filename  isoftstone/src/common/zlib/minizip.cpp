/********************************************************************
*	版权所有 (C) 2001-2008 积成电子股份有限公司
*	保留所有版权
*	
*	日期：	2008-12-17
*	摘要：	参考 zlib/contrib/minizip 修改而成的 zip 文件的压缩、解压缩方法
*
*********************************************************************/

#include "minizip.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#ifdef unix
# include <unistd.h>
# include <utime.h>
# include <sys/types.h>
# include <sys/stat.h>
#else
# include <direct.h>
# include <io.h>
#endif

#include "zip.h"
#include "unzip.h"

#include <qdir.h>

#ifdef WIN32
#define USEWIN32IOAPI
#include "iowin32.h"
#endif

#define WRITEBUFFERSIZE (16384)
#define MAXFILENAME (256)
#define CASESENSITIVITY (0)

#ifdef WIN32
uLong filetime(const char* f,			/* name of file to get info on */
			   tm_zip* /*tmzip*/,		/* return value: access, modific. and creation times */
			   uLong* dt)				/* dostime */
{
	int ret = 0;
	{
		FILETIME ftLocal;
		HANDLE hFind;

		// lgch WIN32_FIND_DATA -> WIN32_FIND_DATAA
		// FindFirstFile -> FindFirstFileA 使用非 UNICODE 版本
		WIN32_FIND_DATAA  ff32;
		hFind = FindFirstFileA(f,&ff32);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			FileTimeToLocalFileTime(&(ff32.ftLastWriteTime),&ftLocal);
			FileTimeToDosDateTime(&ftLocal,((LPWORD)dt)+1,((LPWORD)dt)+0);
			FindClose(hFind);
			ret = 1;
		}
	}
	return ret;
}
#else
#ifdef unix
uLong filetime(const char *f,               /* name of file to get info on */
				tm_zip *tmzip,        /* return value: access, modific. and creation times */
				uLong *dt)            /* dostime */
{
	int ret=0;
	struct stat s;        /* results of stat() */
	struct tm* filedate;
	time_t tm_t=0;

	if (strcmp(f,"-")!=0)
	{
		char name[MAXFILENAME+1];
		int len = strlen(f);
		if (len > MAXFILENAME)
			len = MAXFILENAME;

		strncpy(name, f,MAXFILENAME-1);
		/* strncpy doesnt append the trailing NULL, of the string is too long. */
		name[ MAXFILENAME ] = '\0';

		if (name[len - 1] == '/')
			name[len - 1] = '\0';
		/* not all systems allow stat'ing a file with / appended */
		if (stat(name,&s)==0)
		{
			tm_t = s.st_mtime;
			ret = 1;
		}
	}
	filedate = localtime(&tm_t);

	tmzip->tm_sec  = filedate->tm_sec;
	tmzip->tm_min  = filedate->tm_min;
	tmzip->tm_hour = filedate->tm_hour;
	tmzip->tm_mday = filedate->tm_mday;
	tmzip->tm_mon  = filedate->tm_mon ;
	tmzip->tm_year = filedate->tm_year;

	return ret;
}
#else
uLong filetime(char *f,                /* name of file to get info on */
				tm_zip *tmzip,         /* return value: access, modific. and creation times */
				uLong *dt)             /* dostime */
{
	return 0;
}
#endif
#endif

int check_exist_file(const char* filename)
{
	FILE* ftestexist;
	int ret = 1;
	ftestexist = fopen(filename,"rb");
	if (ftestexist==NULL)
		ret = 0;
	else
		fclose(ftestexist);
	return ret;
}

/* calculate the CRC32 of a file,
because to encrypt a file, we need known the CRC32 of the file before */
int getFileCrc(const char* filenameinzip,void*buf,unsigned long size_buf,unsigned long* result_crc)
{
	unsigned long calculate_crc=0;
	int err=ZIP_OK;
	FILE * fin = fopen(filenameinzip,"rb");
	unsigned long size_read = 0;
	unsigned long total_read = 0;
	if (fin==NULL)
	{
		err = ZIP_ERRNO;
	}

	if (err == ZIP_OK)
		do
		{
			err = ZIP_OK;
			size_read = (int)fread(buf,1,size_buf,fin);
			if (size_read < size_buf)
				if (feof(fin)==0)
				{
					//printf("error in reading %s\n",filenameinzip);
					err = ZIP_ERRNO;
				}

				if (size_read>0)
					calculate_crc = crc32(calculate_crc,(const Bytef *)buf,size_read);
				total_read += size_read;

		} while ((err == ZIP_OK) && (size_read>0));

		if (fin)
			fclose(fin);

		*result_crc=calculate_crc;
		//printf("file %s crc %x\n",filenameinzip,calculate_crc);
		return err;
}

/* change_file_date : change the date/time of a file
filename : the filename of the file where date/time must be modified
dosdate : the new date at the MSDos format (4 bytes)
tmu_date : the SAME new date at the tm_unz format */
void change_file_date(const char* filename, uLong dosdate, tm_unz tmu_date)
{
#ifdef WIN32
	Q_UNUSED(tmu_date);
	HANDLE hFile;
	FILETIME ftm,ftLocal,ftCreate,ftLastAcc,ftLastWrite;

	// lgch CreateFile -> CreateFileA
	hFile = CreateFileA(filename,GENERIC_READ | GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,0,NULL);
	GetFileTime(hFile,&ftCreate,&ftLastAcc,&ftLastWrite);
	DosDateTimeToFileTime((WORD)(dosdate>>16),(WORD)dosdate,&ftLocal);
	LocalFileTimeToFileTime(&ftLocal,&ftm);
	SetFileTime(hFile,&ftm,&ftLastAcc,&ftm);
	CloseHandle(hFile);
#else
#ifdef unix
	struct utimbuf ut;
	struct tm newdate;
	newdate.tm_sec = tmu_date.tm_sec;
	newdate.tm_min=tmu_date.tm_min;
	newdate.tm_hour=tmu_date.tm_hour;
	newdate.tm_mday=tmu_date.tm_mday;
	newdate.tm_mon=tmu_date.tm_mon;
	if (tmu_date.tm_year > 1900)
		newdate.tm_year=tmu_date.tm_year - 1900;
	else
		newdate.tm_year=tmu_date.tm_year ;
	newdate.tm_isdst=-1;

	ut.actime=ut.modtime=mktime(&newdate);
	utime(filename,&ut);
#endif
#endif
}


/* mymkdir and change_file_date are not 100 % portable
As I don't know well Unix, I wait feedback for the unix portion */

int mymkdir(const char* dirname)
{
	int ret=0;
#ifdef WIN32
	ret = mkdir(dirname);
#else
#ifdef unix
	ret = mkdir (dirname,0775);
#endif
#endif
	return ret;
}

int makedir (const char * newdir)
{
	char *buffer ;
	char *p;
	int  len = (int)strlen(newdir);

	if (len <= 0)
		return 0;

	buffer = (char*)malloc(len+1);
	strcpy(buffer,newdir);

	if (buffer[len-1] == '/') {
		buffer[len-1] = '\0';
	}
	if (mymkdir(buffer) == 0)
	{
		free(buffer);
		return 1;
	}

	p = buffer+1;
	while (1)
	{
		char hold;

		while(*p && *p != '\\' && *p != '/')
			p++;
		hold = *p;
		*p = 0;
		if ((mymkdir(buffer) == -1) && (errno == ENOENT))
		{
			//printf("couldn't create directory %s\n",buffer);
			free(buffer);
			return 0;
		}
		if (hold == 0)
			break;
		*p++ = hold;
	}
	free(buffer);
	return 1;
}

int do_list(unzFile uf, CZipFileInfoVector& zipFileInfos)
{
	uLong i;
	unz_global_info gi;
	int err;

	zipFileInfos.clear();
	SZipFileInfo aFileInfo;

	err = unzGetGlobalInfo (uf,&gi);
	//if (err!=UNZ_OK)
	//	printf("error %d with zipfile in unzGetGlobalInfo \n",err);
	//printf(" Length  Method   Size  Ratio   Date    Time   CRC-32     Name\n");
	//printf(" ------  ------   ----  -----   ----    ----   ------     ----\n");
	if (err==UNZ_OK)
	{
		for (i=0;i<gi.number_entry;i++)
		{
			char filename_inzip[MAXFILENAME];
			unz_file_info file_info;
			err = unzGetCurrentFileInfo(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
			if (err!=UNZ_OK)
			{
				//printf("error %d with zipfile in unzGetCurrentFileInfo\n",err);
				break;
			}

			// 获取压缩文件信息
			aFileInfo.m_file_name = filename_inzip;
			aFileInfo.m_file_time.setDate(QDate(file_info.tmu_date.tm_year,
				file_info.tmu_date.tm_mon,
				file_info.tmu_date.tm_mday));
			aFileInfo.m_file_time.setTime(QTime(file_info.tmu_date.tm_hour,
				file_info.tmu_date.tm_min,
				file_info.tmu_date.tm_sec));
			aFileInfo.m_uncompressed_size = file_info.uncompressed_size;
			aFileInfo.m_compressed_size = file_info.compressed_size;
			if (file_info.compression_method==0)
			{
				aFileInfo.m_compression_method = eCompressionMethod_Stored;
			}
			else
			{
				if (file_info.compression_method==Z_DEFLATED)
				{
					uInt iLevel=(uInt)((file_info.flag & 0x6)/2);
					if (iLevel==0)
						aFileInfo.m_compression_method = eCompressionMethod_Defl_N;
					else if (iLevel==1)
						aFileInfo.m_compression_method = eCompressionMethod_Defl_X;
					else if ((iLevel==2) || (iLevel==3))
						aFileInfo.m_compression_method = eCompressionMethod_Defl_F;
				}
				else
				{
					aFileInfo.m_compression_method = eCompressionMethod_Unknown;
				}
			}
			if (file_info.uncompressed_size > 0)
			{
				aFileInfo.m_ratio = (file_info.compressed_size*100) / file_info.uncompressed_size;
			}
			aFileInfo.m_is_crypt = ((file_info.flag & 1) != 0);
			aFileInfo.m_crc = file_info.crc;

			zipFileInfos.push_back(aFileInfo);

			if ((i+1)<gi.number_entry)
			{
				err = unzGoToNextFile(uf);
				if (err!=UNZ_OK)
				{
					//printf("error %d with zipfile in unzGoToNextFile\n",err);
					break;
				}
			}
		}
	}

	return err;
}

int do_extract_currentfile(unzFile uf,
						   int opt_extractdir,
						   const char *dirname,
						   int opt_extract_without_path,
						   int opt_overwrite,
						   const char* password)
{
	char filename_fullpath[MAXFILENAME];
	// filename_fullpath 数据区存放起始位置
	uLong index_filename_inzip = 0;
	// filename_fullpath 数据区有效长度
	uLong size_filename_inzip = sizeof(filename_fullpath);
	if (opt_extractdir == 1)
	{
		// 解压缩到指定目录，则恢复全路径名
		strncpy(filename_fullpath, dirname, sizeof(filename_fullpath)-1);
		filename_fullpath[ sizeof(filename_fullpath) ] = '\0';
		// 计算外部路径占用的长度
		index_filename_inzip = strlen(filename_fullpath);
		size_filename_inzip -= index_filename_inzip;
	}

	char* filename_withoutpath;
	char* p;
	int err=UNZ_OK;
	FILE *fout=NULL;
	void* buf;
	uInt size_buf;

	unz_file_info file_info;
	//uLong ratio=0;
	// 获取压缩文件信息，包括文件名，如果外部传入存放目录，文件名直接追加在目录之后
	err = unzGetCurrentFileInfo(uf, &file_info, filename_fullpath+index_filename_inzip,
		size_filename_inzip, NULL, 0, NULL, 0);

	if (err!=UNZ_OK)
	{
		//printf("error %d with zipfile in unzGetCurrentFileInfo\n",err);
		return err;
	}

	size_buf = WRITEBUFFERSIZE;
	buf = (void*)malloc(size_buf);
	if (buf==NULL)
	{
		//printf("Error allocating memory\n");
		return UNZ_INTERNALERROR;
	}

	p = filename_withoutpath = filename_fullpath;
	while ((*p) != '\0')
	{
		if (((*p)=='/') || ((*p)=='\\'))
			filename_withoutpath = p+1;
		p++;
	}

	if ((*filename_withoutpath)=='\0')
	{
		// filename_fullpath 为目录信息，创建目录
		if (opt_extract_without_path==0)
		{
			//printf("creating directory: %s\n",filename_fullpath);
			mymkdir(filename_fullpath);
		}
	}
	else
	{
		const char* write_filename;
		// 去掉压缩文件中的目录信息，加上外部传入的目录信息，得到的文件名
		char filename_junkpath[MAXFILENAME];

		int skip=0;

		if (opt_extract_without_path==0)
		{
			write_filename = filename_fullpath;
		}
		else
		{
			strncpy(filename_junkpath, dirname, sizeof(filename_junkpath)-1);
			filename_junkpath[ sizeof(filename_junkpath) ] = '\0';
			strncat(filename_junkpath, filename_withoutpath, sizeof(filename_junkpath)-strlen(filename_junkpath)-1);

			write_filename = filename_junkpath;
		}

		err = unzOpenCurrentFilePassword(uf,password);
		//if (err!=UNZ_OK)
		//{
		//	printf("error %d with zipfile in unzOpenCurrentFilePassword\n",err);
		//}

		if ((opt_overwrite!=1) && (err==UNZ_OK))
		{
			// opt_overwrite != 1，需要检测是否存在解压缩的文件
			FILE* ftestexist;
			ftestexist = fopen(write_filename,"rb");
			if (ftestexist!=NULL)
			{
				// 检测到已经存在解压缩文件
				fclose(ftestexist);

				if (opt_overwrite==2)
				{
					// 如果 opt_overwrite == 2，表示略过
					skip = 1;
				}
				else
				{
					// 如果 opt_overwrite == 1，解压缩失败
					err = UNZ_ERRNO;
				}
			}
		}

		if ((skip==0) && (err==UNZ_OK))
		{
			fout=fopen(write_filename,"wb");

			/* some zipfile don't contain directory alone before file */
			if ((fout==NULL) && (opt_extract_without_path==0) &&
				(filename_withoutpath!=(char*)filename_fullpath))
			{
				// 带目录解压缩，不能创建文件时，再创建文件所在路径
				char c=*(filename_withoutpath-1);
				*(filename_withoutpath-1)='\0';
				makedir(filename_fullpath);
				*(filename_withoutpath-1)=c;
				fout=fopen(write_filename,"wb");
			}

			//if (fout==NULL)
			//{
			//	printf("error opening %s\n",write_filename);
			//}
		}

		if (fout!=NULL)
		{
			//printf(" extracting: %s\n",write_filename);

			do
			{
				err = unzReadCurrentFile(uf,buf,size_buf);
				if (err<0)
				{
					//printf("error %d with zipfile in unzReadCurrentFile\n",err);
					break;
				}
				if (err>0)
				{
					if (fwrite(buf,err,1,fout)!=1)
					{
						//printf("error in writing extracted file\n");
						err=UNZ_ERRNO;
						break;
					}
				}
			}
			while (err>0);
			if (fout)
			{
				fclose(fout);
			}

			if (err==0)
			{
				change_file_date(write_filename,file_info.dosDate,
					file_info.tmu_date);
			}
			else
			{
				// 
			}
		}

		if (err==UNZ_OK)
		{
			err = unzCloseCurrentFile (uf);
			//if (err!=UNZ_OK)
			//{
			//	printf("error %d with zipfile in unzCloseCurrentFile\n",err);
			//}
		}
		else
			unzCloseCurrentFile(uf); /* don't lose the error */
	}

	free(buf);
	return err;
}

int do_extract(unzFile uf,
			   int opt_extractdir,
			   const char *dirname,
			   int opt_extract_without_path,
			   int opt_overwrite,
			   const char* password)
{
	uLong i;
	unz_global_info gi;
	int err;
	//FILE* fout=NULL;

	err = unzGetGlobalInfo (uf,&gi);
	//if (err!=UNZ_OK)
	//	printf("error %d with zipfile in unzGetGlobalInfo \n",err);
	if (err == UNZ_OK)
	{
		for (i=0;i<gi.number_entry;i++)
		{
			err = do_extract_currentfile(uf,
				opt_extractdir,
				dirname,
				opt_extract_without_path,
				opt_overwrite,
				password);
			if (err != UNZ_OK)
			{
				break;
			}

			if ((i+1)<gi.number_entry)
			{
				err = unzGoToNextFile(uf);
				if (err!=UNZ_OK)
				{
					//printf("error %d with zipfile in unzGoToNextFile\n",err);
					break;
				}
			}
		}
	}

	return err;
}

int do_extract_onefile(unzFile uf,
					   const char* filename,
					   int opt_extractdir,
					   const char *dirname,
					   int opt_extract_without_path,
					   int opt_overwrite,
					   const char* password)
{
	//int err = UNZ_OK;
	if (unzLocateFile(uf,filename,CASESENSITIVITY)!=UNZ_OK)
	{
		//printf("file %s not found in the zipfile\n",filename);
		return 2;
	}

	return do_extract_currentfile(uf,
		opt_extractdir,
		dirname,
		opt_extract_without_path,
		opt_overwrite,
		password);
}

bool zip_files_compress(const QString& strZipFileName,
						const QString& strPath,
						const QStringList& strFileNameList,
						int nOverWrite,
						int nCompressLevel,
						const QString& strPassword)
{
	int opt_overwrite = (nOverWrite>=0 && nOverWrite<=2) ? nOverWrite : 0;
	int opt_compress_level = (nCompressLevel>=0 && nCompressLevel<=9) ? nCompressLevel : Z_DEFAULT_COMPRESSION;
	char filename_try[MAXFILENAME+16];
	bool zipok = true ;
	int err = ZIP_OK;
	int size_buf = 0;
	void* buf = NULL;

	QByteArray cstrPassword = strPassword.toLocal8Bit();
	const char* password = cstrPassword.isEmpty() ? NULL : (const char *)cstrPassword.data();

	size_buf = WRITEBUFFERSIZE;
	buf = (void*)malloc(size_buf);
	if (buf==NULL)
	{
		//printf("Error allocating memory\n");
		//return ZIP_INTERNALERROR;
		return false;
	}

	int i,len;
	int dot_found=0;

	// 获取压缩文件名
	strncpy(filename_try, strZipFileName.toLocal8Bit(), MAXFILENAME-1);
	/* strncpy doesnt append the trailing NULL, of the string is too long. */
	filename_try[ MAXFILENAME ] = '\0';

	// 检测文件名是否有 .zip 后缀，没有则自动追加
	len=(int)strlen(filename_try);
	for (i=0;i<len;i++)
		if (filename_try[i]=='.')
			dot_found=1;

	if (dot_found==0)
		strcat(filename_try,ZIP_SUFFIX);

	// 检测压缩文件是否已经存在
	if (opt_overwrite==2)
	{
		// 压缩文件不存在，则自动改成重新创建
		if (check_exist_file(filename_try)==0)
			opt_overwrite=1;
	}
	else
	{
		if (opt_overwrite==0)
		{
			if (check_exist_file(filename_try)!=0)
			{
				// 压缩文件存在，覆盖选项为 0，压缩失败
				zipok = false;
			}
		}
	}

	if (zipok)
	{
		zipFile zf;
		int errclose;
# ifdef USEWIN32IOAPI
		zlib_filefunc_def ffunc;
		fill_win32_filefunc(&ffunc);
		zf = zipOpen2(filename_try,(opt_overwrite==2) ? 2 : 0,NULL,&ffunc);
# else
		zf = zipOpen(filename_try,(opt_overwrite==2) ? 2 : 0);
# endif

		if (zf == NULL)
		{
			//printf("error opening %s\n",filename_try);
			err = ZIP_ERRNO;
		}
		else
		{
			//	printf("creating %s\n",filename_try);
			len = strFileNameList.size();
			for (i=0;(i<len) && (err==ZIP_OK);i++)
			{
				FILE * fin;
				int size_read;
				// 生成文件的绝对路径名
				QByteArray cstrAbsFileName = (strPath + strFileNameList[i]).toLocal8Bit();
				const char* absfilenameinzip = cstrAbsFileName;
				// 获取文件的相对路径名
				QByteArray cstrRelativeFileName = strFileNameList[i].toLocal8Bit();
				const char* relativefilenameinzip = cstrRelativeFileName;
				zip_fileinfo zi;
				unsigned long crcFile=0;

				zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
					zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
				zi.dosDate = 0;
				zi.internal_fa = 0;
				zi.external_fa = 0;
				filetime(absfilenameinzip,&zi.tmz_date,&zi.dosDate);

				/*
				err = zipOpenNewFileInZip(zf,absfilenameinzip,&zi,
				NULL,0,NULL,0,NULL / * comment * /,
				(opt_compress_level != 0) ? Z_DEFLATED : 0,
				opt_compress_level);
				*/
				if ((password != NULL) && (err==ZIP_OK))
					err = getFileCrc(absfilenameinzip,buf,size_buf,&crcFile);

				// 使用相对路径名进行记录
				err = zipOpenNewFileInZip3(zf,relativefilenameinzip,&zi,
					NULL,0,NULL,0,NULL /* comment*/,
					(opt_compress_level != 0) ? Z_DEFLATED : 0,
					opt_compress_level,0,
					/* -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, */
					-MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
					password,crcFile);

				if (err != ZIP_OK)
				{
					//printf("error in opening %s in zipfile\n",absfilenameinzip);
				}
				else
				{
					fin = fopen(absfilenameinzip,"rb");
					if (fin==NULL)
					{
						err=ZIP_ERRNO;
						//printf("error in opening %s for reading\n",absfilenameinzip);
					}
				}

				if (err == ZIP_OK)
				{
					do
					{
						err = ZIP_OK;
						size_read = (int)fread(buf,1,size_buf,fin);
						if (size_read < size_buf)
						{
							if (feof(fin)==0)
							{
								//printf("error in reading %s\n",absfilenameinzip);
								err = ZIP_ERRNO;
							}
						}

						if (size_read>0)
						{
							err = zipWriteInFileInZip (zf,buf,size_read);
							//if (err<0)
							//{
							//	printf("error in writing %s in the zipfile\n",
							//		absfilenameinzip);
							//}

						}
					} while ((err == ZIP_OK) && (size_read>0));

					if (fin)
						fclose(fin);

					if (err<0)
						err=ZIP_ERRNO;
					else
					{
						err = zipCloseFileInZip(zf);
						//if (err!=ZIP_OK)
						//	printf("error in closing %s in the zipfile\n",
						//	absfilenameinzip);
					}
				}
			}
			errclose = zipClose(zf,NULL);
			//if (errclose != ZIP_OK)
			//	printf("error in closing %s\n",filename_try);
		}
	}

	free(buf);
	return (err == ZIP_OK);
}

bool zip_sub_dir(const QString& strZipFileName,
				 const QString& strPath,
				 const QString& strNameFilter,
				 int nCompressLevel,
				 const QString& strPassword,
				 QDir& absDir,
				 const QString& strRelativePath)
{
	bool bRet = true;

	// 获取当前目录的子目录
	QStringList subDirs =absDir.entryList(QDir::Dirs, QDir::Name|QDir::IgnoreCase);

	// 遍历所有子目录
	QStringList::const_iterator iteDir;
	for (iteDir=subDirs.begin(); iteDir!=subDirs.end(); ++iteDir)
	{
		QString strSubPath = *iteDir;
		if (strSubPath == "." || strSubPath == "..")
		{
			continue;
		}

		// 步进到子目录
		absDir.cd(strSubPath);

		// 获取步进后目录的文件列表
		QStringList allfiles = absDir.entryList(QStringList() <<strNameFilter, QDir::Files, QDir::Name|QDir::IgnoreCase);

		// 获取相对 strPath 目录
		QString strSubRelativePath = strRelativePath;
		strSubRelativePath += strSubPath;
		strSubRelativePath += "/";
		QStringList::iterator iteFile;
		for (iteFile=allfiles.begin(); iteFile!=allfiles.end(); ++iteFile)
		{
			// 文件名改为相对 strPath 的文件名
			*iteFile = strSubRelativePath + *iteFile;
		}

		// 使用追加方式进行子目录文件压缩
		bRet = zip_files_compress(strZipFileName, strPath, allfiles, 2, nCompressLevel, strPassword);
		if (!bRet)
		{
			break;
		}

		// 进行子目录文件压缩
		bRet = zip_sub_dir(strZipFileName, strPath, strNameFilter, nCompressLevel, strPassword, absDir, strSubRelativePath);
		if (!bRet)
		{
			break;
		}

		// 退回到父目录
		absDir.cdUp();
	}
	return bRet;
}

bool zip_files_compress(const QString& strZipFileName,
						const QString& strPath,
						const QString& strNameFilter,
						bool bIncludeSubDir,
						int nOverWrite,
						int nCompressLevel,
						const QString& strPassword)
{
	QDir absDir(strPath);

	// 获得文件列表，不包含目录信息
	QStringList allfiles = absDir.entryList(QStringList() <<strNameFilter, QDir::Files, QDir::Name|QDir::IgnoreCase);
	bool bRet = zip_files_compress(strZipFileName, strPath, allfiles, nOverWrite, nCompressLevel, strPassword);

	if (bRet && bIncludeSubDir)
	{
		// 进行子目录文件压缩
		zip_sub_dir(strZipFileName, strPath, strNameFilter, nCompressLevel, strPassword, absDir, QString::null);
	}
	return bRet;
}

bool zip_file_compress(const QString& strFileName,
					   bool autodel,
					   int nOverWrite,
					   int nCompressLevel,
					   const QString& strPassword)
{
	QString strZipFileName = strFileName;
	strZipFileName.replace(QChar('\\'), QChar('/'));	// 将'\'替换为'/'

	QString strPath;
	QString strNoPathFileName;

	// 从文件名中区分出路径和不带路径的文件名
	int index = strZipFileName.indexOf('/');
	if (index == -1)
	{
		// 不包含路径信息，路径取当前路径
		strNoPathFileName = strZipFileName;
	}
	else
	{
		strPath = strZipFileName.left(index+1);
		strNoPathFileName = strZipFileName.right(strZipFileName.length()-index-1);
	}

	// 压缩目标文件
	strZipFileName += ZIP_SUFFIX;
	QStringList allfiles = (QStringList() << strNoPathFileName);
	bool bRet = zip_files_compress(strZipFileName, strPath, allfiles, nOverWrite, nCompressLevel, strPassword);

	// 生成压缩文件成功，且设置自动删除标志，才能删除原始文件
	if (bRet && autodel)
	{
		QFile::remove(strFileName);
	}

	return bRet;
}

bool zip_file_uncompress(const QString& strZipFileName,
						 const QString& strPath,
						 const QString& strExtractFileName,
						 bool bExtractWithPathname,
						 int nOverWrite,
						 const QString& strPassword)
{
	QByteArray cstrZipFileName = strZipFileName.toLocal8Bit();
	const char *zipfilename = cstrZipFileName.isEmpty() ? NULL : (const char *)cstrZipFileName;
	QByteArray cstrPath = strPath.toLocal8Bit();
	const char *dirname = cstrPath.isEmpty() ? NULL : (const char *)cstrPath;
	QByteArray cstrExtractFileName = strExtractFileName.toLocal8Bit();
	const char *filename_to_extract = cstrExtractFileName.isEmpty() ? NULL : (const char *)cstrExtractFileName;
	QByteArray cstrPassword = strPassword.toLocal8Bit();
	const char *password = cstrPassword.isEmpty() ? NULL : (const char *)cstrPassword;

	char filename_try[MAXFILENAME+16] = "";
	int opt_do_extract_withoutpath = bExtractWithPathname ? 0 : 1;
	int opt_overwrite = (nOverWrite>=0 && nOverWrite<=2) ? nOverWrite : 0;
	int opt_extractdir = cstrPath.isEmpty() ? 0 : 1;
	unzFile uf = NULL;

	bool bRet = false;
	if (zipfilename != NULL)
	{
		// 创建解压缩目录
		if (opt_extractdir && makedir(dirname) == 0) 
		{
			//printf("Error changing into %s, aborting\n", dirname);
			//exit(-1);
		}
		else
		{
# ifdef USEWIN32IOAPI
			zlib_filefunc_def ffunc;
# endif

			strncpy(filename_try, zipfilename, MAXFILENAME-1);
			/* strncpy doesnt append the trailing NULL, of the string is too long. */
			filename_try[ MAXFILENAME ] = '\0';

# ifdef USEWIN32IOAPI
			fill_win32_filefunc(&ffunc);
			uf = unzOpen2(zipfilename,&ffunc);
# else
			uf = unzOpen(zipfilename);
# endif
			if (uf==NULL)
			{
				strcat(filename_try,ZIP_SUFFIX);
# ifdef USEWIN32IOAPI
				uf = unzOpen2(filename_try,&ffunc);
# else
				uf = unzOpen(filename_try);
# endif
			}

			if (uf==NULL)
			{
				//printf("Cannot open %s or %s.zip\n",zipfilename,zipfilename);
				//return 1;
			}
			else
			{
				//printf("%s opened\n",filename_try);
				if (filename_to_extract == NULL)
				{
					// 全部文件解压缩
					bRet = (do_extract(uf, opt_extractdir, dirname,
						opt_do_extract_withoutpath, opt_overwrite, password) == 0);
				}
				else
				{
					// 指定文件解压缩
					bRet = (do_extract_onefile(uf, filename_to_extract, opt_extractdir, dirname,
						opt_do_extract_withoutpath, opt_overwrite, password) == 0);
				}
				int errclose;
				errclose = unzClose(uf);
				//if (errclose != UNZ_OK)
				//	printf("error in closing %s\n",filename_try);
			}
		}
	}
	return bRet;
}

bool zip_file_list(const QString& strZipFileName, CZipFileInfoVector& zipFileInfos)
{
	QByteArray cstrZipFileName = strZipFileName.toLocal8Bit();
	const char *zipfilename = cstrZipFileName.isEmpty() ? NULL : (const char *)cstrZipFileName;

	char filename_try[MAXFILENAME+16] = "";
	unzFile uf=NULL;

	bool bRet = false;
	if (zipfilename!=NULL)
	{

# ifdef USEWIN32IOAPI
		zlib_filefunc_def ffunc;
# endif

		strncpy(filename_try, zipfilename,MAXFILENAME-1);
		/* strncpy doesnt append the trailing NULL, of the string is too long. */
		filename_try[ MAXFILENAME ] = '\0';

# ifdef USEWIN32IOAPI
		fill_win32_filefunc(&ffunc);
		uf = unzOpen2(zipfilename,&ffunc);
# else
		uf = unzOpen(zipfilename);
# endif
		if (uf==NULL)
		{
			strcat(filename_try,ZIP_SUFFIX);
# ifdef USEWIN32IOAPI
			uf = unzOpen2(filename_try,&ffunc);
# else
			uf = unzOpen(filename_try);
# endif
		}

		if (uf==NULL)
		{
			//printf("Cannot open %s or %s.zip\n",zipfilename,zipfilename);
			//return 1;
		}
		else
		{
			//printf("%s opened\n",filename_try);
			bRet = (do_list(uf, zipFileInfos) == 0);

			int errclose;
			errclose = unzClose(uf);
			//if (errclose != UNZ_OK)
			//	printf("error in closing %s\n",filename_try);
		}
	}
	return bRet;
}
