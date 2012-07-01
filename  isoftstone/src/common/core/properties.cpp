
#include "properties.h"
#include "macro2.h"

#ifdef WIN32
#include <winsock.h>
#include <wsipx.h>
#include <wsnwlink.h>
#pragma comment(lib,"ws2_32")
#endif

#include <string.h>

namespace HiRTDB
{
string Properties::keyValueSeparators = "=: \t\r\n\f";
string Properties::strictKeyValueSeparators = "=:";
string Properties::specialSaveChars = "=: \t\r\n\f#!";
string Properties::whiteSpaceChars = " \t\r\n\f";	

pair< bool,string> Properties::getProperty(std::string key, std::string defaultValue) 
{
	pair< bool,string> rt(false,"");

	iterator iter = find(key);
	if(iter==end())
	{
		iter = m_defaults.find(key);
		if(iter==m_defaults.end())
		{
			return pair< bool,string>(false,defaultValue);
		}
		return pair< bool,string>(true,iter->second);
	}
	return pair< bool,string>(true,iter->second);
}

void Properties::list(ostream & out) 
{
	for (Properties::iterator iter= begin() ; iter!=end();iter++) 
	{
		string key = iter->first;
		string val = iter->second;
		if (val.size() > 40) 
		{
			val = val.substr(0, 37) + "...";
		}
		out<<key + " = " + val<<std::endl;
	}
}

const vector<string> Properties::propertyNames() 
{
	vector<string> rt;
	for (Properties::iterator iter= begin() ; iter!=end();iter++) 
	{
		rt.push_back(iter->second);
	}
	return rt;
}

//##ModelId=436046DA0218
bool Properties::setProperty(std::string key, std::string value)
{
	pair<iterator,bool> temp =
		insert(string_map::value_type(key, value));

	bool rt = temp.second;
	//此属性已经存在了，修改为新的属性
	if(!rt){			
		temp.first->second = value;
	}
	return rt;
}

//##ModelId=436046DA0222
void Properties::load(istream & in)
{
	//到达文件的末尾了吗？
	string line;
	char firstChar;

	// 如果配置文件使用 Unicode (UTF-8) 作为默认编码，则可能包括 Unicode 签名 (BOM)。 
	// BOM 是位于文本文件开头的 2 到 4 个字节，可将文件标识为 Unicode，还标识后面字节的字节顺序。
	// 由于 UTF-8 没有字节顺序，因此可以选择添加 UTF-8 BOM。对于 UTF-16 和 UTF-32，这是必需的。
	// UTF-8: EF BB BF
	// UTF-16 little-endian: FF FE
	// UTF-16 big-endian: FE FF
	// UTF-32 little-endian: FF FE 00 00
	// UTF-32 big-endian: 00 00 FE FF
	bool bBomDone = false;

	while(!in.eof())
	{
		//读入一行
		line = readSingleLine(in);

		//第一行需要跳过 BOM 签名
		if (!bBomDone)
		{
			//只处理 UTF-8 的 BOM
			//配置文件支持 ANSI、UTF-8 两种编码格式
			if (line.size() > 2 && line.at(0) == char(0xEF) && line.at(1) == char(0xBB) && line.at(2) == char(0xBF))
			{
				// 去掉 BOM 签名
				line = line.substr(3, line.length()-3);
			}
			bBomDone = true;
		}

		//空行跳过
		if(line.empty())
			continue;

		//注释行忽略
		firstChar = line.at(0);
		if((firstChar=='!')||(firstChar=='#'))
			continue;

		//如果有续行符
		while (continueLine(line)) 
		{
			string nextLine = readSingleLine(in);

			string loppedLine = line.substr(0, line.length()-1);
			// Advance beyond whitespace on new line
			size_type startIndex=0;
			for(startIndex=0; startIndex<nextLine.length(); startIndex++)
				if (whiteSpaceChars.find(nextLine.at(startIndex)) == string::npos)
					break;
			nextLine = nextLine.substr(startIndex,nextLine.length());
			line = loppedLine+nextLine;
		}

		// Find start of key
		string::size_type len = line.length();
		string::size_type keyStart;
		for(keyStart=0; keyStart<len; keyStart++) 
		{
			if(whiteSpaceChars.find(line.at(keyStart)) == string::npos)
				break;
		}
		// Blank lines are ignored
		if (keyStart == len)
			continue;

		// Find separation between key and value
		string::size_type separatorIndex;
		for(separatorIndex=keyStart; separatorIndex<len; separatorIndex++) 
		{
			char currentChar = line.at(separatorIndex);
			if (currentChar == '\\')
				separatorIndex++;
			else if(keyValueSeparators.find(currentChar) != string::npos)
				break;
		}

		// Skip over whitespace after key if any
		string::size_type valueStart;
		for (valueStart=separatorIndex; valueStart<len; valueStart++)
			if (whiteSpaceChars.find(line.at(valueStart)) == string::npos)
				break;

		// Skip over one non whitespace key value separators if any
		if (valueStart < len)
			if (strictKeyValueSeparators.find(line.at(valueStart)) != string::npos)
				valueStart++;

		// Skip over white space after other separators if any
		while (valueStart < len) {
			if (whiteSpaceChars.find(line.at(valueStart)) == string::npos)
				break;
			valueStart++;
		}

		string::size_type valueEnd = len-1;
		while(whiteSpaceChars.find(line.at(valueEnd)) != string::npos)
			--valueEnd;

		//去掉分隔符，以及键值后的所有空格
		string::size_type keyEnd = separatorIndex-1;
		while(whiteSpaceChars.find(line.at(keyEnd)) != string::npos)
			--keyEnd;

		// Skip over whitespace after value if any

		string key = line.substr(keyStart, (keyEnd-keyStart+1));
		string value = (separatorIndex < len) ? line.substr(valueStart, (valueEnd-valueStart+1)) : "";

		// Convert then store key and value
		key = loadConvert(key);
		value = loadConvert(value);

		setProperty(key, value);
	}
}

void Properties::store(ostream & out, std::string header)
{
	Hi_UNUSED(out);
	Hi_UNUSED(header);
	//输出文件头
	//out<<"#"<<header<<endl;
	////时间
	//time_t now;
	//tm * local_now;
	//time(&now);
	//local_now = localtime(&now);
	//out<<"#"<<asctime(local_now)<<endl;
	//string key,value;
	//for(iterator iter=begin();iter!=end();iter++)
	//{
	//	key = iter->first;
	//	value = iter->second;

	//	key = saveConvert(key, true);

	//	/* No need to escape embedded and trailing spaces for value, hence
	//	* pass false to flag.
	//	*/
	//	value = saveConvert(value, false);

	//	out<<key<<" = "<<value<<endl;
	//}

}
bool Properties::continueLine (std::string line)
{
	string::size_type slashCount = 0;
	string::size_type index = line.length() - 1;
	while((index >= 0) && (line.at(index--) == '\\'))
		slashCount++;
	return (slashCount % 2 == 1);
}

std::string Properties::readSingleLine(istream & in)
{
	string line;
	std::getline(in, line);
	return line;
}
std::string Properties::loadConvert (std::string str) 
{
	string::iterator iter;
	char aChar;
	for(iter=str.begin();iter!=str.end();iter++)
	{
		aChar = *iter;
		if (aChar == '\\')
		{//转意符
			iter = str.erase(iter);
			if(iter!=str.end())
			{
				aChar = * iter;
				if (aChar == 't') * iter = '\t';
				else if (aChar == 'r') * iter = '\r';
				else if (aChar == 'n') * iter = '\n';
			}
		} 
	}
	return str;
}

std::string Properties::saveConvert(std::string str, bool escapeSpace) 
{
	string::size_type len = str.length();
	string rt;
	for(string::size_type x=0; x<len; x++) {
		char aChar = str.at(x);
		switch(aChar) 
		{
		case ' ':
			if (x == 0 || escapeSpace) 
				rt.append(1,'\\');
			rt.append(1,' ');
			break;
		case '\\':rt.append(1,'\\'); rt.append(1,'\\');
			break;
		case '\t':rt.append(1,'\\'); rt.append(1,'t');
			break;
		case '\n':rt.append(1,'\\'); rt.append(1,'n');
			break;
		case '\r':rt.append(1,'\\'); rt.append(1,'r');
			break;
		case '\f':rt.append(1,'\\'); rt.append(1,'f');
			break;
		default:
			if (specialSaveChars.find(aChar) != string::npos)
				rt.append(1,'\\');
			rt.append(1,aChar);
		}
	}
	return rt;
}

CEnvVariable* CEnvVariable::sm_Instance = NULL;

CEnvVariable::CEnvVariable()
{
}

CEnvVariable::~CEnvVariable()
{
}

CEnvVariable* CEnvVariable::instance(void)
{
	if (NULL == sm_Instance) 
	{
		sm_Instance = new CEnvVariable(); 
	}
	return sm_Instance; 
} 

std::string CEnvVariable::getEnv(std::string& env)
{
	iterator iter = std::map<string,string>::find(env);
	if (iter == std::map<string,string>::end())
	{
		std::string value = getenv(env.c_str());
// 		HiRTDB::CTimeWrapper::replace(value,"\\","/");
// 		m_envContainer.insert(std::make_pair(env,value)) ;
		return value;
	}
	else
	{
		return iter->second;
	}
}

std::string CEnvVariable::getEnv_s(const char* env)
{
	std::string retValue = "";
	char *pValue;
	size_t len;
	errno_t err = _dupenv_s( &pValue, &len, env );
	retValue = pValue;
	free(pValue);
	return retValue;
}

std::string CEnvVariable::getEnv(const char* env)
{
	return getEnv(std::string(env));
}

std::string CEnvVariable::getComputerName(void)
{
	char hostname[256];
	int res = gethostname(hostname, sizeof(hostname));
	if (res == 0)
	{
		return std::string(hostname);
	}
	return "";
}

std::vector<std::string> CEnvVariable::getIPList()
{
	std::vector<std::string> retv;

	char hostname[256];
	int res = gethostname(hostname, sizeof(hostname));
	if (res == 0)
	{
		hostent* pHostent = gethostbyname(hostname);
		{
			if (pHostent)
			{
				hostent& he = *pHostent;
				sockaddr_in sa;
				for (int nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) 
				{
					memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
					// 输出机器的IP地址.
					retv.push_back(inet_ntoa(sa.sin_addr)); 
				}
			}
		}
	}
	return retv;
}

std::string CEnvVariable::getScadaHome()
{
	return getEnv("LSCADA");
}

std::string CEnvVariable::getTempPath(const std::string& name)
{
	return getEnv("LSCADA").append("/temp/").append(name).append("/");
}

std::string CEnvVariable::getConfigPath(const std::string& name)
{
	return getEnv("LSCADA").append("/config/").append(name).append(".config");
}

std::string CEnvVariable::getLogPath(const std::string& name)
{
	return getEnv("LSCADA").append("/log/").append(name).append("/").append(name).append(".log");
}

}//namespace 