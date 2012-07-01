#ifndef ALGORITHM_LCSH_H
#define ALGORITHM_LCSH_H

#include <map>
#include <vector>

namespace LCore
{
	template<class TYPE,class Stream,template<typename _Ty,typename _Ax = std::allocator<_Ty> > class Container>
	static void printSeq(Stream& out,const Container<TYPE>& container)
	{
		typename typedef Container<TYPE>::const_iterator Const_Iterator;
		for (Const_Iterator iter = container.begin() ; iter != container.end() ; iter++)
		{
			out << *iter;
			out << "\n";
		}
	}
}

#endif