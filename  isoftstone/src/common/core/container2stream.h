#ifndef _CONTAINER2STREAM_H_
#define _CONTAINER2STREAM_H_

#include "escore.h"
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <memory>
#include <xmemory>
#include <ostream>
#include <iostream>
#include <fstream>
#include <istream>
#include <stdexcept>
#include <qdatastream.h>

using namespace std;

#define  MaxSize 256


template <class Stream,class T>
inline Stream& read(Stream& fin,T& value)
{
	fin.read((char*)&value,sizeof(value));
	return fin;
}

// 特例化字符串
template <class Stream>
inline Stream& read(Stream& fin,string& value)
{
	int length = 0;
	fin.read((char*)&length,sizeof(length)); 
	char tmp[MaxSize];
	memset(tmp,0,MaxSize);
	fin.read(tmp,length); 
	value = tmp;
	return fin;
}

inline void read(ifstream& fin,char*& value)
{
	string tmp;
	read(fin,tmp);

	strcpy_s(value,MaxSize,tmp.c_str());
}

template <class T>
inline void write(ofstream& fin,const T& value)
{
	fin.write((char*)&value,sizeof(value));
}

// 特例化字符串
template <>
inline void write(ofstream& fout,const string& value)
{
	int length = strlen(value.c_str());
	fout.write((char*)&length,sizeof(length));
	fout.write(value.c_str(),length);
}

inline void write(ofstream& fout,const char* value)
{
	write(fout,string(value));
}

//#if 0

// 要求 TYPE 类型支持序列化
// 文本的序列化
/*
template <class TYPE,class Stream ,template<typename _Ty,typename _Ax = std::allocator<_Ty> > class Container>
Stream& operator<<(Stream& dataStream, const Container<TYPE>& data)
{
	typename Container<TYPE>::size_type nCount = data.size();
	dataStream << nCount;

	typename Container<TYPE>::const_iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter)
	{
		dataStream << *iter;
	}
	return dataStream;
};
*/

// 二进制的反序列化 
template <class TYPE,class Stream ,template<typename _Ty,typename _Ax = std::allocator<_Ty> > class Container>
Stream& operator>>(Stream& dataStream, Container<TYPE>& data)
{
	typename Container<TYPE>::size_type nCount = 0;
	read(dataStream,nCount);

	TYPE value;
	for (Container<TYPE>::size_type i = 0; i < nCount; ++i)
	{
		read(dataStream,value);
		data.push_back(value);
	}
	return dataStream;
};

//#endif

template <class Stream,class TYPE>
Stream& operator<<(Stream& dataStream, const std::vector<TYPE>& data)
{
	size_t nCount = data.size();
	dataStream << nCount;

	typename std::vector<TYPE>::const_iterator ite;
	for (ite=data.begin(); ite!=data.end(); ++ite)
	{
		dataStream << *ite;
	}
	return dataStream;
};

template <class TYPE>
QDataStream& operator<<(QDataStream& dataStream, const std::vector<TYPE>& data)
{
	size_t nCount = data.size();
	dataStream << nCount;

	typename std::vector<TYPE>::const_iterator ite;
	for (ite=data.begin(); ite!=data.end(); ++ite)
	{
		dataStream << *ite;
	}
	return dataStream;
};

template <class TYPE>
QDataStream& operator>>(QDataStream& dataStream, std::vector<TYPE>& data)
{
	size_t nCount = 0;
	dataStream >> nCount;

	TYPE value;
	for (size_t i=0; i<nCount; ++i)
	{
		dataStream >> value;
		data.push_back(value);
	}
	return dataStream;
};

template <class TYPE>
QDataStream& operator<<(QDataStream& dataStream, const std::list<TYPE>& data)
{
	size_t nCount = data.size();
	dataStream << nCount;

	typename std::list<TYPE>::const_iterator ite;
	for (ite=data.begin(); ite!=data.end(); ++ite)
	{
		dataStream << *ite;
	}
	return dataStream;
};

template <class TYPE>
QDataStream& operator>>(QDataStream& dataStream, std::list<TYPE>& data)
{
	size_t nCount = 0;
	dataStream >> nCount;

	TYPE value;
	for (Juint32 i=0; i<nCount; ++i)
	{
		dataStream >> value;
		data.push_back(value);
	}
	return dataStream;
};

template <class TYPE>
QDataStream& operator<<(QDataStream& dataStream, const std::deque<TYPE>& data)
{
	size_t nCount = data.size();
	dataStream << nCount;

	typename std::deque<TYPE>::const_iterator ite;
	for (ite=data.begin(); ite!=data.end(); ++ite)
	{
		dataStream << *ite;
	}
	return dataStream;
};

template <class TYPE>
QDataStream& operator>>(QDataStream& dataStream, std::deque<TYPE>& data)
{
	size_t nCount = 0;
	dataStream >> nCount;

	TYPE value;
	for (Juint32 i=0; i<nCount; ++i)
	{
		dataStream >> value;
		data.push_back(value);
	}
	return dataStream;
};

template <class TYPE,class VALUE>
QDataStream& operator<<(QDataStream& dataStream, const std::map<TYPE,VALUE>& data)
{
	size_t nCount = data.size();
	dataStream << nCount;

	typename std::map<TYPE,VALUE>::const_iterator iter;
	for (iter=data.begin(); iter!=data.end(); ++iter)
	{
		dataStream << iter->frist;
		dataStream << iter->second;
	}
	return dataStream;
};

template <class TYPE,class VALUE>
QDataStream& operator>>(QDataStream& dataStream, std::map<TYPE,VALUE>& data)
{
	size_t nCount = 0;
	dataStream >> nCount;

	TYPE key_f;
	VALUE value_s; 
	for (Juint32 i=0; i<nCount; ++i)
	{
		dataStream >> key_f;
		dataStream >> value_s;
		data.insert(std::make_pair(key_f,value_s));
	}
	return dataStream;
};


#endif	//_CONTAINER2STREAM_H_
