
/*********************************************************************************
 *
 * @file	Properties.h
 * @version	1.0
 * @date	2010-01-15
 * @author	����
 *
 * @brief	�̻߳���
 *
 ********************************************************************************/
 // ��Ȩ(C) 2009 - 2010 ��������Ƽ�
 // �Ķ���ʷ
 // ����		����	�Ķ�����
 // 2010-01-15	����	�����ļ�
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

//�޶�һ������ӵ�е�����ַ���
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

	//��������key��ֵ.
	//������Բ����ڣ�����pair(false,defaultValue);
	//���򷵻�(true,find(key)->second).
	pair< bool,string> getProperty(std::string key, std::string defaultValue=""); 

	//�����е�����-ֵ�Դ�ӡ��ostream���С�
	void list(ostream & out);

	//�������е���������
	const vector<string> propertyNames();

	//���һ������-ֵ�ԡ�
	//����������Ѿ����ڣ��޸�����Ϊ�µ�ֵ������false��
	//Ҳ����ʹ�ø���map��insert�������롣
	bool setProperty(std::string key, std::string value);

	//��һ���������ж�ȡ����-ֵ��

	//1.���к��ԡ�

	//2.���ĳ�еĵ�һ���ַ�Ϊ'#' ��'!'����ô������Ϊע���У�
	//ע������ǵ�һ���ַ���

	//3.ÿ�ζ�һ�У���ĳ�еĵ�һ���ǿո��ַ�Ϊc,
	//��� c Ϊ '#' ��'!'����ô������Ϊע���У�����

	//4.λ��һ��ĩβ��'\'��Ϊ���з�,����ж��'\'����ֻ�Ὣ���
	//һ��'\'��Ϊ���з�(��ȥ��)���������Ϊ�е����ݡ�

	//5.ʹ��'\'��Ϊת�����\t, \n, \r, \\, \", \', \ (\�ո�)
	//�ֱ�ת��Ϊ��Ӧ���ַ�'\t', '\n', '\r', '\\', '\"', 
	//'\'',' ' (�ո�).

	//6.��c��ʼ������ֱ��������һ��'='��':'Ϊֹ�ɵõ�
	//�ַ���str(������'='��':'),ȥ��str�󲿵����пո��
	//��Ϊ���ԡ�'='��':'�ַ����������Ϊ����ֵ��

	//7.���������û��'='��':'�ַ�����ô��c��c���ĵ�һ��
	//�ո�Ϊֹ���ַ���������Ϊ���ԣ��˿ո��ķ���֮���
	//�ַ����ڱ�ȥ��ǰ��ո����Ϊ����ֵ��

	//8.���һ�����Գ����˶�Σ���ô�����һ�ζ���Ϊ׼

	//����
	//1)	 Truth = Beauty
	//Truth:Beauty
	//Truth   :Beauty
	//������д�������������-ֵ��("Truth","Beauty").
	//2)  fruits    apple, banana, pear,
	//cantaloupe, watermelon,
	//kiwi, mango
	//��������-ֵ��Ϊ("fruits"��"apple, banana, pear, cantaloupe, watermelon, kiwi, mango")
	//3)  cheeses
	//��������-ֵ��("cheeses","")��
	//3)  >!comment.
	//> !property	
	//���'>' ��־����һ�еĿ�ʼ����ô��һ����Ϊע�ͣ�
	//���ڶ�������Ϊ���Դ�����������-ֵ��("!property","")��
	//##ModelId=436046DA0222
	void load(istream & in);

	//��һ���������д������-ֵ��

	//1.��������һ���ļ�ͷ(string header)���Զ���header֮ǰ
	//���'#',�Ӷ�ʹheader��Ϊע�ͳ������ļ���ʼ�����Ǳ�
	//��ע����ǣ����header�б��������ʽ�����ţ���ô��
	//�ܻ��������ϣ���ĸ����á�

	//����:
	//header = "DAFProperties \n 3 properties."
	//������ļ��к���Ϊ('>'��ʾһ�еĿ�ʼ)��
	//>#DAFProperties 
	//> 3 properties.
	//����һ��" 3 properties."�����Ϊһ������-ֵ��
	//("3","properties.")
	//���ϣ����ȷ��ʹ�ø�ʽ�����ţ�����ͨ����Ӻ��ʵ�ע��
	//����('#','!')����ȷ��λ�á�

	//�����������Ը�Ϊ
	//header = "DAFProperties \n# 3 properties."
	//������ļ��к���Ϊ('>'��ʾһ�еĿ�ʼ��)
	//>#DAFProperties 
	//># 3 properties.

	//2.��header֮�󽫻���Ϊע�ʹ�ӡ�����ʱ��.

	//3.���ʱ��'='����ÿ������-ֵ�ԡ�

	//4.ʹ��'\'��Ϊת������ַ�'\t', '\n', '\r', '\\', '\"'. ��
	//��ת��Ϊ��Ӧ��\t, \n, \r, \\, \", \'��

	//5.���Ժ�����ֵ�е�ǰ���ո������еĿո��Լ����Ժ�
	//����ֵ�е�'#','!','='��':'֮ǰ�����һ��'\'�ַ���
	//��֤�����ܱ���ȷ�Ķ�����

	//����
	//1)	����-ֵ��("Truth","Beauty").
	//�����
	//>Truth=Beauty
	//2) (" fruits" , "  apple, banana, pear")
	//�����
	//>\ fruits=\ \ apple, banana, pear
	//3) ("comment:" , "=is a mark.")
	//�����
	//>comment\:=\=\=is a mark.
	//4) ("Jack Smith" , "")
	//�����
	//>jack\ smith=
	void store(ostream & out, std::string header="");

protected :
	string_map m_defaults;

private:
	//�Ƿ�ӵ�����з�
	bool continueLine (std::string line);

	//��ȡ������һ�У��������������з�
	std::string readSingleLine(istream & in);

	//����ת���
	std::string loadConvert (std::string str);

	//���ת���
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

