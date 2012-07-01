#ifndef STRINGLIST_H
#define STRINGLIST_H

#include "escore.h"
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>



class LIBCORE_EXPORT HiStringList : public std::list<std::string>
{

public:
	HiStringList() { }
	HiStringList( const HiStringList& right );
	HiStringList( const std::list<std::string>& right );
	HiStringList( const std::string& right );
	HiStringList( const char* right );

	void sort();

	// 由list转为vector
	void toVector(std::vector<std::string>& vec);

	std::string operator[](int index);
	
	static HiStringList split( const char* delimer, const std::string &str );

	static bool split(const std::string&, const std::string&, std::vector<std::string>&);
	// 去掉两端空格
	static std::string trim(const std::string&);
	// 去掉所有空格
	static std::string removeAllspace(const std::string&);

	static std::string toLower(const std::string&);

	static std::string toUpper(const std::string&);
	// 增加分隔符，形成字符串
	std::string join( const std::string &sep ) const;

	// 过滤字符串
	// HiStringList grep( const std::string &str, bool cs = TRUE ) const;
};



#endif // STRINGLIST_H
