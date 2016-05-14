#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdexcept>
#include "alloc.h"
template<class _Ty, class _A = JY::allocator<_Ty> > 
class My_vector
{
public:
	typedef My_vector<_Ty, _A> _Myt;
	typedef _A allocator_type;
	typedef _Ty* pointer;
	typedef const _Ty* const_pointer;
	typedef _Ty reference;
	typedef const _Ty const_reference;
	typedef pointer _Tptr;
	typedef _Tptr iterator;
	typedef const_pointer const_iterator;
	typedef int size_type;
public:
	My_vector(const _A& _A1 = _A())//default construct
		:allocator(_A1),_size(0),_capacity(0),buf(0)
	{}
	My_vector(size_type size,const _A& _A1=_A())
		:allocator(_A1),_size(0),_capacity(size)
	{
		//buf = new _Ty[_capacity];
		allocator.allocate(size,0);
	}
	My_vector(int size,_Ty _val)
	{
		_size = size;
		_capacity = size;
		buf = new _Ty[_capacity];
		for(int i = 0;i < size;i++)
		{
			buf[i] = _val;
		}
	}
	My_vector(My_vector<_Ty>const& rt)
		:buf(NULL)
	{operator=(rt);}
	_Myt& operator=(const _Myt& rt)
	{
		if(this != &rt)
		{
			delete []buf;
			_size = rt._size;
			_capacity = rt._capacity;
			buf = new _Ty[_capacity];
			for(int i=0;i<size;i++)
			{
				buf[i] = rt.buf[i];
			}
		}
		return *this;
	}
	~My_vector()
	{
		delete []buf;
	}
public:
	_Ty& operator[](int index)
	{return buf[index];}
	size_type capacity()const
	{return _capacity;}
	size_type size() const
	{return _size;}
	void resize(size_type _N ,const _Ty& _X = _Ty())
	{
		if(_N > _capacity)
		{
			reserve(2*_capacity);
		}
		if(size() > _N)
		{
			insert(end(),_N-size(),_X);
		}
		if(size() < _N)
		{
			erase(begin() + _N ,end());
		}
	}
	void insert(iterator _P,size_type _M,const _Ty& _x)
	{
		if(_capacity - _size < _M)//capacity not enough
		{
			reserve(2*_capacity);
			for(int i=0;i<_M;i++)
			{
				buf[_P+i] = _x;
			}
			_size = size() + _M;
		}
		if(size() - _P < _M)//insert before size()
		{
			for(int i=0;i<_M;i++)
			{
				buf[_P+i] = _x;
			}
			_size = _P + _M;
		}
		else if(0 < _M)
		{
			for(int i=0 ;i<_M;i++)
			{
				buf[_P + i] = _x;
			}
			_size = size()+_M;
		}
	}
	iterator erase(iterator _F, iterator _L)
	{
		while(_F <= _L)
		{
			erase(_F);
			_L--;
		}
		return _F;
	}
	iterator erase(iterator _P)
	{
		int index = _P - begin();
		memmove(_P ,_P+1,(_size-index)*sizeof(_Ty));
		_size--;
		return _P;
	}
	iterator begin()
	{return &buf[0];}
	const_iterator begin() const
	{return (const_iterator)&buf[0];}
	iterator end()
	{return &buf[size()];}
	const_iterator end() const
	{return &buf[size()];}
	const_reference at(size_type _P)
	{
		if(_P > _size)
			_Xran();
		return *(begin()+_P);
	}
	void reserve(int newCapacity)
	{
		if(newCapacity > _capacity)
		{
			newCapacity = 2*_capacity;
			_Ty* oldBuf = buf;
			buf = new _Ty[newCapacity];
			for(int i=0;i<_size;i++)
			{
				buf[i] = oldBuf[i];
			}
			_capacity = newCapacity;
			delete []oldBuf;
		}
	}
protected:
	void _Xran()
	{}
private:
	_A allocator;
	int _size;
	int _capacity;
	_Ty* buf;
};
#endif
