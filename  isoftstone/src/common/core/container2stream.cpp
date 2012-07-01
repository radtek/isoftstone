

#include <iostream>
#include "container2stream.h"
#include "serialize.h"
#include "stringlist.h"
#include "algorithm.h"


using namespace std;

void test()
{
	std::vector<int> data;
	std::vector<int> data2;
	cout << data;
	LCore::printSeq(cout,data);
	ios::open_mode mode = ios::out;

	ifstream fin("abc",ios::binary);
	fin >> data2;
	HiStringList strlist;
	std::string name = "2	341";
	HiStringList::split("/",name);
}

