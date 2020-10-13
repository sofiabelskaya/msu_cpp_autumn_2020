#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <cstddef>

class allocator
{
	private:
	
		char* base_address; //указатель на начало фиксированного большого блока памяти
		size_t total_size; //размер данного блока
		char* offset; //смещение относительно base_address, на которое мы будем перемещаться, выделяя куски памяти
		bool is_allocated;
public:
	allocator();// конструктор
	~allocator();//деструтор
	void make_allocator(size_t max_size);
	char* alloc(size_t size);
	void reset();

};
#endif
