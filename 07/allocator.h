#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <cstddef>

template <class T>
class my_allocator {
private:
    T* base_address; //указатель на начало фиксированного большого блока памяти
    size_t total_size; //размер данного блока
    T* offset; //смещение относительно base_address, на которое мы будем перемещаться, выделяя куски памяти
    bool is_allocated;

public:
    my_allocator()
        : base_address(nullptr)
        , total_size(0)
        , offset(nullptr)
        , is_allocated(false) // инициализируем нулевыми значениями
    {
        extern int max_size;
        if (max_size != 0) //если выделяем 0 памяти, то возвращаем нулевые указатели
        {
            is_allocated = true;
            base_address = new T[max_size]; //выделяем память для большого фиксированного блока
            total_size = max_size; //заносим в струтуру размер большого блока
            offset = base_address; //так как данный блок выделяет только память под большой кусок смещение=0
        }
    }
    ~my_allocator()
    {
        //std::cout << "Destructor called for allocator " << std::endl;
        delete[] base_address;
    }
    /*
	void make_allocator(size_t max_size)
	{ 
		if (!is_allocated)
		{
			is_allocated = true;
			if (max_size != 0)//если выделяем 0 памяти, то возвращаем нулевые указатели
			{
				base_address = new T[max_size];//выделяем память для большого фиксированного блока
				total_size = max_size; //заносим в струтуру размер большого блока
				offset = base_address; //так как данный блок выделяет только память под большой кусок смещение=0
			}
		}
		else
		{
			std::cout << "Already allocated" << std::endl;
		}
		
	}*/
    T* allocate(size_t size)
    {
        if (is_allocated) // проверяем что alloc был вызван после выделения большой памяти
        {
            if (total_size == 0) //если выделили 0 памяти вернуть нулевой указатель
                return nullptr;
            if (size == 0) //если просят выделить память размера ноль возвращаем нулевой указатель
                return nullptr;
            if (offset + size > base_address + total_size) // если памяти не хватает возвращаем нулевой указатель
                return nullptr;
            T* pointer = offset; //возвращаем указатель на начало памяти, затем сдвигаем offset на размер выделенной памяти(в начало следующей аллокации)
            offset += size;
            return pointer;
        }
        else {
            std::cout << "Run make_allocator first, than alloc" << std::endl;
            return nullptr;
        }
    }
    void deallocate(T* ptr, const size_t size)
    {
        offset = ptr; // т.к. мы всегда полностью удаляем весь вектор
    }
};
#endif
