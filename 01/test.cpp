#include <iostream>
#include "allocator.h"
#include <cstddef>
void test1(allocator allocator1)//тест на то что если выделили 0 памяти для большого куска, то должны получить nullptr при дальнейших попытках ее использовать
{
	allocator1.make_allocator(0);
	if (allocator1.alloc(10) == nullptr) std::cout << "success test1" << std::endl;
	else std::cout << "test1 fail" << std::endl;
}
void test2(allocator allocator1)//если выделен большой кусок памяти, из него аллоцируем память размера 0 и получаем nullptr
{
	allocator1.make_allocator(10);
	if (allocator1.alloc(0) == nullptr) std::cout << "success test2" << std::endl;
	else std::cout << "test2 fail" << std::endl;
}
void test3(allocator allocator1) //если просим больше памяти, чем выделили на большой кусок
{
	allocator1.make_allocator(10);
	if (allocator1.alloc(11) == nullptr) std::cout << "success test3" << std::endl;
	else std::cout << "test3 fail" << std::endl;
}
void test4(allocator allocator1) //большой кусок 10, сначала 5 аллоцируем, потом еще 5 и все должно быть ок
{
	allocator1.make_allocator(10);
	allocator1.alloc(5);
	if (allocator1.alloc(5) != nullptr) std::cout << "success test4" << std::endl;
	else std::cout << "test4 fail" << std::endl;
}
void test5(allocator allocator1) //большой кусок 10, сначала 5 аллоцируем, потом еще 6 и должны получить nullptr
{
	allocator1.make_allocator(10);
	allocator1.alloc(5);
	if (allocator1.alloc(6) == nullptr) std::cout << "success test5" << std::endl;
	else std::cout << "test5 fail" << std::endl;
}
void test6(allocator allocator1) //сначала аллоцируем 5, затем еще 4, указатель при второй аллокации должен быть на расстоянии 5 от первого
{
	allocator1.make_allocator(10);
	char* ch1 = allocator1.alloc(5);
	char* ch2 = allocator1.alloc(4);
	if (ch1 + 5 == ch2) std::cout << "success test6" << std::endl;
	else std::cout << "test6 fail" << std::endl;
}
void test7(allocator allocator1) // проверяем что после функции резет снова можем использовать эту память
{
	allocator1.make_allocator(5);
	char* ch1 = allocator1.alloc(5);
	allocator1.reset();
	char* ch2 = allocator1.alloc(4);
	if (ch1 == ch2 and ch1 != nullptr) std::cout << "success test7" << std::endl;
	else std::cout << "test7 fail" << std::endl;
}
int main()
{
	allocator allocator1;
	test1(allocator1);
	test2(allocator1);
	test3(allocator1);
	test4(allocator1);
	test5(allocator1);
	test6(allocator1);
	test7(allocator1);
	return 0;
}