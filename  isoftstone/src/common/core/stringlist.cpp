
#include <algorithm>
#include <iterator>
#include "stringlist.h"
#include "container2stream.h"


using namespace std;


HiStringList::HiStringList( const HiStringList& right )
{
	copy(right.begin(),right.end(),back_inserter(*this));
}
HiStringList::HiStringList( const std::list<string>& right )
{
	copy(right.begin(),right.end(),back_inserter(*this));
}

HiStringList::HiStringList( const std::string& right )
{
	push_back(right); 
}

HiStringList::HiStringList( const char* right )
{
	push_back(std::string(right)); 
}

std::string HiStringList::operator[](int index)
{
	std::list<std::string>::iterator iter = this->begin();
	std::advance(iter,index);
	if (iter != this->end())
	{
		return *iter;
	}
	return "";
}

HiStringList HiStringList::split( const char* delimer, const std::string &str )
{
	HiStringList retv;
	std::string sentence = str;
	char* next_token;
	char *tokenPtr=strtok_s(const_cast<char*>(sentence.c_str()), delimer, &next_token);
	retv.push_back(std::string(tokenPtr));
	while(tokenPtr!=NULL)
	{
		tokenPtr=strtok_s(NULL, delimer, &next_token);
		if (tokenPtr)
		{
			retv.push_back(std::string(tokenPtr));
		}
	}
	return retv;
}

bool HiStringList::split(const std::string& str, const std::string& delimer, std::vector<std::string>& outstrseq)
{
	return true;
}

std::string HiStringList::trim(const std::string& str)
{
	return str;	
}

std::string HiStringList::removeAllspace(const std::string& str)
{
	return str;
}

std::string HiStringList::toLower(const std::string& str)
{
	return str;
}

std::string HiStringList::toUpper(const std::string& str)
{
	return str;
}

std::string HiStringList::join( const std::string &sep ) const
{
	std::string ret;
	int i = 0;
	for (HiStringList::const_iterator iter = begin() ; iter != end() ;iter++)
	{
		i++;
		ret += *iter;
		if (i != (int)size())
		{
			ret += sep;
		}
	}

	return ret;
}

void HiStringList::toVector(std::vector<string>& vec)
{
	copy(begin(),end(),back_inserter(vec));
}
