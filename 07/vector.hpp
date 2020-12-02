#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include "allocator.h"
using namespace std;

template <class T>
class MyIterator : public std::iterator<std::random_access_iterator_tag, T> {
    template <class T_, class Allocator>
    friend class Vector;

private:
    T* ptr_;

public:
    MyIterator(T* ptr)
        : ptr_(ptr)
    {
    }
    MyIterator(const MyIterator& iter)
        : ptr_(iter.ptr_)
    {
    }
    bool operator!=(const MyIterator& iter) const
    {
        return ptr_ != iter.ptr_;
    }
    bool operator==(const MyIterator& iter) const
    {
        return ptr_ == iter.ptr_;
    }
    bool operator>(const MyIterator& iter) const
    {
        return ptr_ > iter.ptr_;
    }
    bool operator<(const MyIterator& iter) const
    {
        return ptr_ < iter.ptr_;
    }
    bool operator<=(const MyIterator& iter) const
    {
        return ptr_ <= iter.ptr_;
    }
    bool operator>=(const MyIterator& iter) const
    {
        return ptr_ >= iter.ptr_;
    }
    typename MyIterator::reference operator*() const
    {
        return *ptr_;
    }
    MyIterator& operator++()
    {
        ++ptr_;
        return *this;
    }
    MyIterator& operator--()
    {
        --ptr_;
        return *this;
    }
    MyIterator& operator+=(const int n)
    {
        ptr_ += n;
        return *this;
    }
    friend T* operator+(const MyIterator& iter, const int n)
    {
        return iter.ptr_ + n;
    }
    friend T* operator-(const MyIterator& iter, const int n)
    {
        return iter.ptr_ - n;
    }
    MyIterator& operator-=(const int n)
    {
        ptr_ -= n;
        return *this;
    }
    T& operator[](const size_t i)
    {
        return ptr_[i];
    }
    friend int operator-(const MyIterator& iter, const MyIterator& iter2)
    {
        return iter.ptr_ - iter2.ptr_;
    }
};

template <class T, class Allocator = std::allocator<T> >
class Vector {
public:
    using iterator = MyIterator<T>;
    using const_iterator = MyIterator<const T>;

    Vector()
    {
        capacity_ = 1;
        storage = alloc.allocate(capacity_);
        size_ = 0;
    }
    Vector(size_t size)
    {
        this->size_ = size;
        capacity_ = 2 * size;
        storage = alloc.allocate(capacity_);
    }
    Vector(size_t size, const T& val)
    {
        this->size_ = size;
        capacity_ = 2 * size;
        storage = alloc.allocate(capacity_);
        for (size_t i = 0; i < size; i++) {
            storage[i] = val;
        }
    }
    Vector(const Vector<T>& v)
    {
        this->size_ = v.size_;
        this->capacity_ = v.capacity_;
        this->storage = alloc.allocate(capacity_);
        for (size_t i = 0; i < size_; i++) {
            this->storage[i] = v.storage[i];
        }
    }
    ~Vector()
    {
        alloc.deallocate(this->storage, capacity_);
    }

    T& operator[](size_t i)
    {
		if(i >= size_)
		{
			throw std::out_of_range("index is out of range");
		}
        return this->storage[i];
    }
    const T& operator[](const size_t i) const
    {
		if(i >= size_)
		{
			throw std::out_of_range("index is out of range");
		}
        return this->storage[i];
    }
    void pop_back()
    {
        size_--;
    }
    void push_back(const T& val)
    {
        if (size_ + 1 >= capacity_) {
            reserve((size_ + 1) * 2);
        }
        storage[size_] = val;
        size_++;
    }
    void push_back(T&& val)
    {
        if (size_ + 1 >= capacity_) {
            reserve((size_ + 1) * 2);
        }
        storage[size_] = std::move(val);
        size_++;
    }
    template <class... Args>
    T& emplace_back(Args&&... args)
    {
        if (size_ + 1 >= capacity_) {
            reserve((size_ + 1) * 2);
        }
        storage[size_] = T(std::forward<Args>(args)...);
        size_++;
        return storage[size_];
    }
    void clear()
    {
        size_ = 0;
    }

    const size_t size() const
    {
        return this->size_;
    }
    const size_t capacity() const
    {
        return this->capacity_;
    }

    void resize(size_t n)
    {
        reserve(n);
        size_ = n;
    }
    void resize(size_t n, const T& val)
    {
        reserve(n);
        for (size_t i = size_; i < n; i++) {
            storage[i] = val;
        }
        size_ = n;
    }
    void reserve(size_t reserve_size)
    {
        if (reserve_size > this->capacity_) {
            T* storage2 = alloc.allocate(reserve_size);
            for (size_t i = 0; i < size_; i++) {
                storage2[i] = std::move(this->storage[i]);
            }
            alloc.deallocate(this->storage, capacity_);
            this->storage = storage2;
            this->capacity_ = reserve_size;
        }
    }

    bool empty() const
    {
        return size_ == 0;
    }

    iterator begin()
    {
        return iterator(storage);
    }
    iterator end()
    {
        return iterator(storage + size_);
    }
    const_iterator begin() const
    {
        return const_iterator(storage);
    }
    const_iterator end() const
    {
        return const_iterator(storage + size_);
    }
    using Myreverse_iterator = std::reverse_iterator<iterator>;
    Myreverse_iterator rbegin()
    {
        return Myreverse_iterator(end());
    }
    Myreverse_iterator rend()
    {
        return Myreverse_iterator(begin());
    }
    using Myreverse_iterator_const = std::reverse_iterator<const_iterator>;
    Myreverse_iterator_const rbegin() const
    {
        return Myreverse_iterator_const(end());
    }
    Myreverse_iterator_const rend() const
    {
        return Myreverse_iterator_const(begin());
    }

private:
    T* storage;
    Allocator alloc;
    size_t size_; // фактический размер вектора
    size_t capacity_; //размер памяти, доступной для записи без перераспределения
};

#endif
