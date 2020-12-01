#include <iostream>
#include "vector.hpp"
#include <iostream>
#include <string>
#include <cassert>

struct MyStruct
{
	int a;
	bool b;
	MyStruct(int a, bool b) :a(a), b(b)
	{

	}
};


int main()
{
	Vector<int> v(2, 1);
	if (v[0] == 1 && v.size() == 2) {
		cout << "test1 ok" << endl;
	}
	else {
		cout << "test1 fail" << endl;
	}
	v.reserve(8); 
	if (v.size()==2 && v.capacity() == 8) {
		cout << "test2 ok" << endl;
	}
	else {
		cout << "test2 fail" << endl;
	}
	v.resize(10, 2);
	if (v.size() == 10 && v[9] == 2) {
		cout << "test3 ok" << endl;
	}
	else {
		cout << "test3 fail" << endl;
	}
	if (!v.empty()) {
		cout << "test4 ok" << endl;
	}
	else {
		cout << "test4 fail" << endl;
	}
	v.clear();
	if (v.empty()) {
		cout << "test5 ok" << endl;
	}
	else {
		cout << "test5 fail" << endl;
	}
	v.emplace_back(33);
	if (v[0]==33) {
		cout << "test6 ok" << endl;
	}
	else {
		cout << "test6 fail" << endl;
	}
	int a = 1;
	int cap = v.capacity();
	while (a < 10)
	{
		v.push_back(a);
		a++;
	}
	if (cap * 2 == v.capacity()) {
		cout << "test7 ok" << endl;
	}
	else {
		cout << "test7 fail" << endl;
	}
	int i = 0;
	string str = "test8 ok";
	for (MyIterator<int> it = v.begin(); it <v.end() ; ++it)
	{
		if (*it != v[i])
		{
			str = "test8 fail";
			break;
		}
		i++;
	}
	cout << str<<endl;
	Vector<MyStruct> vstr;
	vstr.emplace_back(1, true);
	if (vstr[0].a == 1 and vstr[0].b) {
		cout << "test9 ok" << endl;
	}
	else {
		cout << "test9 fail" << endl;
	}
}
