#include "allocator.h"
#include <cstddef>


	allocator::allocator() : base_address(nullptr), total_size(0), offset(nullptr)// инициализируем нулевыми значениями
	{
	
	};
	allocator::~allocator()
	{
		//std::cout << "Destructor called for allocator " << std::endl;
		delete [] base_address;
	};
	void allocator::make_allocator(size_t max_size)
	{
		if (max_size != 0)//если выделяем 0 памяти, то возвращаем нулевые указатели
		{
			base_address = new char[max_size];//выделяем память для большого фиксированного блока
			total_size = max_size; //заносим в струтуру размер большого блока
			offset = base_address; //так как данный блок выделяет только память под большой кусок смещение=0
		}
	};
	char* allocator::alloc(size_t size)
	{
		if (total_size == 0) return nullptr; //если выделили 0 памяти вернуть нулевой указатель
		if (size == 0) return nullptr; //если просят выделить память размера ноль возвращаем нулевой указатель
		if (offset + size > base_address + total_size) return nullptr;// если памяти не хватает возвращаем нулевой указатель
		char* pointer = offset; //возвращаем указатель на начало памяти, затем сдвигаем offset на размер выделенной памяти(в начало следующей аллокации)
		offset += size;
		return pointer;
	};
	void allocator::reset()
	{
		offset = base_address; //снова вернулись в начало
	};


