#ifndef __ALLOC_H__
#define __ALLOC_H__

#define _PDFT int
#define _SIZT size_t
namespace JY
{
	template<class _Ty> inline
	_Ty* _Allocate(_PDFT _N,_Ty *)
	{
		if(_N < 0)
			_N = 0;
		return ((_Ty*)operator new((_SIZT)_N * sizeof(_Ty)));
	}
	template<class _T1, class _T2> inline
	void _Construct(_T1* _P,_T2& _V)
	{new ((void*)_P) _T1(_V);}
	
	template<class _Ty> inline
	void _Destroy(_Ty* _P)
	{
		_P->~_Ty();
	}
	template<class _Ty>
	class allocator
	{
	public:
		typedef _PDFT different_type;
		typedef _SIZT size_type;
		typedef _Ty* pointer;
		typedef const _Ty* const_pointer;
		typedef _Ty& reference;
		typedef const _Ty& const_reference;
	public:
		pointer address(reference _X)const
		{return &_X;}
		const_pointer address(const_reference _X)const
		{return &_X;}
		pointer allocate(size_type _N, const void*)
		{
			return _Allocate(different_type(_N),(pointer)0);
		
		}
		char* _Charalloc(size_type _N)
		{
			return _Allocate((different_type)_N,(char*)0);
		}
		void deallocate(void* _P, size_type)
		{operator delete(_P);}
		void construct(pointer _P,const _Ty& _V)
		{
			_Construct(_P,_V);
		}
		void destroy(pointer _P)
		{
			_Destroy(_P);
		}
		_SIZT max_size()const
		{
			_SIZT _N = (_SIZT)(-1)/sizeof(_Ty);
			return (0<_N ? _N : 1);
		}
	};
}
#endif
