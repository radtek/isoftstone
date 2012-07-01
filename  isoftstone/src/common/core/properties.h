
/*********************************************************************************
 *
 * @file	Properties.h
 * @version	1.0
 * @date	2010-01-15
 * @author	刘瑞功
 *
 * @brief	线程基类
 *
 ********************************************************************************/
 // 版权(C) 2009 - 2010 海信网络科技
 // 改动历史
 // 日期		作者	改动内容
 // 2010-01-15	刘瑞功	创建文件
 //===============================================================================

#ifndef __Properties_H_
#define __Properties_H_

#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <stdexcept>
#include <iosfwd>
#include "escore.h"

namespace HiRTDB
{
using std::string;
using std::map;
using std::pair;
using std::vector;
using std::istream;
using std::ostream;
using std::ios;

//限定一行所能拥有的最大字符数
const string::size_type LINE_BUFFER_SIZE = 1024;

class  LIBCORE_EXPORT Properties : public map<string,string>
{
	typedef map<string,string> string_map;
	typedef map<string,string>::iterator iterator;
	typedef pair<bool,string> value_pair;

public:
	Properties(){}
	Properties(const string_map & defaults):m_defaults(defaults)
	{}

	//查找属性key的值.
	//如果属性不存在，返回pair(false,defaultValue);
	//否则返回(true,find(key)->second).
	pair< bool,string> getProperty(std::string key, std::string defaultValue=""); 

	//将所有的属性-值对打印到ostream流中。
	void list(ostream & out);

	//返回所有的属性名。
	const vector<string> propertyNames();

	//添加一个属性-值对。
	//如果此属性已经存在，修改属性为新的值，返回false。
	//也可以使用父类map的insert函数插入。
	bool setProperty(std::string key, std::string value);

	//从一个输入流中读取属性-值对

	//1.空行忽略。

	//2.如果某行的第一个字符为'#' 或'!'，那么此行作为注释行，
	//注意必须是第一个字符！

	//3.每次读一行，设某行的第一个非空格字符为c,
	//如果 c 为 '#' 或'!'，那么此行作为注释行，否则：

	//4.位于一行末尾的'\'作为续行符,如果有多个'\'，则只会将最后
	//一个'\'作为续行符(并去掉)，其余的作为行的内容。

	//5.使用'\'作为转意符，\t, \n, \r, \\, \", \', \ (\空格)
	//分别转换为相应的字符'\t', '\n', '\r', '\\', '\"', 
	//'\'',' ' (空格).

	//6.从c开始搜索，直到碰到第一个'='或':'为止可得到
	//字符串str(不包括'='或':'),去掉str后部的所有空格后
	//作为属性。'='或':'字符后的内容作为属性值。

	//7.如果此行中没有'='或':'字符，那么从c到c其后的第一个
	//空格为止的字符串将被作为属性，此空格后的非零之后的
	//字符串在被去掉前后空格后作为属性值。

	//8.如果一个属性出现了多次，那么以最后一次定义为准

	//例：
	//1)	 Truth = Beauty
	//Truth:Beauty
	//Truth   :Beauty
	//这三种写法都会产生属性-值对("Truth","Beauty").
	//2)  fruits    apple, banana, pear,
	//cantaloupe, watermelon,
	//kiwi, mango
	//产生属性-值对为("fruits"，"apple, banana, pear, cantaloupe, watermelon, kiwi, mango")
	//3)  cheeses
	//产生属性-值对("cheeses","")。
	//3)  >!comment.
	//> !property	
	//如果'>' 标志的是一行的开始，那么第一行作为注释，
	//而第二行则作为属性处理，产生属性-值对("!property","")。
	//##ModelId=436046DA0222
	void load(istream & in);

	//从一个输出流中写入属性-值对

	//1.可以设置一个文件头(string header)，自动在header之前
	//添加'#',从而使header作为注释出现在文件开始，但是必
	//须注意的是，如果header中本身包含格式化符号，那么可
	//能会产生并不希望的副作用。

	//例如:
	//header = "DAFProperties \n 3 properties."
	//输出到文件中后会变为('>'表示一行的开始)。
	//>#DAFProperties 
	//> 3 properties.
	//这样一来" 3 properties."将会变为一个属性-值对
	//("3","properties.")
	//如果希望正确的使用格式化符号，可以通过添加合适的注释
	//符号('#','!')到正确的位置。

	//例如上例可以改为
	//header = "DAFProperties \n# 3 properties."
	//输出到文件中后会变为('>'表示一行的开始。)
	//>#DAFProperties 
	//># 3 properties.

	//2.在header之后将会作为注释打印输出的时间.

	//3.输出时用'='连接每个属性-值对。

	//4.使用'\'作为转意符，字符'\t', '\n', '\r', '\\', '\"'. 分
	//别转换为相应的\t, \n, \r, \\, \", \'。

	//5.属性和属性值中的前导空格、属性中的空格以及属性和
	//属性值中的'#','!','='和':'之前都添加一个'\'字符以
	//保证它们能被正确的读出。

	//例：
	//1)	属性-值对("Truth","Beauty").
	//输出：
	//>Truth=Beauty
	//2) (" fruits" , "  apple, banana, pear")
	//输出：
	//>\ fruits=\ \ apple, banana, pear
	//3) ("comment:" , "=is a mark.")
	//输出：
	//>comment\:=\=\=is a mark.
	//4) ("Jack Smith" , "")
	//输出：
	//>jack\ smith=
	void store(ostream & out, std::string header="");

protected :
	string_map m_defaults;

private:
	//是否拥有续行符
	bool continueLine (std::string line);

	//读取单独的一行，不解析最后的续行符
	std::string readSingleLine(istream & in);

	//解析转意符
	std::string loadConvert (std::string str);

	//添加转意符
	std::string saveConvert(std::string str, bool escapeSpace);

	static string keyValueSeparators;
	static string strictKeyValueSeparators ;
	static string specialSaveChars;
	static string whiteSpaceChars;	
};

class  LIBCORE_EXPORT CEnvVariable : public map<string,string>
{
	typedef map<string,string> string_map;
	typedef map<string,string>::iterator iterator;

public:

	static CEnvVariable* instance(void);

	std::string getScadaHome();

	std::string getEnv(std::string& env);

	std::string getEnv(const char* env);

	static std::string getEnv_s(const char* env);

	std::string getTempPath(const std::string& name);

	std::string getConfigPath(const std::string& name);

	std::string getLogPath(const std::string& name);

	std::vector<std::string> getIPList();

	std::string getComputerName(void);

private:

	CEnvVariable(void);

	~CEnvVariable(void);

	string_map m_envContainer;
	
	static CEnvVariable* sm_Instance;


};

}

#endif //__Properties_H_

