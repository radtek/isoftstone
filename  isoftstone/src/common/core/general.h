#ifndef GENERAL_LCSH_H
#define GENERAL_LCSH_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "math.h"
#include <qstring.h>
#include <qdatetime.h>
#include <qstringlist.h>
#include <qdir.h>
#include "escore.h"
#include "iestypedef.h"

static const double PI=3.1415926;

class LIBCORE_EXPORT CGeneralFunction
{
public:

	static std::string getCurrentThreadID()
	{
		std::string threadID;
		return threadID;
	}

	static int *compute_prefix_function (const char *p)
	{   
		int m = strlen(p);   
		int k = 0;   
		int *x = new int[m];   
		x[0] = 0;      
		for (int q = 2; q <= m; q++)
		{   
			while (k > 0 && p[k] != p[q-1])   
				k = x[k-1];   
			if (p[k] == p[q-1])    
				k++;   
			x[q-1] = k;   
		}   
		return x;   
	}  
	// 返回匹配成功的个数
	static int kmp_matcher(const char *t,const char *p) 
	{   
		int match = 0;
		int n = strlen(t);   
		int m = strlen(p);   
		int *x = compute_prefix_function(p);   
		int q = 0;    
		for (int i = 0; i < n; i++)
		{
			while (q > 0 && p[q] != t[i])   
				q = x[q-1]; 
			if (p[q] == t[i])    
				q++; 
			if (q == m) 
			{ 
				match++;
				q = x[q-1];
			}   
		}   
		return match;
	}  


	static std::vector<std::string> disperse(const std::string& str)
	{
		std::vector<std::string> retv;
		std::string ss = str;
		int len = ss.length();
		for (int i = 0; i < len ;)
		{
			char tmp = ss.at(i);
			std::string word = "";
			if (tmp < 0) // 如果为汉字，双字节
			{
				word = ss.substr(i,2);
				i = i+2;
			}
			else
			{
				word = ss.substr(i,1);
				i++;
			}
			retv.push_back(word);
		}
		return retv;
	}

	static bool checkCharctor(const std::string& str)
	{
		bool ret = true;
		bool tag = false;
		std::vector<std::string> strv = disperse(str);
		for (std::vector<std::string>::iterator iter = strv.begin() ; iter != strv.end() ; iter++)
		{
			tag = false;
			if (!ret)
			{
				break;
			}
			const std::string& ss = *iter;
			char tmp = ss.at(0);
			if (tmp < 0 || // 汉字
				((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z')) // 字符
				||(tmp >= '0' && tmp <= '9')) // 数字
			{
				tag = true;
			}

			ret = ret && tag;
		}
		return ret;
	}

	static double Normal(double z)
	{
		double temp;
		temp=exp((-1)*z*z/2)/sqrt(2*PI);
		return temp;

	}
	/***************************************************************/
	/* 返回标准正态分布的累积函数，该分布的平均值为 0，标准偏差为 1。                           */
	/***************************************************************/
	static double NormSDist(const double z)
	{
		// this guards against overflow
		if(z > 6) return 1;
		if(z < -6) return 0; 

		static const double gamma =  0.231641900,
			a1  =  0.319381530,
			a2  = -0.356563782,
			a3  =  1.781477973,
			a4  = -1.821255978,
			a5  =  1.330274429; 

		double k = 1.0 / (1 + fabs(z) * gamma);
		double n = k * (a1 + k * (a2 + k * (a3 + k * (a4 + k * a5))));
		n = 1 - Normal(z) * n;
		if(z < 0)
			return 1.0 - n; 

		return n;
	} 


	/***************************************************************/
	/* 返回标准正态分布累积函数的逆函数。该分布的平均值为 0，标准偏差为 1。                    */
	/***************************************************************/ 
	static double normsinv(const double p)
	{
		static const double LOW  = 0.02425;
		static const double HIGH = 0.97575;

		/* Coefficients in rational approximations. */
		static const double a[] =
		{
			-3.969683028665376e+01,
			2.209460984245205e+02,
			-2.759285104469687e+02,
			1.383577518672690e+02,
			-3.066479806614716e+01,
			2.506628277459239e+00
		}; 

		static const double b[] =
		{
			-5.447609879822406e+01,
			1.615858368580409e+02,
			-1.556989798598866e+02,
			6.680131188771972e+01,
			-1.328068155288572e+01
		}; 

		static const double c[] =
		{
			-7.784894002430293e-03,
			-3.223964580411365e-01,
			-2.400758277161838e+00,
			-2.549732539343734e+00,
			4.374664141464968e+00,
			2.938163982698783e+00
		}; 

		static const double d[] =
		{
			7.784695709041462e-03,
			3.224671290700398e-01,
			2.445134137142996e+00,
			3.754408661907416e+00
		}; 

		double q, r; 

		errno = 0; 

		if (p < 0 || p > 1)
		{
			errno = EDOM;
			return 0.0;
		}
		else if (p == 0)
		{
			errno = ERANGE;
			return -HUGE_VAL /* minus "infinity" */;
		}
		else if (p == 1)
		{
			errno = ERANGE;
			return HUGE_VAL /* "infinity" */;
		}
		else if (p < LOW)
		{
			/* Rational approximation for lower region */
			q = sqrt(-2*log(p));
			return (((((c[0]*q+c[1])*q+c[2])*q+c[3])*q+c[4])*q+c[5]) /
				((((d[0]*q+d[1])*q+d[2])*q+d[3])*q+1);
		}
		else if (p > HIGH)
		{
			/* Rational approximation for upper region */
			q  = sqrt(-2*log(1-p));
			return -(((((c[0]*q+c[1])*q+c[2])*q+c[3])*q+c[4])*q+c[5]) /
				((((d[0]*q+d[1])*q+d[2])*q+d[3])*q+1);
		}
		else
		{
			/* Rational approximation for central region */
			q = p - 0.5;
			r = q*q;
			return (((((a[0]*r+a[1])*r+a[2])*r+a[3])*r+a[4])*r+a[5])*q /
				(((((b[0]*r+b[1])*r+b[2])*r+b[3])*r+b[4])*r+1);
		}
	} 


	static bool checkIpValid(const QString& strIpAddr, QString& strNormalIpAddr)
	{
		bool bRet = JTRUE;
		strNormalIpAddr = QString::null;

		// 将 IP 地址分割成 4 个字符串
		QStringList strIpList = strIpAddr.split('.');
		if (strIpList.size() == 4)
		{
			for (int i=0; i < strIpList.size(); ++i)
			{
				// 判断数值是否合法
				Jint32 tmpInt = strIpList[i].toInt();
				if (i == 0)
				{
					// 第一字节
					if (tmpInt <= 0 || tmpInt >= 255)
					{
						bRet = JFALSE;
						break;
					}
				}
				else
				{
					// 第二、三、四字节
					if (tmpInt < 0 || tmpInt >= 255)
					{
						bRet = JFALSE;
						break;
					}
				}
				// 生成规则化的IP地址
				if (i > 0)
				{
					strNormalIpAddr += QString(".");
				}
				strNormalIpAddr += QString("%1").arg(tmpInt);
			}
		}
		else
		{
			bRet = JFALSE;
		}
		return bRet;
	}

	// UTC "1970-01-01 00:00:00.000"
	// 本地时区（北京时间） "1970-01-01 08:00:00.000"
	static QString dateTime2fileString(const QDateTime& value, bool hasHour, bool hasMinute, bool hasSecond)
	{
		// 如果 value 非法，则取 "1970-01-01 08:00:00.000"
		Jint32 year = 1970, month = 1, day = 1, hour = 8, minute = 0, second = 0;
		if (value.isValid())
		{
			QDate date = value.date();
			QTime time = value.time();

			year = date.year();
			month = date.month();
			day = date.day();
			hour = time.hour();
			minute = time.minute();
			second = time.second();
		}

		QString fileString = QString("%1%2%3")
			.arg(year)
			.arg((month<10) ? QString("0%1").arg(month) : QString("%1").arg(month))
			.arg((day<10) ? QString("0%1").arg(day) : QString("%1").arg(day));
		if (hasHour)
		{
			fileString += QString("-%1")
				.arg((hour<10) ? QString("0%1").arg(hour) : QString("%1").arg(hour));
		}
		if (hasHour && hasMinute)
		{
			fileString += QString("%1")
				.arg((minute<10) ? QString("0%1").arg(minute) : QString("%1").arg(minute));
		}
		if (hasHour && hasMinute && hasSecond)
		{
			fileString += QString("%1")
				.arg((second<10) ? QString("0%1").arg(second) : QString("%1").arg(second));
		}
		return fileString;
	}

	static QDateTime fileString2dateTime(const QString& strValue)
	{
		// 年
		Jint32 year = strValue.left(4).toInt();
		// 月
		Jint32 month = strValue.mid(4, 2).toInt();
		// 日
		Jint32 day = strValue.mid(6, 2).toInt();
		// 时
		Jint32 hour = strValue.mid(9, 2).toInt();
		// 分
		Jint32 minute = strValue.mid(11, 2).toInt();
		// 秒
		Jint32 second = strValue.mid(13, 2).toInt();

		QDateTime retDateTime(QDate(year, month, day), QTime(hour, minute, second));
		if (!retDateTime.isValid())
		{
			// 如果 strValue 非法，则取 "1970-01-01 08:00:00.000"
			retDateTime = QDateTime(QDate(1970, 1, 1), QTime(8, 0, 0));
		}
		return retDateTime;
	}

	static QDateTime fileName2dateTime(const QString& strFileName,
										const QString& typeName,
										bool hasHour,
										bool hasMinute,
										bool hasSecond)
	{
		// 文件中使用的日期字符串的长度，如：20020113-22 的长度
		Juint32 nTimeStringLength = dateTime2fileString(QDateTime(), hasHour, hasMinute, hasSecond).length();
		// 日期字符串 + 文件类型名 的长度
		int nTimeStringPlusTypeNameLength = nTimeStringLength + typeName.length() + 1;
		if (strFileName.length() >= nTimeStringPlusTypeNameLength)
		{
			// 截取文件名中日期字符串，并转成日期
			return fileString2dateTime(strFileName.right(nTimeStringPlusTypeNameLength).left(nTimeStringLength));
		}
		else
		{
			return QDateTime();
		}
	}

	static QDateTime fileName2dateTime(const QString& strFileName)
	{
		// 取第一个 '-' 位置
		// 取第一个 '.' 位置
		int nRailIndex = strFileName.indexOf('-');
		int nDotIndex = strFileName.indexOf('.');

		if ((nRailIndex >= 0) && (nDotIndex > nRailIndex))
		{
			// 从文件名中截取出日期字符串，并转换成时间
			return fileString2dateTime(strFileName.mid(nRailIndex+1, nDotIndex-nRailIndex-1));
		}
		else
		{
			return QDateTime();
		}
	}

	static QString findLastFile(const QString& filePath,
								 const QString& nameFilter,
								 const QString& typeName,
								 bool bFindLast,
								 bool hasHour,
								 bool hasMinute,
								 bool hasSecond)
	{
		// 得到所有文件
		QStringList allfiles = QDir(filePath).entryList(QStringList() << nameFilter, QDir::Files, QDir::Time|QDir::Reversed);

		// 文件中使用的日期字符串的长度，如：20020113-22 的长度
		Juint32 nTimeStringLength = dateTime2fileString(QDateTime(), hasHour, hasMinute, hasSecond).length();
		// 日期字符串 + 文件类型名 的长度
		Juint32 nTimeStringPlusTypeNameLength = nTimeStringLength + typeName.length() + 1;

		// 最新的文件名，及时间
		QString lastFileName;
		QDateTime lastDateTime;

		QString fileName;
		QDateTime datetime;

		// 文件名格式：xx20020113-22.dat，即文件名末尾必须是日期和文件类型名
		QStringList::const_iterator ite;
		for (ite=allfiles.begin(); ite!=allfiles.end(); ++ite)
		{
			fileName = *ite;
			// 从文件名中截取出日期字符串，并转换成时间
			datetime = fileString2dateTime(fileName.right(nTimeStringPlusTypeNameLength).left(nTimeStringLength));

			if (lastFileName.isEmpty())
			{
				// 找到第一个文件
				lastFileName = fileName;
				lastDateTime = datetime;
			}
			else if ((bFindLast && (lastDateTime < datetime)) ||
				(!bFindLast && (lastDateTime > datetime)))
			{
				// 找到更符合条件的文件
				lastFileName = fileName;
				lastDateTime = datetime;
			}
		}
		return lastFileName;
	}

	static QString findLastFile(const QString& filePath,
								 const QString& nameFilter,
								 bool bFindLast)
	{
		// 得到所有文件
		QStringList allfiles = QDir(filePath).entryList(QStringList() << nameFilter, QDir::Files, QDir::Time|QDir::Reversed);

		// 最新的文件名，及时间
		QString lastFileName;
		QDateTime lastDateTime;

		QString fileName;
		QDateTime datetime;

		// 文件名格式：xx-20020113-22.dat，即第一个 '-'与第一个 '.'之间必须是日期
		QStringList::const_iterator ite;
		for (ite=allfiles.begin(); ite!=allfiles.end(); ++ite)
		{
			fileName = *ite;

			// 取第一个 '-' 位置
			// 取第一个 '.' 位置
			int nRailIndex = fileName.indexOf('-');
			int nDotIndex = fileName.indexOf('.');

			if ((nRailIndex >= 0) && (nDotIndex > nRailIndex))
			{
				// 从文件名中截取出日期字符串，并转换成时间
				datetime = fileString2dateTime(fileName.mid(nRailIndex+1, nDotIndex-nRailIndex-1));

				if (lastFileName.isEmpty())
				{
					// 找到第一个文件
					lastFileName = fileName;
					lastDateTime = datetime;
				}
				else if ((bFindLast && (lastDateTime < datetime)) ||
					(!bFindLast && (lastDateTime > datetime)))
				{
					// 找到更符合条件的文件
					lastFileName = fileName;
					lastDateTime = datetime;
				}
			}
		}
		return lastFileName;
	}

	static QStringList findFilesInTimeSpace(const QDateTime& startDateTime,
											 const QDateTime& endDateTime,
											 const QString& filePath,
											 const QString& nameFilter,
											 const QString& typeName,
											 bool hasHour,
											 bool hasMinute,
											 bool hasSecond)
	{
		QStringList retFilesList;

		if (startDateTime < endDateTime)
		{
			// 得到所有文件
			QStringList allfiles = QDir(filePath).entryList(QStringList() << nameFilter, QDir::Files, QDir::Time|QDir::Reversed);

			// 文件中使用的日期字符串的长度，如：20020113-22 的长度
			Juint32 nTimeStringLength = dateTime2fileString(startDateTime, hasHour, hasMinute, hasSecond).length();
			// 日期字符串 + 文件类型名 的长度
			Juint32 nTimeStringPlusTypeNameLength = nTimeStringLength + typeName.length() + 1;

			QString fileName;
			QDateTime datetime;

			// 文件名格式：xx20020113-22.dat，即文件名末尾必须是日期和文件类型名
			QStringList::const_iterator ite;
			for (ite=allfiles.begin(); ite!=allfiles.end(); ++ite)
			{
				fileName = *ite;
				// 从文件名中截取出日期字符串，并转换成时间
				datetime = fileString2dateTime(fileName.right(nTimeStringPlusTypeNameLength).left(nTimeStringLength));
				if (datetime >= startDateTime && datetime < endDateTime)
				{
					retFilesList << fileName;
				}
			}
		}

		return retFilesList;
	}

	static QStringList findFilesInTimeSpace(const QDateTime& startDateTime,
											 const QDateTime& endDateTime,
											 const QString& filePath,
											 const QString& nameFilter)
	{
		QStringList retFilesList;

		if (startDateTime < endDateTime)
		{
			// 所有文件
			QStringList filesList = QDir(filePath).entryList(QStringList() << nameFilter, QDir::Files, QDir::Time|QDir::Reversed);

			QString fileName;
			QDateTime datetime;

			// 文件名格式：xx-20020113-22.dat，即第一个 '-'与第一个 '.'之间必须是日期
			QStringList::const_iterator ite;
			for (ite = filesList.begin(); ite != filesList.end(); ++ite)
			{
				fileName = *ite;

				// 取第一个 '-' 位置
				// 取第一个 '.' 位置
				int nRailIndex = fileName.indexOf('-');
				int nDotIndex = fileName.indexOf('.');

				if ((nRailIndex >= 0) && (nDotIndex > nRailIndex))
				{
					// 从文件名中截取出日期字符串，并转换成时间
					datetime = fileString2dateTime(fileName.mid(nRailIndex+1, nDotIndex-nRailIndex-1));
					if (datetime >= startDateTime && datetime < endDateTime)
					{
						retFilesList << fileName;
					}
				}
			}
		}

		return retFilesList;
	}

	static QStringList findDateFiles(const QDate& date,
									  const QString& filePath,
									  const QString& nameFilter,
									  const QString& typeName,
									  bool hasHour,
									  bool hasMinute,
									  bool hasSecond)
	{
		QDateTime startDateTime(date);
		QDateTime endDateTime = startDateTime.addDays(1);

		return findFilesInTimeSpace(startDateTime, endDateTime,
			filePath, nameFilter, typeName,
			hasHour, hasMinute, hasSecond);
	}

	static QStringList findDateFiles(const QDate& date, 
									  const QString& filePath, 
									  const QString& nameFilter)
	{
		QDateTime startDateTime( date);
		QDateTime endDateTime = startDateTime.addDays(1);

		return findFilesInTimeSpace(startDateTime, endDateTime, filePath, nameFilter);
	}

	static void delFilesInTimeSpace(const QDateTime& startDateTime,
									 const QDateTime& endDateTime,
									 const QString& filePath,
									 const QString& nameFilter,
									 const QString& typeName,
									 bool hasHour,
									 bool hasMinute,
									 bool hasSecond)
	{
		// 得到 startDateTime、endDateTime 日期之间的文件
		QStringList allfiles = findFilesInTimeSpace(startDateTime, endDateTime,
			filePath, nameFilter, typeName,
			hasHour, hasMinute, hasSecond);

		// 删除文件
		QString fileName;
		QStringList::const_iterator ite;
		for (ite=allfiles.begin(); ite!=allfiles.end(); ++ite)
		{
			fileName = *ite;
			QFile::remove(filePath+fileName);
		}
	}

	static void delFilesInTimeSpace(const QDateTime& startDateTime,
									 const QDateTime& endDateTime,
									 const QString& filePath,
									 const QString& nameFilter)
	{
		// 得到 startDateTime、endDateTime 日期之间的文件
		QStringList allfiles = findFilesInTimeSpace(startDateTime, endDateTime, filePath, nameFilter);

		// 删除文件
		QString fileName;
		QStringList::const_iterator ite;
		for (ite=allfiles.begin(); ite!=allfiles.end(); ++ite)
		{
			fileName = *ite;
			QFile::remove(filePath+fileName);
		}
	}

	static void delExpiredFiles(const QDateTime& expiredTime,
								 const QString& filePath,
								 const QString& nameFilter,
								 const QString& typeName,
								 bool hasHour,
								 bool hasMinute,
								 bool hasSecond)
	{
		delFilesInTimeSpace(QDateTime(), expiredTime,
			filePath, nameFilter, typeName,
			hasHour, hasMinute, hasSecond);
	}

	static void delExpiredFiles(const QDateTime& expiredTime,
								 const QString& filePath,
								 const QString& nameFilter)
	{
		delFilesInTimeSpace(QDateTime(), expiredTime, filePath, nameFilter);
	}

	static bool localStringLess( const QString& left, const QString& right )
	{
		return QString::localeAwareCompare( left, right ) < 0;
	}

	static bool localStringGreater( const QString& left, const QString& right )
	{
		return QString::localeAwareCompare( left, right ) > 0;
	}


	static bool stepProcTime(const QDateTime& currentDateTime, QDateTime& lastProcTime,
								  QDateTime& nextProcTime, Jint32 nStepSeconds, Jint32 nIngoreSeconds)
	{
		bool bRet = JFALSE;
		if (currentDateTime < lastProcTime)
		{
			// 如果机器时间被大范围往前改，重新修正 lastProcTime、nextProcTime
			Jint32 nReverseSeconds = currentDateTime.secsTo(lastProcTime);
			lastProcTime = lastProcTime.addSecs(-(nReverseSeconds/nStepSeconds+1)*nStepSeconds);
			nextProcTime = lastProcTime.addSecs(nStepSeconds);
		}
		else if (currentDateTime >= nextProcTime)
		{
			nextProcTime = nextProcTime.addSecs(nStepSeconds);
			if (nextProcTime <= currentDateTime)
			{
				// 计算被大范围修改的时间
				Jint32 nOverstepSeconds = nextProcTime.secsTo(currentDateTime);
				if (nOverstepSeconds < nIngoreSeconds-nStepSeconds)
				{
					// 当时间被往后改，如果与 nextProcTime 的差值在 nIngoreSeconds 范围之内，则不跳过中间处理
					// 这样保证时间在小范围修改时，数据处理不丢失
				}
				else
				{
					// 如果机器时间被大范围往后改，跳过中间处理点
					nextProcTime = nextProcTime.addSecs((nOverstepSeconds/nStepSeconds+1)*nStepSeconds);
				}
			}
			lastProcTime = nextProcTime.addSecs(-nStepSeconds);

			bRet = JTRUE;
		}
		return bRet;
	}

	static bool stepProcTime(const QDateTime& currentDateTime, QDateTime& lastProcTime,
								 QDateTime& nextProcTime, Jint32 nStepSeconds)
	{
		return stepProcTime(currentDateTime, lastProcTime, nextProcTime, nStepSeconds, nStepSeconds);
	}

};

#endif