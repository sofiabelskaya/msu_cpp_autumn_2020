#include "allocator.h"
#include <cstddef>
#include <iostream>


	allocator::allocator() : base_address(nullptr), total_size(0), offset(nullptr), is_allocated(false)// инициализируем нулевыми значениями
	{
	
	};
	allocator::~allocator()
	{
		//std::cout << "Destructor called for allocator " << std::endl;
		delete [] base_address;
	};
	void allocator::make_allocator(size_t max_size)
	{ 
		if (!is_allocated)
		{
			if (max_size != 0)//если выделяем 0 памяти, то возвращаем нулевые указатели
			{
				is_allocated = true;
				base_address = new char[max_size];//выделяем память для большого фиксированного блока
				total_size = max_size; //заносим в струтуру размер большого блока
				offset = base_address; //так как данный блок выделяет только память под большой кусок смещение=0
			}
		}
		else
		{
			std::cout << "Already allocated" << std::endl;
		}
		
	};
	char* allocator::alloc(size_t size)
		{
		if (is_allocated)// проверяем что alloc был вызван после выделения большой памяти
		{
			if (total_size == 0) //если выделили 0 памяти вернуть нулевой указатель
				return nullptr; 
			if (size == 0) //если просят выделить память размера ноль возвращаем нулевой указатель
				return nullptr; 
			if (offset + size > base_address + total_size) // если памяти не хватает возвращаем нулевой указатель
				return nullptr;
			char* pointer = offset; //возвращаем указатель на начало памяти, затем сдвигаем offset на размер выделенной памяти(в начало следующей аллокации)
			offset += size;
			return pointer;
		}	
		else
		{
			std::cout << "Run make_allocator first, than alloc" << std::endl;
			return nullptr;
		}
	};
	void allocator::reset()
	{
		offset = base_address; //снова вернулись в начало
	};


